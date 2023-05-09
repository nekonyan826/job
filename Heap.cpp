#include"Heap.h"

// template<typename T>
Heap::Heap(/* args */)
{
}

// template<typename T>
Heap::~Heap()
{
}

// template<typename T>
void Heap::update_priority()
{
    for(int i=0;i<this->h.size();++i)
    {
        --h[i];
        ++h[i];
    }
}

// template<typename T>
bool Heap::empty() {
	return h.size() == 0;
}

// template<typename T>
Job Heap::top() {
	return h[0];
}
// template<typename T>
void Heap::swap(Job& a, Job& b) {
	Job c = a;
	a = b;
	b = c;
}

// template<typename T>
bool Heap::can_push(int position) {
	int len = h.size();
	//如果没有左节点或者当前节点小于左节点 并且 没有右节点或者当前节点小于右节点
	if ((position * 2 + 1 >= len || h[position]< h[position * 2 + 1]) && (position * 2 + 2 >= len || h[position]< h[position* 2 + 2] ))return false;
	return true;//不需要向下移动
}

// template<typename T>
void Heap::push_down() {
	int position = 0;
	int len = h.size();
	while (can_push(position)) {//需要下移，一定有左孩子
		int target = position * 2 + 1;//target先指向左节点
		if (position * 2 + 2 < len && h[position * 2 + 2] < h[position * 2 + 1])
			target++;
		//若有右节点，且右节点的值小于左节点，则target指向右节点
		swap(h[position], h[target]);//交换当前节点和它左右节点中较小的那个
		position = target;//当前节点移动到交换的子结点处
	}
}

// template<typename T>
void Heap::pop() {
	swap(h[0], h[h.size() - 1]);//将队首元素放到最后
	typename std::vector<Job>::iterator it = h.end();//迭代器先指向end()
	it--;//自建操作，此时it指向最后一个元素
	h.erase(it);//删除最后一个元素，即删除了原队首元素
	push_down();//从队首向下更新
}

// template<typename T>
void Heap::push_up() {
	int now = h.size() - 1;
	int target;
	while (now > 0) {
		target = (now - 1) / 2;
		if (h[target] < h[now])break;
		swap(h[target], h[now]);
		now = target;
	}
}

// template<typename T>
void Heap::push(const Job& it) {
	h.push_back(it);
	push_up();
}


// template<typename T>
int Heap::size() {
	return h.size();
}


