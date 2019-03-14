#include "pch.h"
#include "Tree.h"
#include "LeafNode.h"
#include "InnerNode.h"
#include <memory>
#include <set>

LeafNode::LeafNode() {
	m_ckeysMax = std::get<1>(Node::treeCur->GetNodeNum());
	m_piKeyArr = new int[m_ckeysMax];
}

LeafNode::LeafNode(int ckeys, int *piarr): m_ckeys(ckeys), m_piKeyArr(piarr) {
	m_ckeysMax = std::get<1>(Node::treeCur->GetNodeNum());
}

LeafNode::LeafNode(int ckeys, int *piarr, InnerNode *pprecNode): m_ckeys(ckeys), m_piKeyArr(piarr), 
				m_pprecNode(pprecNode){
	m_ckeysMax = std::get<1>(Node::treeCur->GetNodeNum());
}

InnerNode* LeafNode::GetPrecNode() const{
	return m_pprecNode;
}

void LeafNode::SetPrecNode(InnerNode *pnode) {
	m_pprecNode = pnode;
}

size_t LeafNode::GetCKeys() const {
	return m_ckeys;
}

int LeafNode::GetKey(size_t npos) const {
	return m_piKeyArr[npos];
}

void LeafNode::InsertKey(int ikey) {
	size_t ckeysNew = m_ckeys + 1;     //new m_ckeys

	//the keys number of this node is in limit
	if (ckeysNew <= m_ckeysMax) {
		size_t nPosInrt = m_ckeys;
		while (nPosInrt != 0)
		{
			if (m_piKeyArr[nPosInrt - 1] > ikey) {
				m_piKeyArr[nPosInrt] = m_piKeyArr[nPosInrt - 1];
				--nPosInrt;
				continue;
			}
			break;
		}
		m_piKeyArr[nPosInrt] = ikey;

		m_ckeys = ckeysNew;
	}
	else {
		size_t ckeys = ckeysNew / 2, ckeys1 = ckeysNew - ckeys;
		std::set<int> s;
		for (size_t i = 0; i != m_ckeys; ++i) {
			s.insert(m_piKeyArr[i]);
		}
		s.insert(ikey);

		int *piarr = new int[m_ckeysMax], *piarr1 = new int[m_ckeysMax];
		auto b = s.cbegin(), e = s.cend();
		for (size_t i = 0; i != ckeys; ++i) {
			piarr[i] = *b;
			++b;
		}
		for (size_t j = 0; j != ckeys1; ++j) {
			piarr1[j] = *b;
			++b;
		}

		delete[]m_piKeyArr;
		m_piKeyArr = piarr;
		m_ckeys = ckeys;

		m_pprecNode->InsertChldNode(new LeafNode(ckeys1, piarr1), piarr1[0]);
	}
}

LeafNode::~LeafNode()
{
	delete[]m_piKeyArr;
}

std::ostream& operator<<(std::ostream &os, const LeafNode &node) {
	os << "LeafNode " << &node << ": ";

	size_t i = 0, imax = node.GetCKeys();
	while (i != imax - 1)
	{
		os << node.GetKey(i) << " < ";
		++i;
	}
	os << node.GetKey(imax - 1);
	return os;
}
