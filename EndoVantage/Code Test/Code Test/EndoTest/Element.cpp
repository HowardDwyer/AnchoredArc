//========================================================================================================
// Element.cpp: implementation for the CElement class.
//========================================================================================================
#include "Element.h"
#include "Node.h"
#include <math.h>
#include "Vector.h"
#include <string>

using namespace std;

CElement::CElement() {
	for (int j = 0; j < 20; j++) {
		m_iFilledNode[j] = 0;
	}
	m_pStiffMatrix = NULL;
	m_bStiffMatrixReady = false;
	m_iNumNodes = 3;
	m_ppNodes = new CNode*[3];
}

CElement::~CElement() {
	if (m_ppNodes != NULL)
		delete[] m_ppNodes;
	if (m_pStiffMatrix != NULL)
		delete[] m_pStiffMatrix;
}
CKPoint CElement::GetCenter() {
	double xx = 0.0;
	double yy = 0.0;
	double zz = 0.0;
	for (int i = 0; i < this->m_iNumNodes; i++) {
		CNode* pNode = GetNode(i);
		xx += pNode->GetX();
		yy += pNode->GetY();
		zz += pNode->GetZ();
	}
	xx /= 3.0;
	yy /= 3.0;
	zz /= 3.0;
	return CKPoint(xx, yy, zz);
}
void CElement::SetNodeLabel(int ithNode, int iLabel) {
	m_iArrayNodeLabels[ithNode] = iLabel;
}
int CElement::GetNodeLabel(int ithNode) {
	return m_iArrayNodeLabels[ithNode];
}
CNode* CElement::GetNode(int i) {
	return m_ppNodes[i];;
}
void CElement::SetNode(int i, CNode* pNode) {
	m_ppNodes[i] = pNode;
	m_iArrayNodeLabels[i] = pNode->GetLabel();
	pNode->AddParentElement(this);
}
double CElement::GetArea() {
	CNode* pn0 = m_ppNodes[0];
	CNode* pn1 = m_ppNodes[1];
	CNode* pn2 = m_ppNodes[2];
	double x0 = pn0->GetX();
	double y0 = pn0->GetY();
	double z0 = pn0->GetZ();
	double x1 = pn1->GetX();
	double y1 = pn1->GetY();
	double z1 = pn1->GetZ();
	double x2 = pn2->GetX();
	double y2 = pn2->GetY();
	double z2 = pn2->GetZ();
	CKPoint pt0(x0, y0, z0), pt1(x1, y1, z1), pt2(x2, y2, z2);
	CVector v1 = pt1 - pt0;
	CVector v2 = pt2 - pt0;
	double dArea = 0.0;
	dArea = (v1.Cross(v2)).Length();
	return dArea * 0.5;
}
CVector CElement::GetFaceNormal() {
	CNode* pn0 = m_ppNodes[0];
	CNode* pn1 = m_ppNodes[1];
	CNode* pn2 = m_ppNodes[2];
	double x0 = pn0->GetX();
	double y0 = pn0->GetY();
	double z0 = pn0->GetZ();
	double x1 = pn1->GetX();
	double y1 = pn1->GetY();
	double z1 = pn1->GetZ();
	double x2 = pn2->GetX();
	double y2 = pn2->GetY();
	double z2 = pn2->GetZ();
	CKPoint pt0(x0, y0, z0), pt1(x1, y1, z1), pt2(x2, y2, z2);
	CVector v1 = pt1 - pt0;
	CVector v2 = pt2 - pt0;
	return v1.Cross(v2);
}
