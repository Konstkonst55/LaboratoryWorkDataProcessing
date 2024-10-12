#pragma once

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include "Node.h"

class BinaryTree {
protected: 
	void PrintRootLeftRightRecursive(Vertex* node);
	void PrintLeftRootRightRecursive(Vertex* node);
	void PrintLeftRightRootRecursive(Vertex* node);

	int CalculateTreeSizeRecursive(Vertex* node);
	int CalculateTreeSumRecursive(Vertex* node);
	int CalculateTreeHeightRecursive(Vertex* node);
	void CalculateSumOfPathRecursive(Vertex* node, int currentHeight, int& totalHeight);

	Vertex* FindVertexRecursive(Vertex* node, int value);
	Vertex** FindVertexPointer(Vertex** node, int value);

	bool DeleteVertexRecursive(Vertex* node, int value);
	void DeleteTreeRecursive(Vertex* node);

public:
	Vertex* root;

	BinaryTree();
	~BinaryTree();

	void PrintRootLeftRight();
	void PrintLeftRootRight();
	void PrintLeftRightRoot();
	void PrintInfo();

	int GetSize();
	int GetSum();
	int GetHeight();
	double GetAvgHeight();
	void CalculateSumOfPath(int currentHeight, int& totalHeight);

	Vertex* FindVertex(int key);

	bool DeleteVertex(int key);
	void Delete();
};

class PBST : public BinaryTree {
public:
	PBST();

	void Create(int* arr, int size);
};

class RST : public BinaryTree {
public:
	RST();

	void AddVertex(int data);
	void AddVertexDoubleIndirection(int data);
};

class AVL : public BinaryTree {
private:
	void RotateLL(Vertex*& node);
	void RotateRR(Vertex*& node);
	void RotateLR(Vertex*& node);
	void RotateRL(Vertex*& node);

public:
	AVL();

	void AddVertex(int data);
};

Vertex* CreateVertex(int value);

#endif // !TREE_UTILS_H