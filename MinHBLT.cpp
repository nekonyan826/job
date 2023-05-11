#include"MinHBLT.h"
#include<iostream>
#include<queue>

//将x和y两棵HBLT合并
void MinHBLT::meld(binaryTreeNode<std::pair<int, Job> >* &x, binaryTreeNode<std::pair<int, Job> >*& y)
{
  //如果y为空，不进行合并
  if (y == nullptr)
    return;
  //如果x为空，那么就将y赋值给x
  if (x == nullptr)
  {
    x = y;
    return;
  }

  //如果y的值小于x的值，进行交换
  if (y->element.second < x->element.second)
    std::swap(x, y);

  //将x的右子节点与y合并。如果x没有右子节点，那么就将y设置为x的右子节点
  meld(x->rightChild, y);

  //如果x的左子节点为空，将右子节点设置为左子节点
  if (x->leftChild == nullptr) {
    x->leftChild = x->rightChild;
    x->rightChild = nullptr;
    
    //因为把右子节点赋值给左子节点了，所以右子节点为空了，那么本节点的s值就为1了
    x->element.first = 1;
  }
  else //如果左子节点不为空，比较是否需要交换
  {
    //如果左子节点的s值比右子节点的小，那么就进行交换
    if (x->leftChild->element.first < x->rightChild->element.first) {
      std::swap(x->leftChild, x->rightChild);
    }

    //因为右子节点到外部节点之间的s值是最小的，所以就将x的s值设置为右子节点的s值+1
    x->element.first = x->rightChild->element.first + 1;
  }
}

void MinHBLT::pop()
{
  //得到根节点的左右子节点
  binaryTreeNode<std::pair<int, Job> >* left = this->root->leftChild,
    *right=this->root->rightChild;

  //删除根节点，将左子节点变为新根节点，然后进行合并
  delete this->root;
  this->root = left;
  meld(this->root, right);
  this->treeSize--;
}

void MinHBLT::push(const Job& theElement)
{
  //创建一个新节点
  binaryTreeNode<std::pair<int, Job> > *q = 
    new binaryTreeNode<std::pair<int, Job> >(std::pair<int,Job>(1, theElement));

  //将新节点与本HBLT进行合并
  this->meld(this->root,q);
  this->treeSize++;
}


void MinHBLT::erase()
{
  //调用clearTree
  clearTree(this->root);
  this->root = nullptr;
  this->treeSize = 0;
}


void MinHBLT::clearTree(binaryTreeNode<std::pair<int, Job> >* t)
{
  //后序遍历删除
  if (t)
  {
    clearTree(t->leftChild);
    clearTree(t->rightChild);
    delete t;
  }
}

void MinHBLT::initialize(Job* theElement, int theSize)
{
  //创建一个队列，用来初始化HBLT
  std::queue<binaryTreeNode<std::pair<int, Job> >*> q;
  //清空当前HBLT
  erase();

  //先建立一组HBLT，每个HBLT中只有一个节点
  for (int i = 1; i <=theSize; ++i)
    q.push(new binaryTreeNode<std::pair<int, Job> >(std::pair<int, Job>(1, theElement[i])));

  //theSize个HBLT，需要合并theSize-1次
  for (int i = 1; i <= theSize - 1; ++i)
  {
    //从队列中取出两个HBLT进行合并
    binaryTreeNode<std::pair<int, Job> >* b = q.front();
    q.pop();
    binaryTreeNode<std::pair<int, Job> >* c = q.front();
    q.pop();
    //合并
    meld(b, c);

    //合并之后再次放入到队列中
    q.push(b);
  }

  if (theSize > 0)
    this->root = q.front();
  this->treeSize = theSize;
}


void MinHBLT::postOrderUpdate(binaryTreeNode<std::pair<int, Job> >* x)const
{
  if (x)
  {
    --x->element.second;//优先级--
    ++x->element.second;//等待时间++
    postOrderUpdate(x->leftChild);
    postOrderUpdate(x->rightChild);
    
  }
}
void MinHBLT::update_priority(){
  postOrderUpdate(root);
}

double MinHBLT::avg_wait_time()
{
  if(this->treeSize == 0) return 0;
  this->sum = 0;
  this->tmp_num = 0;
  this->getWaitTime(this->root);
  return this->sum/this->tmp_num;
}
int MinHBLT::min_wait_time()
{
  if(this->treeSize == 0) return 0;
  this->minn = 1000000000;
  this->getWaitTime(this->root);
  return this->minn;
}
int MinHBLT::max_wait_time()
{
  if(this->treeSize == 0) return 0;
  this->maxx = 0;
  this->getWaitTime(this->root);
  return this->maxx;
}

void MinHBLT::getWaitTime(binaryTreeNode<std::pair<int, Job> >* x)
{
  if (x)
  {
    this->sum += x->element.second.w;
    this->tmp_num += 1;
    if (this->maxx<x->element.second.w) this->maxx = x->element.second.w;
    if (this->minn>x->element.second.w) this->minn = x->element.second.w;
    this->getWaitTime(x->leftChild);
    this->getWaitTime(x->rightChild);
    
  }
}