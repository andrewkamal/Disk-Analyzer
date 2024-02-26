#include "BinarySearchTree.h"
class file
{
    public:
    string name;
    long long size;
    bool dir;
    bool root;
    char* path;
    long long directory_size;
     //AVLTree<file>* TREE;
    BSTNode<file>* Ptr_to_Directory;
    BinarySearchTree<BSTNode<file>,file> *tree;
    BinarySearchTree<BSTNode<file>,file> * my_tree;

    //void Insert(file item,AVLNode<file>*n,AVLTree<file> *t);
    file();

    bool  operator>(const file &it)const;//O(1)
    bool operator<(const file &it)const;//O(1)
    bool operator !=(const file &it)const;//O(1)
    bool operator ==(const file &it)const;
    ~file();

};


