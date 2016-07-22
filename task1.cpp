#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
struct Node{
	string name;
	string id;
	int height;
	Node* left;
	Node* right;
}; 

Node* createNode( string name, string id, Node* l = NULL, Node* r = NULL){
  Node* result = new Node;
  result->name = name;
  result->height = 0;
  result->id = id;
  result->left = l;
  result->right = r;
  return result;
}

int height( Node * x ) {
  // Returns the height of node x or -1 if x is NULL.
  if( x == NULL ) return -1;
  return x->height;
}

bool updateHeight( Node * x ) {
  //
  // Recalculates the height of x from the height of its children.
  // Returns true iff the height of x changes.
  //
  if( x == NULL ) return false;
  int m = std::max(height(x->left), height(x->right)) + 1;
  if( x->height != m ) {
    x->height = m;
    return true;
  }
  return false;
}

void rotateLeft( Node *& b ) {
  Node * a = b->left;
  b->left = a->right;
  a->right = b;
  updateHeight(b);
  updateHeight(a);
  b = a;
}

void rotateRight( Node *& a ) {
  Node * b = a->right;
  a->right = b->left;
  b->left = a;
  updateHeight(a);
  updateHeight(b);
  a = b;
}

void doubleRotateLeft( Node *& c ) {
  rotateRight(c->left);
  rotateLeft(c);
}

void doubleRotateRight( Node *& a ) {
  rotateLeft(a->right);
  rotateRight(a);
}

void balance( Node *& x ) {
  //
  // Check if node x is unbalanced (i.e., the heights of its
  // two children differ by more than one).  If it is, rebalance
  // at x using one of rotateLeft, rotateRight, doubleRotateLeft,
  // or doubleRotateRight, whichever is appropriate.
  //
  if( x == NULL ) return;
  int b = height(x->left) - height(x->right);
  if( b >= -1 && b <= 1 ) return;
  if( b == 2 ) {
    if( height(x->left->left) > height(x->left->right) ) {
      rotateLeft(x);
    } else {
      doubleRotateLeft(x);
    }
  } else {
    if( height(x->right->right) > height(x->right->left) ) {
      rotateRight(x);
    } else {
      doubleRotateRight(x);
    }
  }
}

void insert( string name, string id, Node *& root ) {
  //
  // Insert name into the AVL tree rooted at root.
  // Restore balance if required.
  //
  if( root == NULL ) {
    root = createNode(name, id);
    return;
  }
  char* n = (char*) name.data();
  char*rn = (char*) root->name.data();
  if( strcmp(n, rn) < 0 ) {
    insert( name, id, root->left );
  } else {
    insert( name, id, root->right );
  }
  if( updateHeight(root) ) balance(root);
}

bool find_id (string name, Node * root){
 	if(root == NULL) return false;
	char*n = (char*) name.data();
	char*rn = (char*) root->name.data();
	if( strcmp(n, rn) < 0 )
		return find_id( name, root->left);
	else if (strcmp(n, rn) > 0)
		return find_id(name, root->right);
	else
		return true;
}

int main(int argc, char* argv[]){
	Node* T = NULL;
	ifstream f1(argv[1]);		
	ifstream f2(argv[2]);
	ofstream f3(argv[3]);
	ofstream no(argv[4]);
	string word, word2;
	while(f1 >> word){		
		string n1 = word;
		f1 >> word;
		f1 >> word;
		f1 >> word;
		string id1 = word;	
		insert(n1, id1, T);
	}
	while(f2 >> word2){
		string n2 = word2;
		if( (find_id(n2, T)) == true){
			f3 << word2 << " ";
			f2 >> word2;
			f3 << word2 << " ";
			f2 >> word2;
 			f3 << word2 << endl;
		}else{
			no << word2 << " ";
			f2 >> word2;
			no << word2 << " ";
			f2 >> word2;
 			no << word2 << endl;	
		}
	}
	f1.close();
	f2.close();
	f3.close();
	no.close();
	return 0;
}
