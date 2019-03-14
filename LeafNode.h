#pragma once
#include "Node.h"
class LeafNode :
	public Node
{
	friend std::ostream& operator<<(std::ostream&, const LeafNode&);

	public:
	LeafNode();
	LeafNode(int, int*);
	LeafNode(int, int*, InnerNode*);
	virtual ~LeafNode();

	public:
	void InsertKey(int) override;

	InnerNode* GetPrecNode() const override;
	void SetPrecNode(InnerNode*) override;

	size_t GetCKeys() const;
	int GetKey(size_t) const;
	
	private:
	size_t m_ckeys;  //the number of the keys 
	size_t m_ckeysMax;   //the max number of the keys

	int *m_piKeyArr;    //the pointer pointing to the keys contained in this node

	InnerNode *m_pprecNode;
};

