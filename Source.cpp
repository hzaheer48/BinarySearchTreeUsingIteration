#include<iostream>
#include<queue>
using namespace std;
template<typename T>
struct node {
	T data;
	node<T>* right;
	node<T>* left;
};
//iterator function of BST
template<typename T>
void traverse_level(node<T>* ptr, queue<T>& q)
{
	queue<node<T>*>temp_q;
	temp_q.push(ptr); //pushing first node address in temp_q
	while (!temp_q.empty())
	{
		node<T>* temp;
		temp = temp_q.front();
		temp_q.pop();
		q.push(temp->data); //pushing values level wise
		if (temp->left != NULL) //pushing address of left child node of root node if exists
		{
			temp_q.push(temp->left);
		}
		if (temp->right != NULL)  //pushing address of left right node of root node if exists
		{
			temp_q.push(temp->right);
		}
	}
}
//for copy costructor and assignment operator
template<typename T>
void copy_tree(node<T>* ptr, node<T>*& dest)
{
	if (ptr == NULL)
	{
		dest = NULL;
	}
	else
	{
		queue<T>q;
		queue<node<T>*>temp_q;
		temp_q.push(ptr); //pushing first node address in temp_q
		while (!temp_q.empty())
		{
			node<T>* temp;
			temp = temp_q.front();
			temp_q.pop();
			q.push(temp->data); //pushing values level wise
			if (temp->left != NULL) //pushing address of left child node of root node if exists
			{
				temp_q.push(temp->left);
			}
			if (temp->right != NULL)  //pushing address of left right node of root node if exists
			{
				temp_q.push(temp->right);
			}
		}
		while (!q.empty())
		{
			insert_iterative(dest, q.front()); //inserting in order
			q.pop();
		}
	}
}
template<typename T>
void insert_iterative(node<T>*& ptr, const T& val)
{
	node<T>* temp;
	temp = new node<T>;
	temp->data = val;
	temp->left = temp->right = NULL;
	if (ptr == NULL)
	{
		ptr = temp; //if value is to be inserted in empty BST
	}
	else
	{
		node<T>* temp2 = ptr;
		while (true)
		{
			if (val < temp2->data) //moving left if value to be inserted is smaller then current value
			{
				if (temp2->left == NULL) //when proper location of value is reached
				{
					temp2->left = temp;
					return;
				}
				else
				{
					temp2 = temp2->left;
				}
			}
			else if (val > temp2->data) //moving right if desired value is greater then current value
			{
				if (temp2->right == NULL)  //when proper location of value is reached
				{
					temp2->right = temp;
					return;
				}
				else
				{
					temp2 = temp2->right;
				}
			}
			else
			{
				cout << "Trying to add duplicate value" << endl;
				break;
			}
		}
	}
}
template<typename T>
class BST {
	node<T>* root;
	queue<T> q;
	node <T>* find_ptr(const T& val) //function to find address of node which contains desired value
	{
		node<T>* temp = root; //starting to search from root
		while (temp != NULL && temp->data != val) //will terminate this loop if temp is reached to NULL												//or desired value is found
		{
			if (val < temp->data)	//moving left if desired value is smaller then current value
			{
				temp = temp->left;
			}
			else //moving right if desired value is greater then current value
			{
				temp = temp->right;
			}
		}
		return temp; //will return null if no value is found
	}
	node<T>* func(const T& val) //function to get address of parent node of any node whose value is passed
								// parent node of root node will be itself
	{
		node<T>* temp1, * temp2;
		temp1 = temp2 = root; //starting from root
		if (root != NULL)
		{
			while (temp1 != NULL && temp1->data != val)
			{
				if (val < temp1->data) //moving left if desired value is smaller then current value
				{
					temp2 = temp1; //temp2 will always be one step behind then temp1
									//i.e. at parent node of its children
									//temp2 pointing at parent 
									//temp1 pointing at children(either left or right)
					temp1 = temp1->left;
				}
				else if (val > temp1->data)//moving right if desired value is greater then current value
				{
					temp2 = temp1;//temp2 will always be one step behind then temp1
									//i.e. at parent node of its children
									//temp2 pointing at parent 
									//temp1 pointing at children(either left or right)
					temp1 = temp1->right;
				}
			}
			return temp2; //returning address of parent node
		}
		else
		{
			return NULL;
		}

	}
	node<T>* prdecessor(const T& val) //function to get address of predecessor whose value is passed
	{
		node<T>* temp1 = root;
		node<T>* temp2 = NULL;
		while (temp1 != NULL && temp1->data != val) //getting at location of value whose predecessor is to be found
		{
			if (val < temp1->data) //moving left if desired value is smaller then current value
			{
				temp1 = temp1->left;
			}
			else //moving right if desired value is greater then current value
			{
				temp2 = temp1; //temp2 pointing at parent of child in right node
				temp1 = temp1->right;
			}
		}
		if (temp1 != NULL && temp1->left != NULL) //if left subtree exists where value is located												
												  // right most value of its left subtree will be its predecessor
		{
			temp1 = temp1->left;
			while (temp1->right != NULL)
			{
				temp1 = temp1->right;
			}
			temp2 = temp1;
		}
		//if left subtree doesn't exist,temp2 is already pointing at its predecessor
		return temp2;
	}
public:
	BST()
	{
		root = NULL;
	}
	~BST()
	{
		make_empty();
	}
	BST(BST<T>& src)
	{
		copy_tree(src.root, root);
	}
	void operator=(const BST<T>& src)
	{
		make_empty;
		copy_tree(src.root, root);
	}
	void insert(const T& val)
	{
		insert_iterative(root, val);
	}
	bool find(const T& val)
	{
		node<T>* temp = find_ptr(val);
		if (temp != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool erase(const T& val)
	{
		node<T>* n = find_ptr(val);
		if (n == NULL) //if value is not in BST
		{
			return false;
		}
		if (n->left == NULL && n->right == NULL) //erasing a leaf node
		{
			if (n->data == root->data) //if root node is also leaf node
			{
				delete n;
				root = NULL;
				return true;
			}
			node<T>* temp = func(val); //getting parent node of node which contains value
			if (temp->left != NULL) //to control exception
			{
				if (temp->left->data == n->data)  //if val is in left child node of parent node
				{
					delete n;
					temp->left = NULL; //making parent's node left part null
				}
			}
			else //if val is not in left child node of parent node,then its obviously in its right child
			{
				delete n;
				temp->right = NULL; //making parent's node right part null
			}
			return true;
		}
		if (n->left != NULL && n->right == NULL) //if node containing value has only children at left
		{
			node<T>* temp = func(val); //getting parent node of node which contains value
			if (root->data == val) //if root node has value to be erased and root node only has children in 
									//its left part
			{
				root = root->left;
				delete temp;
				return true;
			}
			if (temp->left != NULL)//to control an exception
			{
				if (temp->left->data == n->data) //if val is in left child node of parent node
				{
					temp->left = n->left; //storing address held in child's left part in parent's left part
				}
			}
			else // if val is not in left child node of parent node, then its obviously in its right child
			{
				temp->right = n->left; //storing address held in child's left part in parent's right part
			}
			delete n;
			return true;
		}
		if (n->right != NULL && n->left == NULL) //if node containing value has only children at right
		{
			node<T>* temp = func(val); //getting parent node of node which contains value
			if (root->data == val)//if root node has value to be erased and root node only has children in 
									//its right part
			{
				root = root->right;
				delete temp;
				return true;
			}
			if (temp->right != NULL) //to control an exception
			{
				if (temp->right->data == n->data) //if val is in right child node of parent node
				{
					temp->right = n->right; //storing address held in child's right part in parent's right part
				}
			}
			else
			{
				temp->left = n->right; //storing address held in child's right part in parent's left part
			}
			delete n;
			return true;
		}
		if (n->left != NULL && n->right != NULL) //if node containing has children at both end
		{
			node<T>* temp1 = prdecessor(val); //temp1 will point towards the node containig predecessor of 
												//value to be erased
			node<T>* temp2 = func(temp1->data); // temp2 will point towards the parent node of node cotaining predecessor of value to
												//to be erased.
			n->data = temp1->data; //overwriting data to be erased with its predecessor
			if (n->left->data == temp1->data) //if predecessor is in very left node of node containing value to be erased
			{
				n->left = temp1->left; //connecting nodes i.e storing address held in left part of predecessor node
										//in node's left part which is overwritten by predecessor
				delete temp1;
				return true;

			}
			else//if predecessor is not in very left node of node containing value to be erased
				//then its in right most node of left subtree of node containing value to be erased	
			{
				temp2->right = temp1->left; //connecting nodes i.e parent node(right part) of predecessor with child node of
											//predecessor(if exist any else it will NULL the parent node right part). 
				delete temp1;
				return true;
			}
		}
	}
	void make_empty()
	{
		while (root != NULL)
		{
			erase(root->data);
		}
	}
	void reset()
	{
		q = queue<T>();
		traverse_level(root, q);
	}
	bool is_last()
	{
		return q.empty();
	}
	T get_next()
	{
		if (is_last())
		{
			throw "Last value reached";
		}
		T val;
		val = q.front();
		q.pop();
		return val;
	}

};