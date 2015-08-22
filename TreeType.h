//  Raza Rauf
//  TreeType.h
//  Binary Tree project
//
//  Impements the TreeType class with data members and member functions
//

//  Please note that I developed this program using the Apple G++ compiler (LLVM version 6.1.0).
//  The compiler does not allow me to have a separate header and implementation file when
//  implementing a generic (template) type class.

#include <iostream>
#include <list>

using namespace std;

struct TreeNode
{
    int info;
    TreeNode *left;
    TreeNode *right;
};

#ifndef ____TreeType__
#define ____TreeType__

template <class ItemType>
class TreeType
{
public:
    //Default class constructor
    TreeType();
    //Default class destructor
    ~TreeType();
    void InsertItem(ItemType item);
    void FindNode(TreeNode* tree, ItemType item, TreeNode*& nodePtr, TreeNode*& parentPtr);
    void DeleteItem(ItemType item);
    void Delete(TreeNode*& tree, ItemType item);
    void DeleteNode(TreeNode*& tree);
    void GetPredecessor(TreeNode* tree, ItemType& data);
    bool IsFull() const;  //Not used
    bool IsEmpty() const; //Not used
    int LengthIs() const;
    ItemType RetrieveItem(ItemType& item, bool& found);
    void Retrieve(TreeNode* tree, ItemType& item, bool& found);
    int CountNodes(TreeNode* tree);
    void Destroy(TreeNode*& tree);
    void showHelper ( TreeNode *p,int level) const;
    void showStructure () const;
    ItemType midNodeHelp(TreeNode* tree);
    ItemType midNode();
    void OrderList(TreeNode* tree, list<ItemType>& TreeList);
    bool SimilarTreesHelp(TreeType& t);
    bool SimilarTrees(TreeNode* tree1, TreeNode* tree2);
    void checkNodes(TreeNode* tree1, TreeNode* tree2, bool& flag);
    
private:
    TreeNode* root;
};

#endif 
/* defined(____TreeType__) */

template <class ItemType>
TreeType<ItemType>::TreeType()
//Constructor
{
    root=NULL;
}

template <class ItemType>
TreeType<ItemType>::~TreeType()
//Destructor
{
    Destroy(root);
}

template <class ItemType>
void TreeType<ItemType>::Destroy(TreeNode*& tree)
//Destructor helper
{
    if (tree != NULL)
    {
        Destroy(tree->left);
        Destroy(tree->right);
        delete tree;
    }
}

template <class ItemType>
void TreeType<ItemType>::FindNode(TreeNode* tree, ItemType item, TreeNode*& nodePtr, TreeNode*& parentPtr)
//Finds a certain node, used by InsertItem
{
    nodePtr = tree;
    parentPtr = NULL;
    bool found = false;
    while (nodePtr != NULL && !found)
    { if (item < nodePtr->info)
    {
        parentPtr = nodePtr;
        nodePtr = nodePtr->left;
    }
    else if (item > nodePtr->info)
    {
        parentPtr = nodePtr;
        nodePtr = nodePtr->right;
    }
    else found = true;
    }
}

template <class ItemType>
void TreeType<ItemType>::InsertItem(ItemType item)
//Inserts a new node
{
    TreeNode* newNode;
    TreeNode* nodePtr;
    TreeNode* parentPtr;
    newNode = new TreeNode;
    newNode->info = item;
    newNode->left = NULL;
    newNode->right = NULL;
    FindNode(root, item, nodePtr, parentPtr);
    if (parentPtr == NULL)
        root = newNode;
    else if (item < parentPtr->info)
        parentPtr->left = newNode;
    else parentPtr->right = newNode;
}

template <class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
//Deletes the node
{
    TreeNode* nodePtr;
    TreeNode* parentPtr;
    FindNode(root, item, nodePtr, parentPtr);
    if (nodePtr != NULL)
        Delete(nodePtr, item);
    else
        cout << "Item does not exist." << endl;
}

template <class ItemType>
void TreeType<ItemType>::Delete(TreeNode*& tree, ItemType item)
//DeleteItem helper
{
    if (item < tree->info)
        Delete(tree->left, item);
    else if (item > tree->info)
        Delete(tree->right, item);
    else
        DeleteNode(tree);  // Node found
}

template <class ItemType>
void TreeType<ItemType>::DeleteNode(TreeNode*& tree)
//Delete helper
{
    ItemType data;
    TreeNode* tempPtr;
    tempPtr = tree;
    if (tree->left == NULL) {
        tree = tree->right;
        delete tempPtr; }
    else if (tree->right == NULL){
        tree = tree->left;
        delete tempPtr;}
    else{
        GetPredecessor(tree->left, data);
        tree->info = data;
        Delete(tree->left, data);}
}
template <class ItemType>
void TreeType<ItemType>::GetPredecessor(TreeNode* tree, ItemType& data)
//Delete helper
{
    while (tree->right != NULL)
        tree = tree->right;
    data = tree->info;
}

