#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
   protected:
    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data> *root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

   public:
    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
        Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** Default destructor.
        Delete every node in this BST.
     */
    // TODO ok
    virtual ~BST() {
	deleteAll(root);
	isize=0;
	iheight=0;
    }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO ok
    virtual bool insert(const Data &item) {
	int cur_height=0;
	BSTNode<Data> *cur=root;
	BSTNode<Data> *parent=nullptr;
	while(cur){
		parent=cur;
		cur_height++;
		if(cur->data < item){cur=cur->right;}
		else if(item < cur->data){cur=cur->left;}
		else return false;
	}
	cur=new BSTNode(item);
	cur->parent=parent;
	isize++;
	iheight=max(iheight,cur_height+1);
	return true;
    }

    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO 
    virtual iterator find(const Data &item) const {
	BSTNode<Data> *cur=root;
	while(cur){
		if(cur->data<item)cur=cur->right;
		else if(item<cur->data)cur=cur->left;
		else{
			iterator tmp(cur);
			return tmp;
		}
	}
	iterator tmp(nullptr);
	return tmp;
    }

    /** Return the number of items currently in the BST.
     */
    // TODO ok
    unsigned int size() const {return isize;}

    /** Return the height of the BST.
     */
    // TODO ok
    unsigned int height() const {return iheight;}

    /** Return true if the BST is empty, else false.
     */
    // TODO ok
    bool empty() const {
	if(root)return false;
	return true;
    }
    /** Return an iterator pointing to the first item in the BST (not the root).
     */
    // TODO ok
    iterator begin() const {
	if(!root){
		iterator tmp(nullptr);
		return tmp;
	}
	BSTNode<Data>* cur=root;
	while(cur->left){
		cur=cur->left;
	}
	iterator tmp(cur);
	return tmp;
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Perform an inorder traversal of this BST.
     */
    void inorder() const { inorder(root); }

   private:
    /** Recursive inorder traversal 'helper' function */

    /** Inorder traverse BST, print out the data of each node in ascending
       order. Implementing inorder and deleteAll base on the pseudo code is an
       easy way to get started.
     */
    // TODO ok
    void inorder(BSTNode<Data> *n) const {
        /* Pseudo Code:
          if current node is null: return;
          recursively traverse left sub-tree
          print current node data
          recursively traverse right sub-tree
        */
	if(!n)return;
	inorder(n->left);
	cout << n << '\n';//format?
	inorder(n->right);
    }

    /** Find the first element of the BST
     */
    static BSTNode<Data> *first(BSTNode<Data> *curr) {
        if (curr == 0) return 0;
        while (curr->left != 0) curr = curr->left;
        return curr;
    }

    /** do a postorder traversal, deleting nodes
     */
    // TODO ok
    static void deleteAll(BSTNode<Data> *n) {
        /* Pseudo Code:
          if current node is null: return;
          recursively delete left sub-tree
          recursively delete right sub-tree
          delete current node
        */
	if(!n)return;
	deleteAll(n->left);
	deleteAll(n->right);
	free(n);
    }
};

#endif  // BST_HPP
