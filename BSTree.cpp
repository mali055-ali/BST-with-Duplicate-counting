#include "BSTree.h"

#include <iostream>

using namespace std;

void BSTree::insert(const string& key) {
  Node* nodeToInsert = new Node(key);

  if(root == nullptr){
     root = nodeToInsert;
     return;
  }
  
  Node* curr = root;

  while(curr != nullptr){
    if(curr->key == key) {
      curr->count++;
      return;
    }
    if(key < curr->key){
      if(curr->left == nullptr){
        curr->left = nodeToInsert;
        nodeToInsert->count = 1;
        return;
      }
      curr = curr->left;
    } else {  // key is more than curr go right
        if(curr->right == nullptr){
          curr->right = nodeToInsert;
          nodeToInsert->count = 1;
          return;
        }
        curr = curr->right;
    }
  }
}

bool BSTree::search(const string& key) const {
  return search(key, root);
}

string BSTree::largest() const {
  if (root == nullptr) {
    return "";
  }

  Node* curr = root;
  while(curr->right != nullptr){
    curr = curr->right;
  }

  return curr->key;
}

string BSTree::smallest() const {
  if (root == nullptr) {
    return "";
  }

  Node* curr = root;
  while(curr->left != nullptr){
    curr = curr->left;
  }

  return curr->key;
}

int BSTree::height(const string& key) const {
  if(root == nullptr) {
    return -1;
  }

  Node* curr = root;
  while (curr->key != key){
    if(key < curr->key){
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return height_of(curr);
}

void BSTree::remove(const string& key) {
  remove(nullptr, root, key);
}

void BSTree::preOrder() const {
  preOrder(root);
  cout << endl;
}

void BSTree::postOrder() const {
  postOrder(root);
  cout << endl;
}

void BSTree::inOrder() const {
  inOrder(root);
  cout << endl;
}

void BSTree::remove(Node* parent, Node* curr, const string& key) {
  //  case tree doesnt exist or key is not found
  if(curr == nullptr) return;

  //  if != to key parent equal current node and go down right or left respective to key and thats child
  // if key = curr key moves on
  if (key < curr->key) {
    remove(curr, curr->left, key);
    return;
  }
  if (key > curr->key) {
    remove(curr, curr->right, key);
    return;
  }
  
  if(curr->count > 1) {
    curr->count--;
    return;
  }

  // case where root is a leaf node
  if(parent == nullptr){
    if(curr->left == nullptr and curr->right == nullptr){
      delete curr;
      root = nullptr;
      return;
    }
  }
 // leaf case
  if(curr->left == nullptr and curr->right == nullptr){
    if (parent->left == curr){
      delete curr;
      parent->left = nullptr;
      return;
    } else {
      delete curr;
      parent->right = nullptr;
      return;
    }
  }

  Node* target = nullptr;
  bool targetInLeft = false;
  if(curr->left != nullptr or curr->right != nullptr){  // if curr has a child or two
    if(curr->left != nullptr){
      target = leftMaxNode(curr->left); 
      targetInLeft = true;
        // find the smalest key in the right subtree
    } else {
       // find the largest key in the left subtree
      target = rightMinNode(curr->right);
      
    }

    curr->key = target->key;
    curr->count = target->count;
    target->count = 1;

    // put target(leaf node) key in curr key, then go down the respective left or right subtree
    // where target exists, and remove target as a simpiler case
    if(targetInLeft) remove(curr, curr->left, target->key);
    else remove(curr, curr->right, target->key);
  }
}

int BSTree::height_of(Node* tree) const {
  if(tree == nullptr) return -1;
  int leftHeight = height_of(tree->left);
  int rightHeight = height_of(tree->right);
  return 1 + max(leftHeight,rightHeight);
}

void BSTree::preOrder(Node* tree) const {
  if(tree == nullptr) return;
  cout << tree->key << '(' << tree->count << "), ";
  preOrder(tree->left);
  preOrder(tree->right);
}

void BSTree::postOrder(Node* tree) const {
  if(tree == nullptr) return;
  postOrder(tree->left);
  postOrder(tree->right);
  cout << tree->key << '(' << tree->count << "), ";
}

void BSTree::inOrder(Node* tree) const {
  if(tree == nullptr) return;
  inOrder(tree->left);
  cout << tree->key << '(' << tree->count << "), ";
  inOrder(tree->right);
}

bool BSTree::search(const string& key, Node* curr) const{
  if(curr == nullptr) return false;  // key not found or tree is empty
  if(key == curr->key) return true;
  if(key < curr->key) return search(key, curr->left);
  return search(key, curr->right);  // case where key > curr key go right
}

Node* BSTree::rightMinNode(Node* target){
  while (target->left != nullptr){
    target = target->left;
  }
  return target;
}

Node* BSTree::leftMaxNode(Node* target){
  while (target->right != nullptr){
    target = target->right;
  }
  return target;
}

