
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"
#define DEBUG 1

// Node constructor, given.
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

// twoDtree destructor, given.
twoDtree::~twoDtree(){
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


// twoDtree assignment operator, given.
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){ 
	stats s(imIn);
	width = imIn.width();
	height = imIn.height();
	root = buildTree(s,pair<int, int>(0,0), pair<int,int>(width-1,height-1), true);
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {
	cout <<"ul : lr -- "<<ul.first<< "." <<ul.second<<" : "<<lr.first<<"."<<lr.second<< " -- vert: " << vert << endl; 
	Node * returnNode = new Node(ul, lr, s.getAvg(ul,lr));

	if (ul.first == lr.first && ul.second == lr.second){
		returnNode->left = NULL;
		returnNode->right = NULL;
		return returnNode;
	}

	long minVar = INT_MAX;
	int minVarSplit = 0;
	if((vert && ul.first != lr.first) || (ul.second == lr.second) ){
		for(int i = ul.first; i < lr.first; i++){
			if( abs(s.getScore(ul, pair<int,int>(i,lr.second)) - 
					s.getScore(pair<int, int> (i+1, ul.second), lr)) < minVar){
						
				minVar = abs(s.getScore(ul, pair<int,int>(i,lr.second)) - 
							s.getScore(pair<int, int> (i+1, ul.second), lr));
				minVarSplit = i;				
			}
		}
		//assign subtrees
		returnNode->left = buildTree(s, ul, pair<int, int>(minVarSplit,lr.second), !vert);
		returnNode->right = buildTree(s, pair<int, int>(minVarSplit+1, ul.second), lr, !vert);
				
		return returnNode;
	
	} else if (!vert || (ul.first == ul.first) ){
		for(int i = ul.second; i < lr.second; i++){
			if( abs(s.getScore(ul, pair<int,int>(lr.first, i)) - 
					s.getScore(pair<int,int>(ul.first, i + 1), lr)) < minVar){
				
				minVar = abs(s.getScore(ul, pair<int,int>(lr.first, i)) - 
							s.getScore(pair<int,int>(ul.first, i + 1), lr));
				minVarSplit = i; 
			}
		}
		//assign subtrees 
		returnNode->left = buildTree(s, ul, pair<int,int>(lr.first,minVarSplit), !vert); 
		returnNode->right = buildTree(s, pair<int,int>(ul.first,minVarSplit+1), lr, !vert); 

		return returnNode; 
	}else{
		cout << "buildTree: nope." << endl;
		return NULL;
	}
	

}

PNG twoDtree::render(){
	PNG returnPic; returnPic.resize(width,height);
	
	
	
	
// YOUR CODE HERE!!

}

int twoDtree::idealPrune(int leaves){

// YOUR CODE HERE!!

}

int twoDtree::pruneSize(int tol){
    
// YOUR CODE HERE!!

}

void twoDtree::prune(int tol){

// YOUR CODE HERE!!

}

void twoDtree::clear() {

	clearRecursive(root);
}

void twoDtree::clearRecursive(Node* node){

	if (node == NULL) return;
	
	clearRecursive(node->left);
	clearRecursive(node->right);
	delete node;
	return;
}

void twoDtree::copy(const twoDtree & orig){

// YOUR CODE HERE!!

}



