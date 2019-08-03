//===========================================================================
// Element.h: interface for the CElement class.
//========================================================================================================
#ifndef __ELEMENT_HH
#define __ELEMENT_HH 

#include <string>
#include <list>
#include "Node.h"

enum ELEMTYPE {
    LTRIANGLETP
};

class CElement
{
 public:
    CElement();
    virtual ~CElement();
    void SetLabel( int iLabel ) { m_iLabel = iLabel ; }
    int GetLabel() { return m_iLabel; }
    void SetNode(int i, CNode* pNode);
 
    CNode* GetNode(int iIndex);
    int GetNumOfNodes() { return m_iNumNodes;}
    void SetNodeLabel(int ithNode, int iLabel);
    int GetNodeLabel(int ithNode);

    // some geometry utilities
    virtual CKPoint GetCenter();
    virtual double GetArea();
    virtual CVector GetFaceNormal();

 protected:
    int m_iLabel;
    CNode** m_ppNodes;
    int m_iNumNodes;
    int m_iNumEdges;
    int m_iNumFaces;
    int m_iNumBC;
    int m_iFilledNode[20];
    int m_iArrayNodeLabels[40]; // an alternative place holding the node labels
    bool m_bActive;
    bool m_bStiffMatrixReady;

    //  finite element procedure information and utilities 
    double* m_pGaussPoints; // the Gauss points, allocated in each type element
    double* m_pStiffMatrix;
    // double's for inertia term
    double* m_pInertia;

 public:

};

#endif 
