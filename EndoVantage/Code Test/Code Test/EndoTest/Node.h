//========================================================================================================
// Node.h: interface for the CNode class.
//========================================================================================================
#ifndef __NODE_HH
#define __NODE_HH 

#include <list>
using namespace std;
#include <list>
#include <vector>
class CKPoint;
class CVector;
class CElement; 

#define  dTorlerence 1.0e-3;
class CNode
{
public:
	CNode();
	CNode(double x, double y, double z);
	void SetupNode(int iLabel, double x, double y, double z);
	CNode(CKPoint);
	virtual ~CNode();
	void SetX(double x) {m_dX = x;} 
	void SetY(double y) {m_dY = y;} 
	void SetZ(double z) {m_dZ = z;} 
	double GetX() { return m_dX;}
	double GetY() { return m_dY;}
	double GetZ() { return m_dZ;}
	void SetLabel ( int iLabel) { m_iLabel = iLabel;}
	void SetInternalLabel(int iLabel) { m_iInternalLabel = iLabel; }
	int GetInternalLabel() { return m_iInternalLabel; }
	void RotateNode(int iAxisIndex, double dAngle);
	void TranslateNode(int iAxisIndex, double dDistance);
	CNode& operator=(CNode& other);
	CNode& operator=(CKPoint& pt);
	int GetLabel () { return m_iLabel; }
	CNode* DeepCopyNode(int iOffset);
	void SetMirror(CNode* pNode) { m_pMirror = pNode;}
	CNode* GetMirror() { return m_pMirror; }
	bool IsAtSameLocation(CNode* pNode);
	friend double Distance(CNode* node1, CNode* node2);
	friend CNode* MiddleNode(CNode* pNode1, CNode* pNode2);
	//
	void AddParentElement(CElement* pElem);
	void AddNeighbourNode(int labNode);
	std::list<CElement*>* GetParentElements() { return &m_lstParents;}
	std::vector<int>* GetNeighbourNodes() { return &m_lstNBRNodes; }
	void MakeYourselfOrphan();
	bool AreYouAnOrphan();
	//void SetNodalResult(CNodalResult* pResult) { m_pResult = pResult; }
	bool IfActive() { return m_bActive; }
	void SetActiveState();
	int GetGlobalIndexOffset() { return m_iGlobalIndexOffset; }
	void SetGlobalIndexOffset(int iOffset) { m_iGlobalIndexOffset = iOffset; }
private:
	double m_dX, m_dY, m_dZ;
	int m_iLabel;
	int m_iInternalLabel;
	int m_iGlobalIndexOffset;
	CNode* m_pMirror; // mirror node
	std::list<CElement*> m_lstParents;
	std::vector<int> m_lstNBRNodes;
	bool m_bActive; 
};

#endif 
