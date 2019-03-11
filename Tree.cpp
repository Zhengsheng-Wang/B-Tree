#include "pch.h"
#include "Tree.h"
#include "LeafNode.h"
#include "InnerNode.h"


Tree::Tree(size_t b, size_t b1): cchldsInNode(b), ckeysLeafNode(b1){
	cchldsInNode = cchldsInNode < 2 ? 2 : cchldsInNode;
	ckeysLeafNode = ckeysLeafNode < 1 ? 1 : ckeysLeafNode;

	Node::treeCur = this;   //set current tree pointer to this
	m_pnodeRoot = new InnerNode;   //construct current tree root
}

std::tuple<int, int> Tree::GetNodeNum() {
	return std::make_tuple(cchldsInNode, ckeysLeafNode);
}

void Tree::PrintTree() {
	std::deque<Node*> deqNode;     //deque to store the node to be printed out

	deqNode.push_back(m_pnodeRoot);
	while (deqNode.empty())
	{
		Node *n = deqNode.front();
		deqNode.pop_front();
		//if the node processed now is a inner node, push its children node to the deque
		if (InnerNode *in = dynamic_cast<InnerNode*>(n)) {
			size_t nchldNode = in->GetCNodes();  //get the number of child nodes
			//push the children nodes
			for (size_t i = 0; i != nchldNode; ++i) {
				deqNode.push_back(in->GetChldNode(i));
			}
		}
		n->Print();  
		std::cout << std::endl;
	}
}

void Tree::InsertNextKey(int ikey) {
	//if the tree is null-tree, assign this first key to the root inner node
	if (m_pnodeRoot->GetCNodes() == 0) {
	}
}

Tree::~Tree()
{
	delete m_pnodeRoot;
}