template <class ItemType>
bool TreeType<ItemType>::IsFull() const
//Checks whether there is enough memory to add another node
{
    TreeNode* location;
    try
    {
        location = new TreeNode;
        delete location;
        return false;
    }
    catch(bad_alloc exception)
    {
        return true;
    }
}

template <class ItemType>
bool TreeType<ItemType>::IsEmpty() const
//Checks whether the tree is empty
{
    return root == NULL;
}

template <class ItemType>
int TreeType<ItemType>::LengthIs() const
//Returns the number of nodes in the tree
{
    return CountNodes(root);
}

template <class ItemType>
int TreeType<ItemType>::CountNodes(TreeNode* tree)
// Recursive function that counts the nodes
{
    if (tree == NULL)
        return 0;
    else
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template <class ItemType>
ItemType TreeType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
    Retrieve(root, item, found);
    return item;
}

template <class ItemType>
void TreeType<ItemType>::Retrieve(TreeNode* tree, ItemType& item, bool& found)
{
    if (tree == NULL)
        found = false;
    else if (item < tree->info)
        Retrieve(tree->left, item, found);
    else if (item > tree->info)
        Retrieve(tree->right, item, found);
    else
    {
        item = tree->info;
        found = true;
    }
}

template <class ItemType>
ItemType TreeType<ItemType>::midNode()
//Find the middle node of the Binary Tree structure
{
    return midNodeHelp(root);
}

template <class ItemType>
ItemType TreeType<ItemType>::midNodeHelp(TreeNode* tree)
//midNode helper
{
    list<ItemType> TreeList;
    OrderList(tree, TreeList);
    int sizeOfTree = TreeList.size();
    int midPoint = (sizeOfTree+1)/2;
    int i=1;
    while(i<midPoint)
    {
        TreeList.pop_front();
        i++;
    }
    ItemType mid = TreeList.front();
    return mid;
}

template <class ItemType>
void TreeType<ItemType>::OrderList(TreeNode* tree, list<ItemType>& TreeList)
{
    if (tree != NULL)
    {
        //Inorder
        OrderList(tree->left,TreeList);
        TreeList.push_back(tree->info);
        OrderList(tree->right,TreeList);
    }
}

template <class ItemType>
bool TreeType<ItemType>::SimilarTreesHelp(TreeType& t)
//Determines whether the shapes of the trees are the same.
{
    return SimilarTrees(root, t.root);
}

template <class ItemType>
bool TreeType<ItemType>::SimilarTrees(TreeNode* tree1, TreeNode* tree2)
//SimilarTreesHelp helper
{
    ItemType numofnodes1=0;
    ItemType numofnodes2=0;
    bool flag=true;
    
    numofnodes1 = CountNodes(tree1);
    numofnodes2 = CountNodes(tree2);
    
    //First check if the number of nodes are same
    if(numofnodes1!=numofnodes2)
        return false;
    //If number of nodes don't equal -> check the shape of both trees
    else
    {
        checkNodes(tree1, tree2, flag);
        if(flag)
            return true;
        else
            return false;
    }
}

template <class ItemType>
void TreeType<ItemType>::checkNodes(TreeNode* tree1, TreeNode* tree2, bool& flag)
//Compares whether each node of tree1 exists at the same place as tree2
{
    //Check if left node exists for both trees
    if((tree1->left!=NULL) && (tree2->left!=NULL))
        //If the left nodes exist, advance to the left
        checkNodes(tree1->left, tree2->left, flag);
    //If left node for one tree exists and left node for the other doesn't
    // => the trees are different -> Set flag to false
    else if((tree1->left!=NULL) || (tree2->left!=NULL))
        flag=false;
    
    //Same algorithm as left applies to right node check
    if((tree1->right!=NULL) && (tree2->right!=NULL))
        checkNodes(tree1->right, tree2->right, flag);
    else if((tree1->right!=NULL) || (tree2->right!=NULL))
        flag=false;
}

template <class ItemType>
void TreeType<ItemType>:: showStructure () const
//Prints out the tree structure with the help of showHelper
{
    if (root == NULL)
        cout << "Empty tree" << endl;
    else
    {
        cout << endl;
        showHelper(root,1);
        cout << endl;
    }
}

template <class ItemType>
void TreeType<ItemType>::showHelper (TreeNode *p, int level) const
//showStructure function helper
//Recursively outputs the tree structure
{
    int j;   // Loop counter
    
    if ( p != 0 )
    {
        //keeps going all the way to right recursively until reaches the leaf node
        showHelper(p->right,level+1);
        
        //count how many level down and add space
        for ( j = 0 ; j < level ; j++ )
            cout << "\t";
        //output the node's data
        cout << " " << p->info;
        
        if ((p->left != 0) && (p->right != 0))
            cout << "<";
        else if ( p->right != 0 )
            cout << "/";
        else if ( p->left != 0 )
            cout << "\\";
        cout << endl;
        
        //once p->right is null, the recursion breaks and outputs each left
        //node of the current position recursively
        showHelper(p->left,level+1);
    }
}

