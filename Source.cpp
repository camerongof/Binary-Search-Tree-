// write a program using the binarry search tree data structure

//TODO: bug in remove(). The function works but when display is called program breaks where an item was removed, elements possible not linking where needed after removal

#include <iostream>
#include <stack>

using namespace std;

class Node 
{
public: 
	int data;
	Node* right;
	Node* left;
	Node(int data)// constructor for the Node class, sets up data and pointers for left and right
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

class BST
{
private:
	Node* root;
public:
	BST()// constructor to setup the root node
	{
		root = NULL;
	}

	void insert(int data)
	{
		Node* newNode = new Node(data); //creating a new node that is holding the value data. Assigning the new creation Node to Node newNode
		Node* temp = root;
		Node* trail = NULL;

		// check to see if the tree is empty
		if (root == NULL)
		{
			root = newNode;
			return;
		}

		while (temp != NULL)// while loop for traversal, as long as temp is not at a leaf node, temp will move its way down the tree
		{
			trail = temp;
			if (data < temp->data) // if the data for insert is less than the current node's value
			{
				temp = temp->left; // move to the left child
			}
			else if (data > temp->data) // if the data for insert is greater than the current node's value
			{
				temp = temp->right; // move to the right child
			}
			else if (data == temp->data) // case for when the data already exists in the tree
			{
				return;
			}
		}

		//newNode = temp; // setting the new Node to temp after the traversal

		if (data < trail->data) // the trail will follow temp down the tree to the correct level or step. once theabove loop is done, trail should be at a leaf node
			// here we can use the same traversal operation to determine which child should hold the newNode
		{
			trail->left = newNode;
		}
		else if (data > trail->data)
		{
			trail->right = newNode;
		}
	}

	void remove(int data) // delete function
	{
		Node* temp = root;
		Node* trail = NULL;

		// check to see if the tree is empty
		if (root == NULL)
		{
			cout << "The tree is empty!\n";
			return;
		}

		while (temp != NULL)// while loop for traversal, as long as temp is not at a leaf node, temp will move its way down the tree
		{
			trail = temp; // follower will always be the parent of temp if temp is not root
			if (data < temp->data) // if the data for insert is less than the current node's value
			{
				temp = temp->left; // move to the left child
			}
			else if (data > temp->data) // if the data for insert is greater than the current node's value
			{
				temp = temp->right; // move to the right child
			}
			else if (data == temp->data) // case for when the data is located in the tree
			{
				if (temp->left == NULL && temp->right == NULL) // this checks if temp at current position is a leaf. Meaning no children
				{
					cout << "Deleting leaf data value: " << temp->data << endl;
					if (trail->left == temp) // disconnecting the link between temp and its trail
					{
						trail->left = NULL;
					}
					else
					{
						trail->right = NULL;
					}
					free(temp);
					return;
				}
				else if (temp->left == NULL || temp->right == NULL) // this case assumes the node for deletion has at most one child
				{
					cout << "Deleting data value: " << temp->data << ".This node has a child.\n";
					if (temp->left != NULL && data < root->data) // if temp's left child is not NULL and the data meant for deletion is on the left side of the tree
					{
						trail->left = temp->left;
					}
					else if (temp->left != NULL && data > root->data) //if temps left child is not NULL and the data meant for deletion is on the right side of the tree
					{
						trail->right = temp->left;
					}
					else if (temp->right != NULL && data < root->data) // if temp's right child is not NULL and the data meaant for deletion is on the left side of the tree
					{
						trail->left = temp->right;
					}
					else if(temp-> right != NULL && data > root ->data) // if temp's right child is not NULL and the data meant for deletion is on the right side of the tree
					{
						trail->right = temp->right;
					}

					free(temp);
					return;
				}
				// case for when the node for deletion has two children 
				else
				{
					cout << "Deleting data value: " << temp->data << ". This node has two children.\n";
					// have to take the delted node's children and re assign them
					//case for right side
					Node* t = temp->right;
					if (t->left == NULL && t->right == NULL) // if temp's right child is a leaf. (No Children)
					{
						temp->data = t->data; // taking the right child's value and reassigning it to temp, 'deleting' temp's original value
						temp->right = NULL; // disconnecting temp's right child
						free(t);
						return;
						// after this operation, temp's left child is still preserved. temp wasn't deleted, its value just changed so the link to the left child still exists
					}
					else if (t->left == NULL && t->right != NULL) // if temp's right child is not a leaf and has a child
					{
						temp->data = t->data; // taking the right child's value and reassigning it to temp, 'deleting' temp's original value
						temp->right = t->right; // linking temp's right child to t's right child
						free(t);
						return;
					}
					// I think the below while is flawed
					while (t->left != NULL)// very convoluted, while t's, (temp's right child at this point), left child exists
					{
						trail = t; // temp's follower, trail now holds t
						t = t->left;// t now holds its left child's value
					}
					temp->data = t->data; // assuming the above not flawed, t does not have a child here, temp now holds t's data
					trail->left = NULL; // again assuming but if I'm correct, after running, in the case that a lower data value exists as sibiling or above temp
					// then we drop it
					free(t);
					return;
				}
				return;
			}
		}

	}

	bool lookup(int data)
	{
		if (root == NULL)
		{
			cout << "The tree is empty!\n";
			return false;
		}

		Node* temp = root;

		while (temp != NULL)
		{
			if (data < temp->data) // if the data for lookup is less than the current node's value
			{
				temp = temp->left; // move to the left child
			}
			else if (data > temp->data) // if the data for lookup is greater than the current node's value
			{
				temp = temp->right; // move to the right child
			}
			else if (data == temp->data) // case for when the data is found in the tree
			{
				cout << "Found data value: " << temp->data << endl;
				return true;
			}
			else
			{
				cout << "Data is not in the tree\n";
				return false;
			}
		}
	}

	void display()
	{
		//function will display the contents of the tree in order (values least to greatest) on a single line using stacks
		// take it slow, this explain is a little insane

		stack<Node*>st; // intializing stack to hold Nodes (including pointers to left and right)
		Node* temp = root; // setup for traversal

		while (temp != NULL || !st.empty()) // while temp is not NULL (not past a leaf node) OR the stack st is not empty
		{
			while (temp != NULL) //while temp is not NULL (not past a leaf node)
			{
				st.push(temp); // pushing temp's current node into the stack, 
				temp = temp->left; //this will be left oriented first
			}
			// breaking out the loop means that temp is now at null past a leaf or is on its return journey for the leaf's sibiling

			temp = st.top(); // reassigning temp from NULL to the top of the stack which should be the latest node pushed
			cout << temp->data << " "; // printing the node
			st.pop(); // deleting the top most node (not always the latest node) from the stack

			temp = temp->right; //whatever node temp was at during the print, we now travel to that node's right child, either NULL or actual child node

			/*Can follow along if you create an arbitray BST on paper, temp starts at root, at 2nd while loop's first full run,the stack will hold root and all left most
			values. Subseuent runs will pop the tops and push in right sibilings fo each step of the tree before getting back to the root, where it will then go through 
			the right side (left most right side)and continue the process */
		}
		cout << endl;
	}
};

int main()
{
	BST tree;

	tree.insert(9);
	tree.insert(4);
	tree.insert(6);
	tree.insert(20);
	tree.insert(170);
	tree.insert(15);
	tree.insert(1);

	tree.display();

	tree.remove(6);

	tree.lookup(15);

	tree.display();

	system("pause");
	return 0;
}