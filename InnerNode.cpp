#include "pch.h"
#include "Tree.h"
#include "InnerNode.h"
#include "LeafNode.h"
#include <memory>


InnerNode::InnerNode() 
{
	m_cnodesMax = std::get<0>(Node::treeCur->GetNodeNum());
	m_piKeyArr = new int[m_cnodesMax - 1];

	m_pChldNodeArr = new Node*[m_cnodesMax];
	for (size_t i = 0; i != m_cnodesMax; ++i) m_pChldNodeArr[i] = NULL;
}

InnerNode::InnerNode(int cnodes, int *pKey, Node **pnode): m_cnodes(cnodes), m_piKeyArr(pKey), m_pChldNodeArr(pnode){
	m_cnodesMax = std::get<0>(Node::treeCur->GetNodeNum());
}

size_t InnerNode::GetCChldNodes() const{
	return m_cnodes;
}

Node* InnerNode::GetChldNode(size_t npos) const{
	return m_pChldNodeArr[npos];
}

size_t InnerNode::GetKey(size_t npos) const {
	return m_piKeyArr[npos];
}

InnerNode* InnerNode::GetPrecNode() const{
	return m_pprecNode;
}

void InnerNode::SetPrecNode(InnerNode *pnode) {
	m_pprecNode = pnode;
}

void InnerNode::InsertKey(int ikey) {
	//if ikey is the first key inserted to this tree
	if (m_cnodes == 0) {
		m_piKeyArr[0] = ikey;

		LeafNode *pleft = new LeafNode, *pright = new LeafNode;
		pright->InsertKey(ikey);
		m_pChldNodeArr[0] = pleft, m_pChldNodeArr[1] = pright;
		pleft->SetPrecNode(this); pright->SetPrecNode(this);

		m_cnodes = 2;

		return;
	}

	size_t  nroute = 0;
	while (nroute != m_cnodes - 1 && m_piKeyArr[nroute] < ikey)
	{
		++nroute;
	}

	if (m_pChldNodeArr[nroute]) {
		m_pChldNodeArr[nroute]->InsertKey(ikey);
	}
	else {
		int *piarr = new int[m_cnodesMax - 1];
		piarr[0] = ikey;
		m_pChldNodeArr[nroute] = new LeafNode(1, piarr, this);
	}
}

void InnerNode::InsertChldNode(Node *pnode, int ikey) {
	size_t nposInrt = 0;      //the position of ikey to be inserted
	while (nposInrt != m_cnodes - 1 && m_piKeyArr[nposInrt] < ikey)
	{
		++nposInrt;
	}

	//the count of the nodes after being inserted is not greater the maximun
	if (m_cnodes + 1 <= m_cnodesMax) {
		for (size_t i = m_cnodes; i != nposInrt + 1;) {
			size_t i1 = i;
			m_pChldNodeArr[i1] = m_pChldNodeArr[--i];
		}
		m_pChldNodeArr[nposInrt + 1] = pnode;

		for (size_t j = m_cnodes - 1; j != nposInrt;) {
			size_t j1 = j;
			m_piKeyArr[j1] = m_piKeyArr[--j];
		}
		m_piKeyArr[nposInrt] = ikey;

		++m_cnodes;               //update the number of children nodes of this inner node
		pnode->SetPrecNode(this);    //set the prec node of pnode
	}
	else {
		//allocate the new node pointers space and initialize it
		Node **ppNodeArr = new Node*[m_cnodesMax];
		for (size_t i = 0; i != m_cnodesMax; ++i) {
			*(ppNodeArr + i) = nullptr;
		}
		int *piarr = new int[m_cnodesMax - 1];

		size_t cnodesNew;    //the cnodes of the splitted prec node

		if (nposInrt == m_cnodes - 1) {
			piarr[0] = ikey;

			ppNodeArr[1] = pnode;

			cnodesNew = 2;
		}
		else
		{
			std::uninitialized_copy(m_piKeyArr + nposInrt, m_piKeyArr + m_cnodes - 1, piarr);

			std::uninitialized_copy(m_pChldNodeArr + nposInrt + 1, m_pChldNodeArr + m_cnodes, ppNodeArr + 1);
			
			//if first key should be replaced
			if (nposInrt == 0) {
				m_piKeyArr[0] = ikey;

				m_pChldNodeArr[1] = pnode;

				ikey = piarr[0];

				cnodesNew = m_cnodes;

				m_cnodes = 2;
			}
			else
			{
				ppNodeArr[0] = pnode;

				cnodesNew = m_cnodes - nposInrt;

				m_cnodes = nposInrt + 1;
			}
		}

		InnerNode *pinnerNodeNew = new InnerNode(cnodesNew, piarr, ppNodeArr);
		for (size_t i = 0; i != cnodesNew; ++i) {
			if (pinnerNodeNew->GetChldNode(i)) {
				pinnerNodeNew->GetChldNode(i)->SetPrecNode(pinnerNodeNew);
			}
		}

		//if this is root node, then the tree grows a new level upwards
		if (m_pprecNode == nullptr) {
			Node **ppnodeArr = new Node*[m_cnodesMax];
			int *pkeyArr = new int[m_cnodesMax - 1];

			ppnodeArr[0] = this;
			pkeyArr[0] = ikey;
			ppnodeArr[1] = pinnerNodeNew;

			InnerNode *prootNodeNew = new InnerNode(2, pkeyArr, ppnodeArr);
			for (size_t i = 0; i != prootNodeNew->GetCChldNodes(); ++i) {
				prootNodeNew->GetChldNode(i)->SetPrecNode(prootNodeNew);
			}

			Node::treeCur->SetRootNode(prootNodeNew);
		}
		else {
			//insert the pinnerNodeNew-subtree to the prec node of this node
			m_pprecNode->InsertChldNode(pinnerNodeNew, ikey);
		}
	}
}

InnerNode::~InnerNode()
{
	//loop of deleting all nodes in the node pointers' domain
	for (size_t i = 0; i != m_cnodes; ++i) {
		delete m_pChldNodeArr[i];
	}

	delete[]m_piKeyArr;
	delete[]m_pChldNodeArr;
}

std::ostream& operator<<(std::ostream &os, const InnerNode &node) {
	os << "InnerNode " << &node << ": ";

	size_t i = 0, imax = node.GetCChldNodes();
	while (i != imax - 1)
	{
		os << node.GetChldNode(i) << " < " << node.GetKey(i) << " <= ";
		++i;
	}
	os << node.GetChldNode(i);
	return os;
}
