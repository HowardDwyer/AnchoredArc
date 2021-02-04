#include "stdafx.h"
#include "Polygon3D.h"
#include "HullConst.h"
#include <cmath>

Polygon3D::Polygon3D(const Polygon3D& source)
{
	fVertices = source.fVertices;
} // Polygon3D::Polygon3D

void Polygon3D::CopyVertices(const std::vector<Point3D>& newVertices)
{
	fVertices = newVertices;
} // Polygon3D::CopyVertices

void Polygon3D::AppendVertex(const Point3D newVertex)
{
	const int numV = NumberOfVertices();
	if (numV > 0){
		const Point3D firstVertex = fVertices.at(0);
		const Point3D lastVertex = fVertices.at(numV - 1);
		if ((newVertex != firstVertex) && (newVertex != lastVertex))
		{
			fVertices.push_back(newVertex);
		}
	}
	else {
		fVertices.push_back(newVertex);
	}
}// Polygon3D::AppendVertex

void Polygon3D::SetBoundingBox() const
{
	if (NumberOfVertices() == 0) {
		fIsBoundingBoxSet = false;
	}
	else {
		fMinX = fMaxX = fVertices.at(0).X();
		fMinY = fMaxY = fVertices.at(0).Y();
		fMinZ = fMaxZ = fVertices.at(0).Z();
		fIsBoundingBoxSet = true;
		for (int index = 1; index < NumberOfVertices(); index++)
		{
			const double thisX = fVertices.at(index).X();
			if (thisX < fMinX) {
				fMinX = thisX;
			}
			else if (thisX > fMaxX) {
				fMaxX = thisX;
			}

			const double thisY = fVertices.at(index).Y();
			if (thisY < fMinY) {
				fMinY = thisY;
			}
			else if (thisY > fMaxY) {
				fMaxY = thisY;
			}

			const double thisZ = fVertices.at(index).Z();
			if (thisZ < fMinZ) {
				fMinZ = thisZ;
			}
			else if (thisZ > fMaxZ) {
				fMaxZ = thisZ;
			}
		}
	}
} // Polygon3D::SetBoundingBox

void Polygon3D::TransformBy(const TransfMatrix3D &aM)
{
	for (int index = 0; index < NumberOfVertices(); index++)
	{
		fVertices.at(index).TransformBy(aM);
	}
} // Polygon3D::TransformByPolygon3D::TransformBy

Point3D Polygon3D::Vertex(const int index) const {
	Point3D result;
	if ((0 <= index) && (index < NumberOfVertices()))
	{
		result = fVertices.at(index);
	} // if index is in range
	return result;
} // Polygon3D::Vertex

bool Polygon3D::IsPlanar() const
{
	bool result = true;
	const int numV = NumberOfVertices();
	if (numV >= 3){
		bool foundPlane = false;
		Plane3D thisPlane;
		for (int index1 = 0; !foundPlane && (index1 < numV); index1++)
		{
			const Point3D p1 = Vertex(index1);
			for (int index2 = index1 + 1; !foundPlane && (index2 < numV); index2++)
			{
				const Point3D p2 = Vertex(index2);
				for (int index3 = index2 + 1; !foundPlane && (index3 < numV); index3++)
				{
					const Point3D p3 = Vertex(index3);
					thisPlane = Plane3D(p1, p2, p3);
					foundPlane = thisPlane.IsWellDefined();
				}
			}
		} // if 3 vertices define a plane
		if (foundPlane){
			for (int index = 0; result && (index < numV); index++)
			{
				result = thisPlane.PointIsOnPlane(Vertex(index));
			}
		}
	} // if there are at least 3 vertices

	return result;
} // Polygon3D::IsPlanar


Plane3D Polygon3D::PlaneOfPoly() const
{
	Plane3D result;
	result.SetNormalToZero();
	if (IsPlanar()){
		const int numV = NumberOfVertices();
		if (numV >= 3){
			bool foundPlane = false;
			Plane3D thisPlane;
			for (int index1 = 0; !foundPlane && (index1 < numV); index1++)
			{
				const Point3D p1 = Vertex(index1);
				for (int index2 = index1 + 1; !foundPlane && (index2 < numV); index2++)
				{
					const Point3D p2 = Vertex(index2);
					for (int index3 = index2 + 1; !foundPlane && (index3 < numV); index3++)
					{
						const Point3D p3 = Vertex(index3);
						thisPlane = Plane3D(p1, p2, p3);
						foundPlane = thisPlane.IsWellDefined();
					}
				}
			} // if 3 vertices define a plane
			if (foundPlane){
				result = thisPlane;
			}
		}
	}
	return result;
} // Polygon3D::PlaneOfPoly


double Polygon3D::SignedArea() const // positive is CCW, returns 0.0 if the poly is not planar
{
	double result = 0.0;
	const int numV = NumberOfVertices();
	if ((numV >= 3) && IsPlanar()){
		const Plane3D thisPlane = PlaneOfPoly();
		const BoundVector3D thisPlaneNormal = thisPlane.NormalVector();
		const Point3D normalStartPt = thisPlaneNormal.StartPoint();
		const Point3D normalEndPt = thisPlaneNormal.EndPoint();
		TransfMatrix3D M;
		M.SetToRotateToVerticalUp(
			normalStartPt.X(),
			normalStartPt.Y(),
			normalStartPt.Z(),
			normalEndPt.X(),
			normalEndPt.Y(),
			normalEndPt.Z());

		Point3D A =Vertex(0);
		A.TransformBy(M);
		for (int indexB = 1; indexB <= (numV - 2); indexB++)
		{
			Point3D B = Vertex(indexB);
			B.TransformBy(M);
			Point3D C = Vertex(indexB + 1);
			C.TransformBy(M);
			const FreeVector3D AB(A, B);
			const FreeVector3D AC(A, C);
			const FreeVector3D ABxAC = AB.Cross(AC);
			result += ABxAC.Z();
		}
	} // if there at least 3 vertices and the poly is planr

	return result;
} // Polygon3D::SignedArea