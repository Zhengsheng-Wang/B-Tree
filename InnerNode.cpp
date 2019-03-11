#include "pch.h"
#include "Tree.h"
#include "InnerNode.h"


InnerNode::InnerNode() 
{
	cnodesMax = std::get<0>(Node::treeCur->GetNodeNum());
	pKey = new int[cnodesMax - 1];
	m_pChldNode = new Node*[cnodesMax];
}

size_t InnerNode::GetCNodes() {
	return cnodes;
}

void InnerNode::SetCNodes(size_t c) {
	cnodes = c;
}

Node* InnerNode::GetChldNode(size_t npos) {
	return m_pChldNode[npos];
}

InnerNode* InnerNode::GetPrecNode() {
	return m_pprecNode;
}

void InnerNode::SetPrecNode(InnerNode *pnode) {
	m_pprecNode = pnode;
}

void InnerNode::InsertNode(Node *pnode, int ikey) {
}

void InnerNode::Print(){
	std::stringstream ss;
	ss << "InnerNode->" << this << ": ";

	for (size_t i = 0; i != cnodes; ++i) {
		ss << m_pChldNode[i];
		if (i == cnodes - 1) break;
		ss << " < " << pKey[i] << " <= ";
	}

	ss << "   ";
	std::cout << ss.str();
}


InnerNode::~InnerNode()
{
	//loop of deleting all nodes in the node pointers' domain
	for (size_t i = 0; i != cnodes; ++i) {
		delete m_pChldNode[i];
	}

	delete[]pKey;
	delete[]m_pChldNode;
}
