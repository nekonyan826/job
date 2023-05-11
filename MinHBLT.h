#ifndef MINHBLT_H
#define MINHBLT_H
#include<iostream>
#include"Job.h"

template<typename T>
struct binaryTreeNode//二叉树节点
{
  T element;
  struct binaryTreeNode<T>* leftChild, *rightChild;
  binaryTreeNode() { this->leftChild = this->rightChild = nullptr; }
  
  binaryTreeNode(const T& theElement) :element(theElement) {
    this->leftChild = this->rightChild = nullptr;
  }

  binaryTreeNode(const T& theElement,const struct binaryTreeNode<T>* theLeftChild,
    const struct binaryTreeNode<T>* theRightChild) :element(theElement) {
    this->leftChild = theLeftChild;
    this->rightChild = theRightChild;
  }
};

class MinHBLT//最小左高树
{
public:
  MinHBLT() { 
    this->root = nullptr; 
    this->treeSize = 0;
  }
  ~MinHBLT() { erase(); }

  bool empty(){//当队列为空返回true;否则返回false
    return this->treeSize == 0;
  }
  int size(){  //返回队列的元素个数
    return this->treeSize;
  }
  Job& top(){     //返回优先级最大的元素的引用
    return this->root->element.second;
  }

  void pop();//删除队首元素
  void push(const Job& theElement);//插入元素theElement
  void initialize(Job* theElement, int theSize);//初始化一个HBLT
  
  void erase(); //清空树
  void meld(MinHBLT& theHBLT){meld(root,theHBLT.root);theHBLT.root = 0;} //将本棵HBLT与参数所指的HBLT进行合并，内部调用私有方法meld
  void update_priority();//更新
  double avg_wait_time();
  int min_wait_time();
  int max_wait_time();
  
private:
  void postOrderUpdate(binaryTreeNode<std::pair<int, Job> >* x)const;//后序遍历
  void getWaitTime(binaryTreeNode<std::pair<int, Job> >* x);
  void clearTree(binaryTreeNode<std::pair<int, Job> >* t);//清空树
  void meld(binaryTreeNode<std::pair<int,Job> >* &x, binaryTreeNode<std::pair<int,Job> >*& y);//合并两个树
  binaryTreeNode<std::pair<int,Job> >* root; //根节点
    // 其中每个树节点类型为std::pait<int,T>类型
    // int：代表每个节点的s值
    // T：代表每个节点的数值
  int treeSize;//树的大小
  double sum;
  int tmp_num;
  int minn;
  int maxx;

  
};

#endif