//========================================================================================================
// EndoTest.cpp
//========================================================================================================
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>

#include "KPoint.h"
#include "Element.h"
#include "Node.h"
#include "Vector.h"

using namespace std;

int m_nNumNodes;
int m_nNumElems;
CNode* m_pNodes;
CElement* m_pElements;

void AllocateArrays();
void PopulateArrays();
void MatrixMatrix();
void MatrixVector();
void SetupModel();

double* X;
double* Y;
double** area;
double** ATA;
double DX_GLOBAL = 0.5;

int main(int argc, char** argv)
{
	// Setup Model
	cout << "SetupModel\n";
	SetupModel();

/*	// Allocate Arrays
	cout << "AllocateArrays\n";
	AllocateArrays();

	// POPULATE AREA AND X ARRAYS
	cout << "PopulateArrays\n";
	PopulateArrays();

	// MATRIX MULTIPLICATION
	cout << "MatrixMatrix\n";
	MatrixMatrix();

	// COMPUTE Y = ATA*X
	cout << "MatrixVector\n";
	MatrixVector();

	// PRINT L2 NORM OF Y
	double norm = 0;
	cout << "Y=( ";
	for (int i = 0; i < 3 * m_nNumNodes; i++)
	{
		cout << Y[i] << " ";
		norm = norm + Y[i] * Y[i];
	}
	cout << ")\n";
	cout << "Squared norm = "<<norm<<'\n';
	norm = sqrt(norm);
	cout<< norm <<" L2 Norm\n";
*/
	//----------------------------------------------------------------------------------------------
	clock_t total = clock();  // total execution time,in ticks
	cout << "printf stmts\n";
//	printf("(%3.5lf) L2 Norm\n", norm);
//	printf("(%3.5lf seconds) in Total\n", ((float)total) / CLOCKS_PER_SEC);
	double totalTime = ((double)total) / CLOCKS_PER_SEC; // dwyerdebug
	cout << totalTime << " seconds in Total\n";          // dwyerdebug

	cout << "return\n";
	return 0;
}

void AllocateArrays()
{
	X = new double[3 * m_nNumNodes];
	Y = new double[3 * m_nNumNodes];
	area = new double* [3 * m_nNumNodes];
	for (int i = 0; i < 3 * m_nNumNodes; ++i)
		area[i] = new double[3 * m_nNumNodes];

	ATA = new double* [3 * m_nNumNodes];
	for (int i = 0; i < 3 * m_nNumNodes; ++i)
		ATA[i] = new double[3 * m_nNumNodes];

}

void MatrixVector()
{
	for (int i = 0; i < 3 * m_nNumNodes; i++)
	{
		Y[i] = 0.0;
		for (int k = 0; k < 3 * m_nNumNodes; k++) {
			Y[i] = Y[i] + ATA[i][k] * X[k];
		}
	}

}
void MatrixMatrix()
{
	// COMPUTE ATA = Area^T * Area;
	for (int j = 0; j < 3 * m_nNumNodes; j++) {
		for (int i = 0; i < 3 * m_nNumNodes; i++) {
			ATA[i][j] = 0.0;
			for (int k = 0; k < 3 * m_nNumNodes; k++) {
				ATA[i][j] = ATA[i][j] + area[k][i] * area[k][j];
			}

		}
	}
}

void PopulateArrays()
{
	// Loop over elements
	for (int i = 0; i < m_nNumElems; i++)
	{
		// Loop over nodes in element
		for (int k = 0; k < 3; k++) {

			// Get Index of Node
			int NodeNumber = m_pElements[i].GetNode(k)->GetLabel() - 1;
			// Get Area of Element
			double element_area = m_pElements[i].GetArea();

			// Accumulate area in area[][] array
			for (int j = 0; j < 3; j++) {
				area[3 * NodeNumber + j][3 * NodeNumber + j] = area[3
					* NodeNumber + j][3 * NodeNumber + j] + element_area;
				if (3 * NodeNumber + j + 1 < 3 * m_nNumNodes) {
					area[3 * NodeNumber + j + 1][3 * NodeNumber + j] = area[3
						* NodeNumber + j + 1][3 * NodeNumber + j]
						+ element_area / 3.0;
				}
				if (3 * NodeNumber + j - 1 > 0) {
					area[3 * NodeNumber + j][3 * NodeNumber + j - 1] = area[3
						* NodeNumber + j][3 * NodeNumber + j - 1]
						+ element_area / 3.0;
				}
			}
			// Accumulate normal in X[] array
			CVector normal = m_pElements[i].GetFaceNormal();
			X[3 * NodeNumber] = X[3 * NodeNumber] + normal.GetX();
			X[3 * NodeNumber + 1] = X[3 * NodeNumber + 1] + normal.GetY();
			X[3 * NodeNumber + 2] = X[3 * NodeNumber + 2] + normal.GetZ();
		}
	}
}

