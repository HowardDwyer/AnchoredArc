//========================================================================================================
// EndoTest.cpp
//========================================================================================================
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <algorithm>
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
void PopulateAreaArray();
void PopulateTransposedAreaArray();
void PopulateVectorX();
void SetVectorsXandYtoZero();
void MatrixMatrix();
void MatrixMatrix_AAT();
void MatrixMatrix_AAT_Parallel();
void MatrixVector();
void SetupModel();

void Debug_MockAreaMatrix(int oneThirdOfSize);
void Debug_MockTransposedAreaMatrix(int oneThirdOfSize);

double* X;
double* Y;
double** area;
double** areaT;
double** ATA;
double DX_GLOBAL = 10;
bool EnablePrintToFile_GLOBAL = false;
bool EnableDebugConsoleMsg_GLOBAL = true;
int main(int argc, char** argv)
{
	double norm = 0;
/*	// Setup Model
	if(EnableDebugConsoleMsg_GLOBAL){cout << "SetupModel\n";}
	SetupModel();

	// Allocate Arrays
	if(EnableDebugConsoleMsg_GLOBAL){cout << "AllocateArrays\n";}
	AllocateArrays();

	// POPULATE AREA AND X ARRAYS
	if(EnableDebugConsoleMsg_GLOBAL){cout << "PopulateArrays\n";}
	PopulateArrays();
*/
	if (EnableDebugConsoleMsg_GLOBAL) { cout << "Debug_MockAreaMatrix\n"; }
//	Debug_MockAreaMatrix(200);
	Debug_MockTransposedAreaMatrix(3200);

	// MATRIX MULTIPLICATION
	if (EnableDebugConsoleMsg_GLOBAL) { cout << "MatrixMatrix\n"; }
//	MatrixMatrix();
//	MatrixMatrix_AAT();
	MatrixMatrix_AAT_Parallel();

	// COMPUTE Y = ATA*X
/*	if (EnableDebugConsoleMsg_GLOBAL) { cout << "MatrixVector\n"; }
	MatrixVector();

	// PRINT L2 NORM OF Y
	if (EnableDebugConsoleMsg_GLOBAL) { cout << "Computing Norm\n"; }
	for (int i = 0; i < 3 * m_nNumNodes; i++)
	{
		norm = norm + Y[i] * Y[i];
	}
	norm = sqrt(norm);
*/
	//----------------------------------------------------------------------------------------------
	clock_t total = clock();  // total execution time,in ticks
	if (EnablePrintToFile_GLOBAL) {
		printf("(%3.5lf) L2 Norm\n", norm);
		printf("(%3.5lf seconds) in Total\n", ((float)total) / CLOCKS_PER_SEC);
	}
	if(EnableDebugConsoleMsg_GLOBAL){
		double totalTime = ((double)total) / CLOCKS_PER_SEC; 
		cout << totalTime << " seconds in Total\n";          
	}

	if (EnableDebugConsoleMsg_GLOBAL) { cout << "return\n"; }
	return 0;
} // main

//============== DEBUG MOCK AREA MATRIX ===============================================
// used for testing only.  replaces SetupModel, AllocateArrays, PopulateArrays
// matrix is square, dimension is three times the value of m_nNumNodes.
// all entries are positive in the range (0, 4).
void Debug_MockAreaMatrix(int oneThirdOfSize)
{
	m_nNumNodes = oneThirdOfSize;
	int numNodesTimesThree = 3 * m_nNumNodes;
	AllocateArrays();

	for (int i=0;i<numNodesTimesThree;i++) 
	{
		for (int j = 0; j < numNodesTimesThree; j++)
		{
			// this formula is nonsense ... it gives positive values in a non-trivial but repeatable pattern
			areaT[i][j] = 4.0*abs(sin(5*i + 7*j + 2));
		}
	}
} // Debug_MockAreaMatrix

//============== DEBUG MOCK TRANSPOSED AREA MATRIX ===============================================
// used for testing only.  replaces SetupModel, AllocateArrays, PopulateArrays
void Debug_MockTransposedAreaMatrix(int oneThirdOfSize)
{
	m_nNumNodes = oneThirdOfSize;
	int numNodesTimesThree = 3 * m_nNumNodes;
	AllocateArrays();

	for (int i = 0; i < numNodesTimesThree; i++)
	{
		for (int j = 0; j < numNodesTimesThree; j++)
		{
			// this formula is nonsense ... it gives positive values in a non-trivial but repeatable pattern
			areaT[j][i] = 4.0 * abs(sin(5 * i + 7 * j + 2));
		}
	}
} // Debug_MockTransposdAreaMatrix

