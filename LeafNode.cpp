#include "pch.h"
#include "Tree.h"
#include "LeafNode.h"
#include "InnerNode.h"
#include <memory>
#include <set>

/*
LeafNode::LeafNode(InnerNode *m_pprecNode) 
{
	ckeysMax = std::get<1>(Node::treeCur->GetNodeNum());
	pKey = new int[ckeysMax];
	m_pprecNode = m_pprecNode;
}
*/

LeafNode::LeafNode(int *p) {
	ckeysMax = std::get<1>(Node::treeCur->GetNodeNum());
	pKey = p;
}

LeafNode::LeafNode(int *p, InnerNode *pprecNode): m_pprecNode(pprecNode){
	ckeysMax = std::get<1>(Node::treeCur->GetNodeNum());
	pKey = p;
}

void LeafNode::Print(){
	std::stringstream ss;
	ss << "LeafNode->" << this << ": ";

	for (size_t i = 0; i != ckeys; ++i) {
		ss << pKey[i] << " < ";
	}
	ss.str().erase(ss.str().length() - 3);
	ss << "   ";
	std::cout << ss.str();
}

size_t LeafNode::GetCKeys() {
	return ckeys;
}
void LeafNode::SetCKeys(size_t c) {
	ckeys = c;
}

InnerNode* LeafNode::GetPrecNode() {
	return m_pprecNode;
}

void LeafNode::SetPrecNode(InnerNode *pnode) {
	m_pprecNode = pnode;
}

void LeafNode::InsertKey(int ikey) {
	size_t ckeysNew = ckeys + 1;     //new ckeys

	if (ckeysNew <= ckeysMax) {
	    int *p = new int[ckeysMax];     //new array to store the result after inserted

		for (size_t i = 0; i != ckeys; ++i) {
			if (pKey[i] <= ikey) ++i;
			else {
				auto p1 = std::uninitialized_copy(pKey, pKey + i, p);
				*(++p1) = ikey;
				std::uninitialized_copy(pKey + i, pKey + ckeysMax - 1, p1);
				break;
			}
		}
		delete[]pKey;
		pKey = p;
	}
	else {
		size_t ckeys = ckeysNew / 2, ckeys1 = ckeysNew - ckeys;
		std::set<int> s;
		for (size_t i = 0; i != ckeysMax; ++i) {
			s.insert(pKey[i]);
		}
		s.insert(ikey);

		int *p1 = new int[ckeysMax], *p2 = new int[ckeysMax];
		auto b = s.cbegin(), e = s.cend();
		for (size_t i = 0; i != ckeys; ++i) {
			p1[i] = *b;
			++b;
		}
		for (size_t j = 0; j != ckeys1; ++j) {
			p2[j] = *b;
			++b;
		}

		delete[]pKey;
		pKey = p1;

		m_pprecNode->InsertNode(new LeafNode(p2), p2[0]);
	}
}

LeafNode::~LeafNode()
{
	delete[]pKey;
}
