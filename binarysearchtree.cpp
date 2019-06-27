#include<iostream>
#include<queue>
#include <windows.h>
using namespace std;

typedef struct node
{
	bool from = 0;						// 0 : from left     1 : from right
	int data = 0;						// integer data
	node* right_child = NULL;			// right child
	node* left_child = NULL;			// left child
	node* parent = NULL;				// parent
}node;

bool isEmpty();
void makeEmpty();
void inOrder(node* nodeptr);
void preOrder(node* nodeptr);
void postOrder(node* nodeptr);
bool contains(int data);
void put(int data);
void del(int data);

queue<int> q;
node* rootParent = new node();

int main()
{	
	///////////////////////////////////////////
	//rootParent->left_child IS POINTING ROOT//
	///////////////////////////////////////////

	rootParent->left_child = NULL;			//root is starting from NULL
	isEmpty();
	makeEmpty();
	inOrder(rootParent->left_child);
	preOrder(rootParent->left_child);
	postOrder(rootParent->left_child);
	contains(4);
	put(20);
	put(5);
	put(24);
	put(1);
	put(4);
	put(23);
	put(27);
	put(2);
	put(21);
	put(28);
	inOrder(rootParent->left_child);
	preOrder(rootParent->left_child);
	postOrder(rootParent->left_child);
	del(5);
	inOrder(rootParent->left_child);
	preOrder(rootParent->left_child);
	postOrder(rootParent->left_child);
	del(20);
	inOrder(rootParent->left_child);
	preOrder(rootParent->left_child);
	postOrder(rootParent->left_child);
	del(-4);								//wrong number
	inOrder(rootParent->left_child);
	preOrder(rootParent->left_child);
	postOrder(rootParent->left_child);
	del(28);
	isEmpty();
	inOrder(rootParent->left_child);
	preOrder(rootParent->left_child);
	postOrder(rootParent->left_child);
	contains(5);
	contains(24);
	makeEmpty();
	isEmpty();
	contains(24);
	put(9);
	contains(9);
	put(17);
	put(45);
	put(2);
	put(21);
	isEmpty();
	preOrder(rootParent->left_child);
	put(28);
	del(17);
	put(10);
	put(10);
	del(10);
	put(10);
	inOrder(rootParent->left_child);
	system("pause");
	return 0;
}

bool isEmpty()
{
	if (rootParent->left_child == NULL)
	{
		cout << "Tree is empty\n\n";
		return true;
	}
	cout << "Tree is not empty\n\n";
	return false;
}

void makeEmpty()
{
	cout << "Tree is successfully emptied\n\n";
	rootParent->left_child = NULL;
	return;
}

void inOrder(node * ptr)
{
	//If empty, then return
	if (ptr == NULL)
	{
		cout << "Cannot traverse in Inorder   because tree is empty\n\n";
		return;
	}

	//If root, then empty queue
	if (ptr == rootParent->left_child)while (!q.empty())q.pop();

	//Traverse
	if (ptr->left_child != NULL)inOrder(ptr->left_child);
	q.push(ptr->data);
	if (ptr->right_child != NULL)inOrder(ptr->right_child);

	//Print queue
	if (ptr == rootParent->left_child)
	{
		cout << "Inorder     : ";
		while (!q.empty())
		{
			printf("%3d ", q.front());
			q.pop();
		}
		cout << "\n\n";
	}
	return;
}

void preOrder(node * ptr)
{
	//If empty, then return
	if (ptr == NULL)
	{
		cout << "Cannot traverse in Preorder  because tree is empty\n\n";
		return;
	}

	//If root, then empty queue
	if (ptr == rootParent->left_child)while (!q.empty())q.pop();

	//Traverse
	q.push(ptr->data);
	if (ptr->left_child != NULL)preOrder(ptr->left_child);
	if (ptr->right_child != NULL)preOrder(ptr->right_child);

	//Print queue
	if (ptr == rootParent->left_child)
	{
		cout << "Preorder    : ";
		while (!q.empty())
		{
			printf("%3d ", q.front());
			q.pop();
		}
		cout << "\n\n";
	}
	return;
}

void postOrder(node * ptr)
{
	//If empty, then return
	if (ptr == NULL)
	{
		cout << "Cannot traverse in Postorder because tree is empty\n\n";
		return;
	}

	//If root, then empty queue
	if (ptr == rootParent->left_child)while (!q.empty())q.pop();

	//Traverse
	if (ptr->left_child != NULL)postOrder(ptr->left_child);
	if (ptr->right_child != NULL)postOrder(ptr->right_child);
	q.push(ptr->data);

	//Print queue
	if (ptr == rootParent->left_child)
	{
		cout << "Postorder   : ";
		while (!q.empty())
		{
			printf("%3d ", q.front());
			q.pop();
		}
		cout << "\n\n";
	}
	return;
}