//=========== SET UP MODEL ==================================================================
// width and height are hard-coded as 200 x 200
void SetupModel() {
	int nnode = 0;
	int nelem = 0;

	// a 1D array of doubles which store 3D coord X,Y,Z for each node
	double* nodecoord1;

	// vertex indices: each element is composed of 3 nodes
	int* conn1;

	double dx = DX_GLOBAL;
	double width = 200;
	double height = 200;
	int nx = (int)(width / dx + 1);  // number of columns of nodes
	int ny = (int)(height / dx + 1); // number of rows of nodes
	nnode = nx * ny;                 // total number of nodes

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
	int cntByThree = 0;
	for (int i = 0; i < nx; i++) {
		nodeXValue = negHalfWidth + i * dx;
		for (int j = 0; j < ny; j++) {
			nodecoord1[cntByThree] = nodeXValue;
			nodecoord1[cntByThree + 1] = negHalfHeight + j * dx;
			nodecoord1[cntByThree + 2] = 0.0;
			cntByThree += 3;
		}
	}

	//----------------------------------------------------------------------------------
	cntByThree = 0;
	for (int i = 0; i < nx - 1; i++) {
		for (int j = 0; j < ny - 1; j++) {
			conn1[cntByThree] = i * ny + j + 1;
			conn1[cntByThree + 1] = (i + 1) * ny + j + 1;
			conn1[cntByThree + 2] = i * ny + j + 1 + 1;
			cntByThree += 3;

			conn1[cntByThree] = (i + 1) * ny + j + 1;
			conn1[cntByThree + 1] = (i + 1) * ny + j + 1 + 1;
			conn1[cntByThree + 2] = i * ny + j + 1 + 1;
			cntByThree += 3;
		}
	}

	//----------------------------------------------------------------------------------
	m_nNumNodes = nnode;
	m_nNumElems = nelem;

	if (EnablePrintToFile_GLOBAL) {
		printf("Number of 3D Points: %d\n", m_nNumNodes);
		printf("Number of Triangular Elements: %d\n", m_nNumElems);
	}
	m_pNodes = new CNode[m_nNumNodes];
	m_pElements = new CElement[m_nNumElems];

	//----------------------------------------------------------------------------------
	cntByThree = 0;
	for (int i = 0; i < m_nNumNodes; i++) {
		m_pNodes[i].SetX(nodecoord1[cntByThree]);
		m_pNodes[i].SetY(nodecoord1[cntByThree + 1]);
		m_pNodes[i].SetZ(nodecoord1[cntByThree + 2]);
		m_pNodes[i].SetLabel(i + 1);
		m_pNodes[i].SetInternalLabel(i);
		cntByThree += 3;
	}

	//----------------------------------------------------------------------------------
	// Setup elements
	cntByThree = 0;
	for (int i = 0; i < m_nNumElems; i++) {
		m_pElements[i].SetNode(0, &m_pNodes[conn1[cntByThree] - 1]);
		m_pElements[i].SetNode(1, &m_pNodes[conn1[cntByThree + 1] - 1]);
		m_pElements[i].SetNode(2, &m_pNodes[conn1[cntByThree + 2] - 1]);
		m_pElements[i].SetLabel(i + 1);
		cntByThree += 3;
	}
	//------------------------------------------------------------------------------------
	// release resources
	delete[] nodecoord1;
	delete[] conn1;
}// SetupModel

//===================== SET VECTORS X AND Y TO ZERO ===================================================
void SetVectorsXandYtoZero()
{
	int numNodesTimesThree = 3 * m_nNumNodes;
	for (int i = 0; i < numNodesTimesThree; i++) { X[i] = Y[i] = 0.0; }
} // SetVectorsXandYtoZero()

 //============== ALLOCATE ARRAYS ==================================================================
