#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H
#include <iostream>


template <class T>
class BinarySearchTree
{
	public:

		BinarySearchTree();// "�� ���������" ������� ������ ������
		BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
		BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
		BinarySearchTree <T>& operator=(const BinarySearchTree <T>& src) = delete;
		BinarySearchTree <T>& operator=(BinarySearchTree <T>&& src) noexcept;

		~BinarySearchTree();
		// 1.1 ������� ������ �� ����� � �������� ������ ������
		bool iterativeSearch(const T& key) const;
		// 2 ������� ������ �������� � ������: true, ���� ������� ��������; false, ���� ������� ��� ���
		bool insert(const T& key);
		// 3.1 �������� �������� �� ������, �� ���������� ������� ���������; true, ���� ������� ������; false, ���� �������� �� ����
		bool deleteKey(const T& key);
		// 4.1 ������ ���������� ����������� ������ � �������� ����� out, ������������ ������, ����� �������� ��������� ������
		void print(std::ostream& out) const;
		// 5.1 ����������� ���������� ����� ������
		int getCount() const;
		// 6.1 ����������� ������ ������
		int getHeight() const;
		// 7 ��������� ����� ������ (�����������)
		void iterativeInorderWalk() const;
		// 8.1 ��������� ����� ������ (�����������)
		void inorderWalk() const;
		// 9 ����� ��������� ������ �� ������� (� ������).
		void walkByLevels() const;
		// 10 �������� �� ��� ������ ��������
		bool isSimilar(const BinarySearchTree<T>& other) const;
		// 11 ���� ���������� ����� � ���� �������� ������
		bool isIdenticalKey(const BinarySearchTree<T>& other) const;

	private:

		template <class T>
		struct Node {
			T key_; // �������� �����, ������������ � ����
			Node<T>* left_; // ��������� �� ����� ���������
			Node<T>* right_; // ��������� �� ������ ���������
			Node<T>* p_; // ��������� �� �������� !!! �� ������������

			// ����������� ����
			Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) : key_(key), left_(left), right_(right), p_(p) { }
			~Node()
			{
				if (left_ != nullptr)
				{
					delete left_;
				}
				if (right_ != nullptr)
				{
					delete right_;
				}
			}
		};

		Node<T>* root_; // ��������� �� �������� ����

		// 1.2 ������� ������ ������ ���� �� ����� � �������� ������ ������
		Node<T>* iterativeSearchNode(const T& key) const;
		// 4.2 ����������� ������� ��� ������ ����������� ������ � �������� �����
		void printNode(std::ostream& out, Node<T>* root) const;
		// 5.2 ����������� ������� ����������� ���������� ����� ������
		int getCount(const Node<T>* node) const;
		// 6.2 ����������� ������� ����������� ������ ������
		int getHeight(const Node<T>* node) const;
		// 8.2 ����������� ������� ��� ���������� ������ ����� ������.
		void inorderWalk(Node<T>* node) const;

}; // ����� ������� ������ TreeBinarySearchTree

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
	root_ = nullptr;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& scr) noexcept
{
	if (root_ == scr.root_) 
	{ 
		return this; 
	}
	std::swap(root_, scr.root_);
	return this;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree <T>&& src) noexcept
{
	if (root_ == src.root_)
	{
		return this;
	}
	std::swap(root_, src.root_);
	return this;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	if (root_ != nullptr)
	{
		delete root_;
	}
}

template <class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key) const
{
	Node<T>* curr = root_;
	while (curr != nullptr)
	{
		if (curr->key_ == key)
		{
			return true;
		}
		else if (curr->key_ > key)
		{
			curr = curr->left_;
		}
		else if (curr->key_ < key)
		{
			curr = curr->right_;
		}
	}
	return false;
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	Node<T>* curr = root_;
	while (curr != nullptr)
	{
		if (curr->key_ == key)
		{
			return curr;
		}
		else if (curr->key_ > key)
		{
			curr = curr->left_;
		}
		else if (curr->key_ < key)
		{
			curr = curr->right_;
		}
	}
	return nullptr;
}

template <class T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node<T>* newNode = new Node<T>(key);

	if (root_ == nullptr)
	{
		root_ = newNode;
	}

	else
	{
		Node<T>* curr = root_;
		while (curr != nullptr)
		{
			if (curr->key_ == key)
			{
				delete newNode;
				return false;
			}
			else if (curr->key_ > key)
			{
				if (curr->left_ == nullptr)
				{
					curr->left_ = newNode;
					newNode->p_ = curr;
					return true;
				}
				curr = curr->left_;
			}
			else if (curr->key_ < key)
			{
				if (curr->right_ == nullptr)
				{
					curr->right_ = newNode;
					newNode->p_ = curr;
					return true;
				}
				curr = curr->right_;
			}
		}
	}

	delete newNode;
	return false;
}

template <class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	Node<T>* delNode = iterativeSearchNode(key);

	if (delNode == nullptr)
	{
		return false;
	}

	else if (delNode->left_ == nullptr && delNode->right_ == nullptr)
	{
		if (delNode->p_ == nullptr)
		{
			delNode = nullptr;
			root_ = nullptr;
		}

		else if (delNode->p_->key_ > key)
		{
			delNode->p_->left_ = nullptr;
		}

		else if (delNode->p_->key_ < key)
		{
			delNode->p_->right_ = nullptr;
		}
	}

	else if (delNode->left_ == nullptr)
	{
		if (delNode->p_ == nullptr)
		{
			root_ = delNode->right_;
			delNode->right_->p_ = nullptr;
		}

		else
		{
			if (delNode->p_->key_ > key)
			{
				delNode->p_->left_ = delNode->right_;
			}

			else
			{
				delNode->p_->right_ = delNode->right_;
			}

			delNode->right_->p_ = delNode->p_;
		}
	}

	else if (delNode->right_ == nullptr)
	{
		if (delNode->p_ == nullptr)
		{
			root_ = delNode->left_;
			delNode->left_->p_ = nullptr;
		}

		else
		{
			if (delNode->p_->key_ > key)
			{
				delNode->p_->left_ = delNode->left_;
			}

			else
			{
				delNode->p_->right_ = delNode->left_;
			}
		}
	}
	
	else if (delNode->left_ != nullptr && delNode->right_ != nullptr)
	{
		Node<T>* rightMinNode = delNode->right_;
		while (rightMinNode->left_ != nullptr)
		{
			rightMinNode = rightMinNode->left_;
		}
		delNode->key_ = rightMinNode->key_;
		
		if (rightMinNode->p_ != delNode)
		{
			rightMinNode->p_->left_ = nullptr;
		}
		else
		{
			delNode->right_ = nullptr;
		}
	}
}

template <class T>
int BinarySearchTree<T>::getCount(const Node<T>* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return (1 + getCount(node->left_) + getCount(node->right_));
}

template <class T>
int BinarySearchTree<T>::getCount() const
{
	return getCount(this->root_);
}

#endif _BINARY_SEARCH_TREE_H