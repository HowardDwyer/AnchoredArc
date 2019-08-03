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
void setupModel();

double* X;
double* Y;
double** area;
double** ATA;
double DX_GLOBAL = 10;

int main(int argc, char** argv)
{
	// Setup Model
	setupModel();

	// Allocate Arrays
	AllocateArrays();

	// POPULATE AREA AND X ARRAYS
	PopulateArrays();

	// MATRIX MULTIPLICATION
	MatrixMatrix();

	// COMPUTE Y = ATA*X
	MatrixVector();

	// PRINT L2 NORM OF Y
	double norm = 0;
	for (int i = 0; i < 3 * m_nNumNodes; i++)
	{
		norm = norm + Y[i] * Y[i];
	}
	norm = sqrt(norm);
	clock_t total = clock();
	printf("(%3.5lf) L2 Norm\n", norm);
	printf("(%3.5lf seconds) in Total\n", ((float)total) / CLOCKS_PER_SEC);

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
void setupModel() {

	int nnode = 0;
	int nelem = 0;
	double* nodecoord1;
	int* conn1;
	int ny = 0;
	int nx = 0;

	double dx = DX_GLOBAL;
	double width = 200;
	double height = 200;
	nx = (int)(width / dx + 1);
	ny = (int)(height / dx + 1);
	nnode = nx * ny;
	nodecoord1 = new double[3 * nnode];
	nelem = (nx - 1) * (ny - 1) * 2;
	conn1 = new int[3 * nelem];

	// create simple mesh
	int cnt = 0;
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			nodecoord1[3 * cnt + 0] = -width / 2.0 + i * dx;
			nodecoord1[3 * cnt + 1] = -height / 2.0 + j * dx;
			nodecoord1[3 * cnt + 2] = 0;
			cnt++;
		}
	}
	cnt = 0;
	for (int i = 0; i < nx - 1; i++) {
		for (int j = 0; j < ny - 1; j++) {
			conn1[3 * cnt] = i * ny + j + 1;
			conn1[3 * cnt + 1] = (i + 1) * ny + j + 1;
			conn1[3 * cnt + 2] = i * ny + j + 1 + 1;
			cnt++;

			conn1[3 * cnt] = (i + 1) * ny + j + 1;
			conn1[3 * cnt + 1] = (i + 1) * ny + j + 1 + 1;
			conn1[3 * cnt + 2] = i * ny + j + 1 + 1;
			cnt++;

		}
	}


	m_nNumNodes = nnode;
	m_nNumElems = nelem;

	printf("Number of 3D Points: %d\n", m_nNumNodes);
	printf("Number of Triangular Elements: %d\n", m_nNumElems);
	m_pNodes = new CNode[m_nNumNodes];
	m_pElements = new CElement[m_nNumElems];

	for (int i = 0; i < m_nNumNodes; i++) {

		m_pNodes[i].SetX(nodecoord1[3 * i]);
		m_pNodes[i].SetY(nodecoord1[3 * i + 1]);
		m_pNodes[i].SetZ(nodecoord1[3 * i + 2]);
		m_pNodes[i].SetLabel(i + 1);
		m_pNodes[i].SetInternalLabel(i);
	}

	// Setup elements
	for (int i = 0; i < m_nNumElems; i++) {
		m_pElements[i].SetNode(0, &m_pNodes[conn1[3 * i] - 1]);
		m_pElements[i].SetNode(1, &m_pNodes[conn1[3 * i + 1] - 1]);
		m_pElements[i].SetNode(2, &m_pNodes[conn1[3 * i + 2] - 1]);
		m_pElements[i].SetLabel(i + 1);
	}

}