void AllocateArrays()
{
	int numNodesTimesThree = 3 * m_nNumNodes;

	// X and Y are 1D arrays
	X = new double[numNodesTimesThree];
	Y = new double[numNodesTimesThree];
	SetVectorsXandYtoZero();
	// area is a square 2D array
//	area = new double* [numNodesTimesThree];
//	for (int i = 0; i < numNodesTimesThree; ++i)
//		area[i] = new double[numNodesTimesThree];
	areaT = new double* [numNodesTimesThree];
	for (int i = 0; i < numNodesTimesThree; ++i)
		areaT[i] = new double[numNodesTimesThree];

	// ATA is a square 2D array
	ATA = new double* [numNodesTimesThree];
	for (int i = 0; i < numNodesTimesThree; ++i)
		ATA[i] = new double[numNodesTimesThree];
} // AllocateArrays

//===================== POPULATE ARRAYS ===================================================
void PopulateArrays()
{
//	PopulateAreaArray();
	PopulateTransposedAreaArray();
	PopulateVectorX();
} // PopulateArrays

//===================== POPULATE AREA ARRAY ===================================================
void PopulateAreaArray()
{
	int nodeIndexTimesThree;
	int numOfNodesTimesThree = 3 * m_nNumNodes;
	double oneThird = 1.0 / 3.0;
	// Loop over elements
	for (int i = 0; i < m_nNumElems; i++)
	{
		// Get Area of Element
		double element_area = m_pElements[i].GetArea();
		double oneThirdArea = element_area * oneThird;

		// Loop over vertices in this triangular element
		for (int k = 0; k < 3; k++) {

			// Get Index of Node which is located at vertex k in triangular element i.
			int nodeNumber = m_pElements[i].GetNode(k)->GetLabel() - 1;
			nodeIndexTimesThree = nodeNumber * 3;

			// Accumulate area in area[][] array
			for (int j = 0; j < 3; j++)
			{
				area[nodeIndexTimesThree + j][nodeIndexTimesThree + j] += element_area;

				if (nodeIndexTimesThree + j + 1 < numOfNodesTimesThree)
				{
					area[nodeIndexTimesThree + j + 1][nodeIndexTimesThree + j] += oneThirdArea;
				}

				if (nodeIndexTimesThree + j - 1 > 0)
				{
					area[nodeIndexTimesThree + j][nodeIndexTimesThree + j - 1] += oneThirdArea;
				}
			}
		} // loop through the nodes which are vertices for this element
	} // loop through each triangular element
} // PopulateAreaArray

//===================== POPULATE TRANSPOSED AREA ARRAY ===================================================
void PopulateTransposedAreaArray()
{
	int nodeIndexTimesThree;
	int numOfNodesTimesThree = 3 * m_nNumNodes;
	double oneThird = 1.0 / 3.0;
	// Loop over elements
	for (int i = 0; i < m_nNumElems; i++)
	{
		// Get Area of Element
		double element_area = m_pElements[i].GetArea();
		double oneThirdArea = element_area * oneThird;

		// Loop over vertices in this triangular element
		for (int k = 0; k < 3; k++) {

			// Get Index of Node which is located at vertex k in triangular element i.
			int nodeNumber = m_pElements[i].GetNode(k)->GetLabel() - 1;
			nodeIndexTimesThree = nodeNumber * 3;

			// Accumulate area in areaT[][] array
			for (int j = 0; j < 3; j++)
			{
				areaT[nodeIndexTimesThree + j][nodeIndexTimesThree + j] += element_area;

				if (nodeIndexTimesThree + j + 1 < numOfNodesTimesThree)
				{
					areaT[nodeIndexTimesThree + j][nodeIndexTimesThree + j + 1] += oneThirdArea;
				}

				if (nodeIndexTimesThree + j - 1 > 0)
				{
					areaT[nodeIndexTimesThree + j - 1][nodeIndexTimesThree + j] += oneThirdArea;
				}
			}
		} // loop through the nodes which are vertices for this element
	} // loop through each triangular element
} //PopulateTransposedAreaArray

