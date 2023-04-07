#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H
#include <iostream>


template <class T>
class BinarySearchTree
{
	public:

		BinarySearchTree();// "по умолчанию" создает пустое дерево
		BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
		BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
		BinarySearchTree <T>& operator=(const BinarySearchTree <T>& src) = delete;
		BinarySearchTree <T>& operator=(BinarySearchTree <T>&& src) noexcept;

		~BinarySearchTree();
		// 1.1 Функция поиска по ключу в бинарном дереве поиска
		bool iterativeSearch(const T& key) const;
		// 2 Вставка нового элемента в дерево: true, если элемент добавлен; false, если элемент уже был
		bool insert(const T& key);
		// 3.1 Удаление элемента из дерева, не нарушающее порядка элементов; true, если элемент удален; false, если элемента не было
		bool deleteKey(const T& key);
		// 4.1 Печать строкового изображения дерева в выходной поток out, использовать скобки, чтобы показать структуру дерева
		void print(std::ostream& out) const;
		// 5.1 Определение количества узлов дерева
		int getCount() const;
		// 6.1 Определение высоты дерева
		int getHeight() const;
		// 7 Инфиксный обход дерева (итеративный)
		void iterativeInorderWalk() const;
		// 8.1 Инфиксный обход дерева (рекурсивный)
		void inorderWalk() const;
		// 9 Обход двоичного дерева по уровням (в ширину).
		void walkByLevels() const;
		// 10 Являются ли два дерева похожими
		bool isSimilar(const BinarySearchTree<T>& other) const;
		// 11 Есть одинаковые ключи в двух деревьях поиска
		bool isIdenticalKey(const BinarySearchTree<T>& other) const;

	private:

		template <class T>
		struct Node {
			T key_; // значение ключа, содержащееся в узле
			Node<T>* left_; // указатель на левое поддерево
			Node<T>* right_; // указатель на правое поддерево
			Node<T>* p_; // указатель на родителя !!! не используется

			// Конструктор узла
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

		Node<T>* root_; // Указатель на корневой узел

		// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
		Node<T>* iterativeSearchNode(const T& key) const;
		// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
		void printNode(std::ostream& out, Node<T>* root) const;
		// 5.2 Рекурсивная функция определения количества узлов дерева
		int getCount(const Node<T>* node) const;
		// 6.2 Рекурсивная функция определения высоты дерева
		int getHeight(const Node<T>* node) const;
		// 8.2 Рекурсивная функция для инфиксного обхода узлов дерева.
		void inorderWalk(Node<T>* node) const;

}; // конец шаблона класса TreeBinarySearchTree

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