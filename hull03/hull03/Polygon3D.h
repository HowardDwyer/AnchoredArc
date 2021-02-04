#pragma once
#include "Point3D.h"
#include "Plane3D.h"
#include <vector>

class Polygon3D : public HullGeomType
{
private:
	std::vector<Point3D> fVertices;
protected:
	virtual void SetBoundingBox() const;
public:
	Polygon3D();
	Polygon3D(const Polygon3D& source);

	~Polygon3D();

	void CopyVertices(const std::vector<Point3D>& newVertices);
	void AppendVertex(const Point3D newVertex);
	int NumberOfVertices() const { return fVertices.size(); }
	Point3D Vertex(const int index) const;

	virtual void Draw(){ /* TODO*/ }
	virtual void TransformBy(const TransfMatrix3D &aM);

	bool IsPlanar() const;
	Plane3D PlaneOfPoly() const;

	double SignedArea() const; // positive is CCW, returns 0.0 if the poly is not planar
	bool operator == (const Polygon3D& otherPoly) const 
	{
		const int thisNumV = this->NumberOfVertices();
		const int otherNumV = otherPoly.NumberOfVertices();
		bool allMatch = (thisNumV == otherNumV);
		for (int index = 0; allMatch && (index < thisNumV); index++)
		{
			allMatch = (Vertex(index) == otherPoly.Vertex(index));
		}
		return allMatch;
	}
    bool operator != (const Polygon3D& otherPoly) const 
	{
		const int thisNumV = this->NumberOfVertices();
		const int otherNumV = otherPoly.NumberOfVertices();
		bool misMatch = (thisNumV != otherNumV);
		for (int index = 0; !misMatch && (index < thisNumV); index++)
		{
			misMatch = (Vertex(index) != otherPoly.Vertex(index));
		}
		return misMatch;
	}

}; // class Polygon3D
