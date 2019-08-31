#include "Node.h"
#include <math.h>
#include "KPoint.h"
#include "Element.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNode::CNode()
{
	m_dX =m_dY=m_dZ =0.0;
	m_iLabel = -1;
	m_pMirror = NULL;
	m_iInternalLabel = -1;
	m_bActive = true;
}
CNode::CNode(double x, double y, double z)
{
	m_dX= x; m_dY = y; m_dZ = z;
	m_iLabel = -1;
	m_pMirror = NULL;
	m_bActive = true;
}
void CNode::SetupNode(int iLabel, double x, double y, double z)
{
	m_dX = x; m_dY = y; m_dZ = z;
	m_iLabel = -1;
	m_pMirror = NULL;
	m_bActive = true;
	m_iLabel = iLabel;
}
CNode::~CNode()
{
}
double Distance(CNode* node1, CNode* node2)
{
	double x1 = node1->m_dX;
	double x2 = node2->m_dX;
	double y1 = node1->m_dY;
	double y2 = node2->m_dY;
	double z1 = node1->m_dZ;
	double z2 = node2->m_dZ;
	return sqrt( (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));
}
CNode::CNode(CKPoint pt)
{
	m_dX = pt.GetX();
	m_dY = pt.GetY();
	m_dZ = pt.GetZ();
	m_iLabel = -1;
	m_pMirror = NULL;
	m_iInternalLabel = -1;
	m_bActive = true;
}
CNode* MiddleNode(CNode* pNode1, CNode* pNode2)
{
	CNode * pNode = new CNode();
	pNode->SetX((pNode1->GetX()+ pNode2->GetX())*0.5);
	pNode->SetY((pNode1->GetY()+ pNode2->GetY())*0.5);
	pNode->SetZ((pNode1->GetZ()+ pNode2->GetZ())*0.5);
	return pNode;
}
CNode& CNode::operator=(CNode& other)
{
	m_dX = other.m_dX;
	m_dY = other.m_dY;
	m_dZ = other.m_dZ;
	return *this;
}
CNode& CNode::operator=(CKPoint& pt)
{
	m_dX = pt.GetX();
	m_dY = pt.GetY();
	m_dZ = pt.GetZ();
	return *this;
}
CNode* CNode::DeepCopyNode(int iOffset)
{
	CNode* pNewNode = new CNode();
	*pNewNode = *this;
	pNewNode->SetLabel(GetLabel()+iOffset);
	return pNewNode;
}
bool CNode::IsAtSameLocation(CNode* pNode)
{
	double x = pNode->GetX();
	double y = pNode->GetY();
	double z = pNode->GetZ();
	x = m_dX - x;
	y = m_dY - y;
	z = m_dZ - z;
	if ( (x*x + y*y + z*z) < 1.0e-12 )
		return true;
	else
		return false;
}
void CNode::AddParentElement(CElement* pElem)
{
	// dont add redundant elements to the list
	std::list<CElement*>::iterator eleIt;
	for ( eleIt=m_lstParents.begin(); eleIt!=m_lstParents.end(); eleIt++ )
	{
		if ( *eleIt == pElem )
			return;
	}
	m_lstParents.push_back(pElem);
}
void CNode::AddNeighbourNode(int iInternalLab)
{
	// dont add redundant node to the list
	std::vector<int>::iterator labIt;
	for (labIt = m_lstNBRNodes.begin(); labIt != m_lstNBRNodes.end(); labIt++)
	{
		if (*labIt == iInternalLab)
			return;
	}
	m_lstNBRNodes.push_back(iInternalLab);
}
void CNode::MakeYourselfOrphan()
{
	m_lstParents.clear();
}
bool CNode::AreYouAnOrphan()
{
	return ( m_lstParents.size() == 0 );
}

void CNode::TranslateNode(int iAxisIndex, double dDistance)
{
	if ( iAxisIndex ==0 )
		m_dX = m_dX+dDistance;
	if ( iAxisIndex == 1 )
		m_dY = m_dY + dDistance;
	if ( iAxisIndex == 2 )
		m_dZ = m_dZ + dDistance;
}
void CNode::RotateNode(int iAxis,double dDeg)
{
	double dPi = asin(1.0)*2.0;
	double dRad = dDeg*dPi/180.0;
	double c = cos(dRad); 
	double s = sin(dRad);
	double x,y,z;
	switch (iAxis)
	{
	case 0:
		y = c*m_dY-s*m_dZ;
		z = s*m_dY+c*m_dZ;
		m_dY = y; m_dZ = z;
		return;
	case 1:
		x = c*m_dX+s*m_dZ;
		z = -s*m_dX+c*m_dZ;
		m_dX = x; m_dZ = z;
		return;
	case 2:
		x = c*m_dX+s*m_dY;
		y = -s*m_dX+c*m_dY;
		m_dX = x; m_dY = y;
		return;
	default:
		return;
	}
}
