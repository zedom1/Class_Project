#ifndef LINKLIST_H
#define LINKLIST_H 


#include "common.h"

struct ListNode{
	Memory start;
	Memory length;
	ListNode * pred;
	ListNode * succ;
	ListNode * insertAsPred( ListNode* node, Memory s,Memory l );
	ListNode * insertAsSucc( ListNode* node, Memory s, Memory l );

};

struct List{
	Quantity _size ;
	ListNode * header,*trailer;
	List();
	Memory* removeNode(  ListNode * p );
	ListNode * first();
	Quantity clear();
	void insertBefore( ListNode* node, Memory * a );
	ListNode * search( Memory e, Quantity n, ListNode * p );
	void insertionSort( );
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
	while(start < tem->start)
		tem = tem->succ;
	_size++;
	return tem->insertAsPred( tem, start , length );
}

#endif