//=========== SET UP MODEL ==================================================================
// width and height are hard-coded as 200 x 200
void SetupModel() {
	int nnode = 0;
	int nelem = 0;

	// a 1D array of doubles which store 3D coord X,Y,Z for each node
	double* nodecoord1;

	// vertex indices: each element is composed of 3 nodes
	int* conn1;

	int ny = 0;
	int nx = 0;

	double dx = DX_GLOBAL;
	double width = 200;
	double height = 200;
	nx = (int)(width / dx + 1);  // number of columns of nodes
	ny = (int)(height / dx + 1); // number of rows of nodes
	nnode = nx * ny;             // total number of nodes

	nodecoord1 = new double[3 * nnode]; // (X,Y,Z) for the coordinates
	nelem = (nx - 1) * (ny - 1) * 2; // number of triangle elements
	conn1 = new int[3 * nelem];      // node indices for the elements

	//----------------------------------------------------------------------------------
	double nodeXValue;
	double negHalfWidth = -width * 0.5;
	double negHalfHeight = -height * 0.5;

	//----------------------------------------------------------------------------------
	// create simple mesh
	int cnt;
	int threeCnt = 0;
	for (int i = 0; i < nx; i++) {
		nodeXValue = negHalfWidth + i * dx;
		for (int j = 0; j < ny; j++) {
			nodecoord1[threeCnt] = nodeXValue;
			nodecoord1[threeCnt + 1] = negHalfHeight + j * dx;
			nodecoord1[threeCnt + 2] = 0;
			threeCnt += 3;
		}
	}

	//----------------------------------------------------------------------------------
//	cnt = 0;
	threeCnt = 0;
	for (int i = 0; i < nx - 1; i++) {
		for (int j = 0; j < ny - 1; j++) {
			conn1[threeCnt] = i * ny + j + 1;
			conn1[threeCnt + 1] = (i + 1) * ny + j + 1;
			conn1[threeCnt + 2] = i * ny + j + 1 + 1;
//			cnt++;
			threeCnt += 3;

			conn1[threeCnt] = (i + 1) * ny + j + 1;
			conn1[threeCnt + 1] = (i + 1) * ny + j + 1 + 1;
			conn1[threeCnt + 2] = i * ny + j + 1 + 1;
//			cnt++;
			threeCnt += 3;
		}
	}

	//----------------------------------------------------------------------------------
	m_nNumNodes = nnode;
	m_nNumElems = nelem;

	printf("Number of 3D Points: %d\n", m_nNumNodes);
	printf("Number of Triangular Elements: %d\n", m_nNumElems);
	m_pNodes = new CNode[m_nNumNodes];
	m_pElements = new CElement[m_nNumElems];

	//----------------------------------------------------------------------------------
	int threeI=0;
	for (int i = 0; i < m_nNumNodes; i++) {
		m_pNodes[i].SetX(nodecoord1[threeI]);
		m_pNodes[i].SetY(nodecoord1[threeI + 1]);
		m_pNodes[i].SetZ(nodecoord1[threeI + 2]);
		m_pNodes[i].SetLabel(i + 1);
		m_pNodes[i].SetInternalLabel(i);
		threeI += 3;
	}

	//----------------------------------------------------------------------------------
	// Setup elements
	threeI = 0;
	for (int i = 0; i < m_nNumElems; i++) {
		m_pElements[i].SetNode(0, &m_pNodes[conn1[threeI] - 1]);
		m_pElements[i].SetNode(1, &m_pNodes[conn1[threeI + 1] - 1]);
		m_pElements[i].SetNode(2, &m_pNodes[conn1[threeI + 2] - 1]);
		m_pElements[i].SetLabel(i + 1);
		threeI += 3;
	}
	//------------------------------------------------------------------------------------
	// release resources
	delete[] nodecoord1;
	delete[] conn1;
}// SetupModel
