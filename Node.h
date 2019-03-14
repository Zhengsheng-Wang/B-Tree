#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <deque>

class Tree;
class InnerNode;
class Node
{
	public:
	Node();
	virtual ~Node();

	public:
	virtual void InsertKey(int) = 0;

	virtual InnerNode* GetPrecNode() const = 0;
	virtual void SetPrecNode(InnerNode*) = 0;

	public:
	static Tree *treeCur;
};

