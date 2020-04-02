
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"
#define DEBUG 0

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
	// cout <<"ul : lr -- "<<ul.first<< "." <<ul.second<<" : "<<lr.first<<"."<<lr.second<< " -- vert: " << vert << endl; 
	Node * returnNode = new Node(ul, lr, s.getAvg(ul,lr));

	if (ul.first == lr.first && ul.second == lr.second){
		returnNode->left = NULL;
		returnNode->right = NULL;
		/*#if DEBUG
			cout << "(" << ul.first << "," << ul.second << ") : " << endl <<
			"\t|r:" << (int)returnNode->avg.r << "| g:" << (int)returnNode->avg.g <<
			"| b:" << (int)returnNode->avg.b << "| a:" << (int)returnNode->avg.a << endl;
			
		#endif*/
		return returnNode;
	}

	long minVar = LONG_MAX;
	int minVarSplit = 0;
	if((vert && (ul.first != lr.first)) || (ul.second == lr.second) ){
		for(int i = ul.first; i < lr.first; i++){
			if( s.getScore(ul, pair<int,int>(i,lr.second)) + 
					s.getScore(pair<int, int> (i+1, ul.second), lr) <= minVar){
						
				minVar = s.getScore(ul, pair<int,int>(i,lr.second)) + 
							s.getScore(pair<int, int> (i+1, ul.second), lr);
				minVarSplit = i;
			}
		}
		//assign subtrees
		returnNode->left = buildTree(s, ul, pair<int, int>(minVarSplit,lr.second), !vert);
		returnNode->right = buildTree(s, pair<int, int>(minVarSplit+1, ul.second), lr, !vert);
		
		return returnNode;
	
	} else if ((!vert && (ul.second != lr.second)) || (ul.first == lr.first) ){
		for(int i = ul.second; i < lr.second; i++){
			if( s.getScore(ul, pair<int,int>(lr.first, i)) + 
					s.getScore(pair<int,int>(ul.first, i + 1), lr) <= minVar){
				
				minVar = s.getScore(ul, pair<int,int>(lr.first, i)) + 
							s.getScore(pair<int,int>(ul.first, i + 1), lr);
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
	renderRecursive(returnPic, root); 
	return returnPic; 
}

void twoDtree::renderRecursive(PNG &pic, Node * node){
	#if DEBUG 
		cout<<"width: "<< pic.width() << " height: " << pic.height() << endl; 
	#endif
	if (node->left == NULL && node->right == NULL){
		for(int x = node->upLeft.first; x <= node->lowRight.first; x++){
			for(int y = node->upLeft.second; y <= node->lowRight.second; y++){
				*pic.getPixel(x,y) = node->avg;
				#if DEBUG 
					cout << "(" << x << "," << y <<"): | red: "<< (int)node->avg.r << " | green: " << (int)node->avg.g << " | blue: "<< (int)node->avg.b << " |" <<endl; 
				#endif
			}
		}
	}
	else{
		renderRecursive(pic, node->left);
		renderRecursive(pic, node->right); 
	}
}

int twoDtree::idealPrune(int leaves){
	return idealPruneRecursive(leaves, 0, 255*255*3);
}

int twoDtree::idealPruneRecursive(int leaves, int min, int max){
	cout << "tolerance: " << ((min+max)/2) << endl;
	if(pruneSize((min + max)/2) == leaves){
		return (min + max) / 2;
	}else if (pruneSize((min + max) / 2) < leaves){
		return idealPruneRecursive(leaves, min, ((min + max) / 2));
	}else if (pruneSize((min + max) / 2) > leaves){
		return idealPruneRecursive(leaves, ((min + max) / 2), max);
	}
}

int twoDtree::pruneSize(int tol){
    
return pruneSizeRecursive(root, tol); 
}

int twoDtree::pruneSizeRecursive(Node* node, int tol){
	if (node == NULL || (node->right == NULL && node->left == NULL) ) return 1; 
	if (checkTol(node, node->avg, tol)){
		return 1; 
	} else {
		return pruneSizeRecursive(node->left, tol) + pruneSizeRecursive(node->right, tol);
	}
}

void twoDtree::prune(int tol){
	pruneRecursive(root, tol);
}

void twoDtree::pruneRecursive(Node* node, int tol){
	if (node == NULL || (node->right == NULL && node->left == NULL) ) return;
	if (checkTol(node, node->avg, tol)){
		clearRecursive(node->left);
		clearRecursive(node->right);
		node->left = NULL;
		node->right = NULL;
		return;
	} else {
		pruneRecursive(node->left, tol);
		pruneRecursive(node->right, tol);
	}

}

bool twoDtree::checkTol(Node* node, RGBAPixel avg, int tol){
	if (node->left == NULL && node->right == NULL){
		return (
			(node->avg.r-avg.r)*(node->avg.r-avg.r) + (node->avg.g-avg.g)*(node->avg.g-avg.g) + (node->avg.b-avg.b)*(node->avg.b-avg.b) <= tol
		);
	} else { 
		return (checkTol(node->left, avg, tol) && checkTol(node->right, avg, tol)); 
	}

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
	copyRecursive(&root, orig.root); 
	height = orig.height;
	width = orig.width;
	return; 
}

void twoDtree::copyRecursive(Node **curr, const Node * other){
	if (other != NULL){
		*curr = new Node(other->upLeft, other->lowRight, other->avg);

		if(other->left != NULL){
			copyRecursive(&(*curr)->left, other->left);
		} else {
			(*curr)->left = NULL;
		}
		
		if(other->right != NULL){
			copyRecursive(&(*curr)->right, other->right); 
		} else {
			(*curr)->right = NULL;
		}
	}
}



