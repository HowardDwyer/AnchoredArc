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
	m_centerComputed = false;
	m_areaAndNormalComputed = false;
}

CElement::~CElement() {
	if (m_ppNodes != NULL)
		delete[] m_ppNodes;
	if (m_pStiffMatrix != NULL)
		delete[] m_pStiffMatrix;
}

void CElement::ComputeCenter()
{
	double xx = 0.0;
	double yy = 0.0;
	double zz = 0.0;
	double oneThird = 1.0 / 3.0;
	for (int i = 0; i < this->m_iNumNodes; i++) {
		CNode* pNode = GetNode(i);
		xx += pNode->GetX();
		yy += pNode->GetY();
		zz += pNode->GetZ();
	}
	m_center.SetX(xx * oneThird);
	m_center.SetY(yy * oneThird);
	m_center.SetZ(zz * oneThird);
	m_centerComputed = true;
} // CElement::ComputeCenter

CKPoint CElement::GetCenter() 
{
	if (!m_centerComputed) { ComputeCenter(); }
	return CKPoint(m_center.GetX(), m_center.GetY(), m_center.GetZ());
}

void CElement::SetNodeLabel(int ithNode, int iLabel) {
	m_iArrayNodeLabels[ithNode] = iLabel;
	m_centerComputed = false;
	m_areaAndNormalComputed = false;
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
	m_centerComputed = false;
	m_areaAndNormalComputed = false;
}

void CElement::ComputeAreaAndNormal()
{
	CNode* pn0 = m_ppNodes[0];
	CNode* pn1 = m_ppNodes[1];
	CNode* pn2 = m_ppNodes[2];
	CVector edge01(pn1->GetX() - pn0->GetX(), pn1->GetY() - pn0->GetY(), pn1->GetZ() - pn0->GetZ());
	CVector edge02(pn2->GetX() - pn0->GetX(), pn2->GetY() - pn0->GetY(), pn2->GetZ() - pn0->GetZ());
	m_faceNormal = edge01.Cross(edge02);
	m_area = m_faceNormal.Length() * 0.5;
	m_areaAndNormalComputed = true;
} // CElement::ComputeAreaAndNormal

double CElement::GetArea() {
	if (!m_areaAndNormalComputed) { ComputeAreaAndNormal(); }
	return m_area;
} // CElement::GetArea

CVector CElement::GetFaceNormal() {
	if (!m_areaAndNormalComputed) { ComputeAreaAndNormal(); }
	CVector result(m_faceNormal.GetX(), m_faceNormal.GetY(), m_faceNormal.GetZ());
	return result;
}  // CElement::GetFaceNormal()