bool contains(int data)
{
	queue<node*> containQ;
	if (rootParent->left_child == NULL)
	{
		cout << "Cannot check "<<data<<" because tree is empty\n\n";
		return false;
	}
	containQ.push(rootParent->left_child);
	while (!containQ.empty())
	{
		node* temp = containQ.front();
		containQ.pop();
		if (temp->data == data)
		{
			cout << "Tree does contains " << data << "\n\n";
			return true;
		}
		else if (temp->data > data && temp->left_child != NULL)containQ.push(temp->left_child);
		else if (temp->data < data && temp->right_child != NULL)containQ.push(temp->right_child);
	}
	cout << "Tree does not contains "<<data<<"\n\n";
	return false;
}

void put(int data)
{
	cout << "Trying to add " << data << " \n";
	//If node is empty, create a root node
	if (rootParent->left_child == NULL) {
		node* root = new node();
		root->from = 0;
		root->data = data;
		root->right_child = NULL;
		root->left_child = NULL;
		root->parent = rootParent;
		rootParent->left_child = root;
		cout << data << " is successfully added\n\n";
		return;
	}

	queue<node*>putQ;
	putQ.push(rootParent->left_child);
	while (!putQ.empty())
	{
		node* temp = putQ.front();
		putQ.pop();
		if (temp->data == data)
		{
			cout << "There is already " << data << " in tree\n\n";
			return;
		}
		else if (temp->data > data && temp->left_child != NULL)putQ.push(temp->left_child);
		else if (temp->data < data && temp->right_child != NULL)putQ.push(temp->right_child);
		else if (temp->data > data && temp->left_child == NULL)
		{
			node* newNode = new node();
			newNode->from = 0;
			newNode->data = data;
			newNode->left_child = NULL;
			newNode->right_child = NULL;
			newNode->parent = temp;
			temp->left_child = newNode;
			cout << data <<" is successfully added\n\n";
			return;
		}

		else if (temp->data < data && temp->right_child == NULL)
		{
			node* newNode = new node();
			newNode->from = 1;
			newNode->data = data;
			newNode->left_child = NULL;
			newNode->right_child = NULL;
			newNode->parent = temp;
			temp->right_child = newNode;
			cout << data << " is successfully added\n\n";
			return;
		}
	}
}

void del(int data)
{
	cout << "Trying to delete " << data << " \n";
	queue<struct node*>delQ;
	if (rootParent->left_child == NULL)
	{
		cout << "Cannot delete "<< data <<" because tree is empty\n\n";
		return;
	}
	delQ.push(rootParent->left_child);
	while (!delQ.empty())
	{
		node* temp = delQ.front();
		delQ.pop();
		if (temp->data == data)
		{
			cout << data << " is successfully deleted\n\n";
			if (temp->right_child == NULL && temp->left_child == NULL)
			{
				if (temp->from == 0) temp->parent->left_child = NULL;
				if (temp->from == 1) temp->parent->right_child = NULL;
			}
			else if (temp->right_child == NULL && temp->left_child != NULL)
			{
				if (temp->from == 0)
				{
					temp->parent->left_child = temp->left_child;
					temp->left_child->from = 0;
				}
				else if (temp->from == 1)
				{
					temp->parent->right_child = temp->left_child;
					temp->left_child->from = 1;
				}
			}
			else if (temp->right_child != NULL && temp->left_child == NULL)
			{
				if (temp->from == 0)
				{
					temp->parent->left_child = temp->right_child;
					temp->right_child->from = 0;
				}
				else if (temp->from == 1)
				{
					temp->parent->right_child = temp->right_child;
					temp->right_child->from = 1;
				}
			}
			else if (temp->right_child != NULL && temp->left_child != NULL)
			{
				node* tempp = temp->left_child;
				while (tempp->right_child != NULL)tempp = tempp->right_child;
				if (tempp->from == 0)
				{
					tempp->parent->left_child = tempp->left_child;
					if (tempp->left_child != NULL)tempp->left_child->from = 0;
				}
				else if (tempp->from == 1)
				{
					tempp->parent->right_child = tempp->left_child;
					if (tempp->left_child != NULL)tempp->left_child->from = 1;
				}
				temp->data = tempp->data;
			}
			return;
		}
		else if (temp->data > data && temp->left_child != NULL)delQ.push(temp->left_child);
		else if (temp->data < data && temp->right_child != NULL)delQ.push(temp->right_child);
	}
	cout << "There is no " << data << " in tree to delete\n\n";
}