//===================== POPULATE VECTOR X ===================================================
void PopulateVectorX()
{
	int nodeIndexTimesThree;
	// Loop over elements
	for (int i = 0; i < m_nNumElems; i++)
	{
		// Loop over vertices in this triangular element
		for (int k = 0; k < 3; k++) {
			// Get Index of Node which is located at vertex k in triangular element i.
			int nodeNumber = m_pElements[i].GetNode(k)->GetLabel() - 1;
			nodeIndexTimesThree = nodeNumber * 3;

			// Accumulate normals of triangular elements in X[] array
			CVector normal = m_pElements[i].GetFaceNormal();
			X[nodeIndexTimesThree]     += normal.GetX();
			X[nodeIndexTimesThree + 1] += normal.GetY();
			X[nodeIndexTimesThree + 2] += normal.GetZ();
		} // loop through the nodes which are vertices for this element
	} // loop through each triangular element
} // PopulateArrays

//================= MATRIX MATRIX ===================================================================
// COMPUTE ATA = Area^T * Area;
void MatrixMatrix()
{
	int numNodesTimesThree = 3 * m_nNumNodes;
	for (int j = 0; j < numNodesTimesThree; j++) {
		for (int i = j; i < numNodesTimesThree; i++) {
			double dotProdSum = 0.0;
			for (int k = 0; k < numNodesTimesThree; k++) {
				// note: the "out of order" indices in the first term is intentional because
				// we are multiplying using the transpose as the first matrix.
				dotProdSum += area[k][i] * area[k][j];
			}
			ATA[i][j] = dotProdSum;
			ATA[j][i] = dotProdSum;
		}
	}
} // MatrixMatrix

//================= MATRIX MATRIX A AT ============================================================
// COMPUTE ATA = AreaT * AreaT^T;
void MatrixMatrix_AAT()
{
	int numNodesTimesThree = 3 * m_nNumNodes;
	double* row_i ;
	double* row_j ;

	for (int j = 0; j < numNodesTimesThree; j++) {
		row_j = areaT[j];
		for (int i = j; i < numNodesTimesThree; i++) {
			row_i = areaT[i];
			double dotProdSum = 0.0;
			for (int k = 0; k < numNodesTimesThree; k++) {
				dotProdSum += row_i[k] * row_j[k];
			}
			ATA[i][j] = dotProdSum;
			ATA[j][i] = dotProdSum;
		}
	}
} // MatrixMatrix_AAT

//================= MATRIX MATRIX A AT PARALLEL ====================================================
// COMPUTE ATA = AreaT * AreaT^T;
void MatrixMatrix_AAT_Parallel()
{
	int numNodesTimesThree = 3 * m_nNumNodes;
	double* row_i;
	double* row_j;
	int nThreads = thread::hardware_concurrency();
	if (EnableDebugConsoleMsg_GLOBAL) { cout << nThreads << " threads\n"; }
	vector<thread> threadVector(nThreads);
	mutex critical;
	//--------------------------------------------------------------------------------------
	for (int t = 0; t < nThreads; t++)
	{
		threadVector[t] = thread(bind(
			[&](const int bj, const int ej, const int t)
			{
				for (int j = bj; j < ej; j++)
				{
					row_j = areaT[j];
					for (int i = j; i < numNodesTimesThree; i++) {
						row_i = areaT[i];
						double dotProdSum = 0.0;
						for (int k = 0; k < numNodesTimesThree; k++) {
							dotProdSum += row_i[k] * row_j[k];
						}
						ATA[i][j] = dotProdSum;
						ATA[j][i] = dotProdSum;
					} // for i
				} // for j
			}, t * numNodesTimesThree / nThreads,
			(t + 1) == nThreads ? numNodesTimesThree :
				(t + 1) * numNodesTimesThree / nThreads,
				t));
	} // for t
	for_each(threadVector.begin(), threadVector.end(), [](thread& x) {x.join(); });
} // MatrixMatrix_AAT_Parallel

//============== MATRIX VECTOR ========================================================
//  performs  Y = Y + ATA*X
void MatrixVector()
{
	int numNodesTimesThree = 3 * m_nNumNodes;
	double dotProdSum;
	double* row_i;
	for (int i = 0; i < numNodesTimesThree; i++)
	{
		dotProdSum = 0.0;
		row_i = ATA[i];
		for (int k = 0; k < numNodesTimesThree; k++) {
			dotProdSum = dotProdSum + row_i[k] * X[k];
		}
		Y[i] = dotProdSum;
	}
} // MatrixVector

