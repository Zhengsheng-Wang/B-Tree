#include "pch.h"
#include "Tree.h"
#include "LeafNode.h"
#include "InnerNode.h"


Tree::Tree(size_t b, size_t b1): cchldsInnerNode(b), ckeysLeafNode(b1){
	cchldsInnerNode = cchldsInnerNode < 2 ? 2 : cchldsInnerNode;
	ckeysLeafNode = ckeysLeafNode < 1 ? 1 : ckeysLeafNode;

	Node::treeCur = this;   //set current tree pointer to this
	m_pnodeRoot = new InnerNode;   //construct current tree root
}

std::tuple<int, int> Tree::GetNodeNum() {
	return std::make_tuple(cchldsInnerNode, ckeysLeafNode);
}

void Tree::PrintTree() {
	std::deque<Node*> deqNode;     //deque to store the node to be printed out

	deqNode.push_back(m_pnodeRoot);
	while (!deqNode.empty())
	{
		Node *n = deqNode.front();
		deqNode.pop_front();
		//if the node processed now is a inner node, push its children node to the deque
		if (InnerNode *in = dynamic_cast<InnerNode*>(n)) {
			size_t nchldNodes = in->GetCChldNodes();  //get the number of child nodes
			//push the children nodes
			for (size_t i = 0; i != nchldNodes; ++i) {
				deqNode.push_back(in->GetChldNode(i));
			}
		}

		if (!n) {
			continue;
		}
		else if (InnerNode *in = dynamic_cast<InnerNode*>(n)) {
			std::cout << *in;
		}
		else
		{
			std::cout << *(dynamic_cast<LeafNode*>(n));
		}
		std::cout << std::endl;
	}
}

void Tree::SetRootNode(InnerNode *pnodeRoot) {
	m_pnodeRoot = pnodeRoot;
}

void Tree::InsertKey(int ikey) {
	m_pnodeRoot->InsertKey(ikey);
}

Tree::~Tree()
{
	delete m_pnodeRoot;
}
