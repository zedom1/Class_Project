#ifndef LINKLIST_H
#define LINKLIST_H 


#include "common.h"

// 单独一个节点的类，保存一块连续可用空间的起始位置及长度
struct ListNode{
	Memory start;
	Memory length;
	ListNode * pred;
	ListNode * succ;
	ListNode * insertAsPred( ListNode* node, Memory s,Memory l );
	ListNode * insertAsSucc( ListNode* node, Memory s, Memory l );

};

// 带首尾哨兵的双向链表类
struct List{
	Quantity _size ;
	ListNode * header,*trailer;
	List();
	// 给定节点指针，将其从链表中删除
	Memory* removeNode(  ListNode * p );
	// 获取除哨兵外的第一个节点
	ListNode * first();
	// 清空除哨兵外的所有节点
	Quantity clear();
	// 在给定节点前面插入节点，a为大小为2的数组，a[0]为起始位置，a[1]为长度
	void insertBefore( ListNode* node, Memory * a );
	// 在p前的n个节点内找到长度<=e的节点
	ListNode * search( Memory e, Quantity n, ListNode * p );
	// 对节点进行排序
	void insertionSort( );
	// 根据起始位置和长度自行插入
	ListNode * insertSingle( Memory start , Memory length);
};


ListNode* ListNode::insertAsPred( ListNode* node, Memory s,Memory l ){
	ListNode *a= new ListNode();
	a->start = s;
	a->length = l;
	a->pred = node->pred;
	a->succ = node;
	node->pred->succ=a;
	node->pred=a;
	return a;
}

ListNode* ListNode::insertAsSucc( ListNode* node, Memory s, Memory l ){
	ListNode *a= new ListNode();
	a->succ = node->succ;
	a->pred = node;
	a->start = s;
	a->length = l;
	node->succ->pred=a;
	node->succ=a;
	return a;
}

List::List(){
	header = new ListNode;
	header->start = 0;
	header->length = 0;
	trailer = new ListNode;
	header->start = 0;
	trailer->length = MAXNBLOCK;
	header->succ=trailer;
	trailer->pred=header;
	_size=0;
	trailer->succ=header->pred=NULL;
	insertSingle(0,1000);
}

Memory * List::removeNode( ListNode * p ){
	Memory * a = new Memory[2];
	a[0] = p->start;
	a[1] = p->length;
	p->pred->succ=p->succ;
	p->succ->pred=p->pred;
	delete p;
	_size--;
	return a;
}

ListNode * List::first(){
	return header->succ;
}

Quantity List::clear(){
	Quantity old_size=_size;
	while( _size!=0 ){
		Memory *a = removeNode(first());
		delete [] a;
	}
	return old_size;
}

void List::insertBefore( ListNode* node, Memory * a ){
	node->insertAsPred(node,a[0], a[1]);
	delete []a;
}

ListNode * List::search( Memory e, Quantity n, ListNode * p ){
	while( 0<=n-- ){
		if( (p=p->pred)->length<=e )
			break;
	}
	return p;
}

void List::insertionSort( ){
	Quantity r = 0;
	ListNode * p = header->succ;
	while( r < _size){
		if(p->start < p->pred->start){
			p->insertAsSucc(search( p->length , r , p ), p->start, p->length); 
			p=p->succ;
			removeNode( p->pred );
		}else{
			p=p->succ;
		}
		r++;
	}
}

ListNode * List::insertSingle( Memory start , Memory length){
	ListNode * tem = header;
    while(start >= tem->start)
		tem = tem->succ;
	_size++;
	return tem->insertAsPred( tem, start , length );
}

#endif
