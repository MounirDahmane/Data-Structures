#pragma once

// i try it mainly for th int data type

#include <iostream>
#include "queue.h"

template <typename T>
class BinaryTree
{
public:
	BinaryTree() = default;
	BinaryTree(T data) 
	{
		this->_root = new node;
		this->_root->data = data;
		this->_root->left = nullptr;
		this->_root->right = nullptr;
		this->_nmbrNodes++;
	}		
	~BinaryTree() 
	{
		_clean(this->_root);
		this->_root = nullptr;
	}

	void insert(T data)
	{
		if (!this->_root)
		{
			this->_root = new node;
			this->_root->left = nullptr;
			this->_root->right = nullptr;
			this->_root->data = data;
			this->_nmbrNodes++;
			return;
		}

		node* newLeaf = new node;
		newLeaf->left = nullptr;
		newLeaf->data = data;
		newLeaf->right = nullptr;

		node* current = this->_root;
		node* parent = nullptr;

		while (current)
		{
			parent = current;
			if (current->data == data)
			{
				std::cout << "THIS_VALUE_IS_ALREADY_INSERTED!" << std::endl;
				delete newLeaf;
				return;
			}
			(data > current->data) ? current = current->right : current = current->left;
			/*if (data > current->data)
				current = current->right;
			else if (data < current->data)
				current = current->left;*/
		}
		(data > parent->data) ? parent->right = newLeaf : parent->left = newLeaf;
		this->_nmbrNodes++;
	}
	bool search(T data)
	{
		if (!this->_root)
		{
			std::cout << "THE_TREE_IS_EMPTY!" << std::endl;
			return false;
		}

		node* current = this->_root;
		while (current)
		{
			if (current->data == data)
				return true;
			if (data > current->data)
				current = current->right;
			else if (data < current->data)
				current = current->left;
		}
		return false;
	}
	void remove(T data)
	{
		if (!this->_root)
		{
			std::cout << "THE_TREE_IS_EMPTY!" << std::endl;
			return;
		}
		if (!this->search(data))
		{
			std::cout << "THE_VALUE_IS_NOT_IN_THE_TREE!" << std::endl;
			return;
		}
		this->_remove(this->_root, data, nullptr);
		this->_nmbrNodes--;
	}
	//Breadth_first method
	void lvlOrderPrint()
	{
		if (!this->_root)
			return;
		Queue<node*> queue;
		queue.Enqueue(this->_root);
		std::cout << "Root :\n";
		std::size_t i = 0;
		while (!queue.empty())
		{
			node* current = queue.Front();

			std::cout << "[" << i << "]" << ":" << current->data << " -->";
			if (current->left) queue.Enqueue(current->left);
			if (current->right) queue.Enqueue(current->right);
			queue.Dequeue();
			i++;
			i % 7 == 0 ? std::cout << std::endl : std::cout;
		}
		std::cout << " Deep\n";
	}
	//depth_first methods
	void PreOrder()
	{
		this->_TreePrint(this->_root, PREORDER);
	}
	void InOrder()
	{
		this->_TreePrint(this->_root, INORDER);
	}
	void PostOrder()
	{
		this->_TreePrint(this->_root, POSTORDER);
	}

	bool IsBST() {
		return _isBSTRange(this->_root, INT_MIN, INT_MAX);
	}
	
	T max()
	{
		if (!this->_root)
		{
			std::cout << "THE_TREE_IS_EMPTY!" << std::endl;
			return NULL;
		}
		node* current = this->_root;
		while (current->right)
			current = current->right;
		return current->data;
	}
	T min()
	{
		if (!this->_root)
		{
			std::cout << "THE_TREE_IS_EMPTY!" << std::endl;
			return NULL;
		}
		node* current = this->_root;
		while (current->left)
			current = current->left;
		return current->data;
	}
	// the target represent the data in a particular node
	int GetDepth(T target) { return this->_calculateDepth(this->_root, target, 0); }
	int GetHeight() { return _calculateHeight(this->_root); }
	int Get_nmbrNodes() { return this->_nmbrNodes; }
	
private:
	struct node
	{
		node* left;
		T  data;
		node* right;
	};

	enum { PREORDER = 0, INORDER, POSTORDER };
	node* _root = nullptr;
	int _nmbrNodes = 0;

	int _calculateHeight(node* current)
	{
		if (!current)
			return -1;
		return (std::max(_calculateHeight(current->left), _calculateHeight(current->right)) + 1);
	}
	int _calculateDepth(node* current, T target, int depth)
	{
		if (!current) // if the target does not exist or there is no tree
			return depth - 1;
		if (current->data == target)
			return depth;

		int leftDepth  = _calculateDepth(current->left , target, depth + 1);
		int rightDepth = _calculateDepth(current->right, target, depth + 1);

		// Return the maximum depth from the left and right subtrees
		if (leftDepth != -1)
			return leftDepth;
		return rightDepth;
	}
	void _TreePrint(node* current, int PRINT)
	{
		if (!current)
			return;
		switch (PRINT)
		{
		case PREORDER:	std::cout << current->data << std::endl;
			_TreePrint(current->left, PREORDER);
			_TreePrint(current->right, PREORDER);
			break;
		case INORDER:	_TreePrint(current->left, INORDER);
			std::cout << current->data << std::endl;
			_TreePrint(current->right, INORDER);
			break;
		case POSTORDER:	_TreePrint(current->left, POSTORDER);
			_TreePrint(current->right, POSTORDER);
			std::cout << current->data << std::endl;
			break;
		}
	}
	void _clean(node* current)
	{
		if (!current)
			return;
		_clean(current->left);
		_clean(current->right);
		delete current;
	}
	bool _isBSTRange(node* root, int min_val, int max_val) 
	{
		if (root == nullptr) 
			return true;

		// Check if the current node's value is within the allowed range
		if (root->data < min_val || root->data > max_val) 
			return false;

		// Recursively check the left and right subtrees with updated ranges
		return _isBSTRange(root->left, min_val, root->data - 1) &&
			   _isBSTRange(root->right, root->data + 1, max_val);
	}
	node* _min(node* current)
	{
		if (!current)
			return nullptr;
		while (current->left)
			current = current->left;
		return current;
	}
	void _remove(node* current, T data, node* parent)
	{
		if (!current)
			return;

		if (data > current->data)
			_remove(current->right, data, current);
		else if (data < current->data)
			_remove(current->left, data, current);
		else {
			if (!current->left && !current->right)
			{
				parent->right == current ? parent->right = nullptr : parent->left = nullptr;
				delete current;
			}
			else if (!current->left)
			{
				parent->right == current ? parent->right = current->right : parent->left = current->right;

				current->right = nullptr;
				delete current;
			}
			else if (!current->right)
			{
				parent->right == current ? parent->right = current->left : parent->left = current->left;

				current->left = nullptr;
				delete current;
			}
			else
			{
				node* minNode = _min(current->right);
				current->data = minNode->data;
				_remove(current->right, minNode->data, current);
			}
		}
	}
};