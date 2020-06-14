//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueLnk.cpp
//
//  SOLUTION: Linked list implementation of the Queue ADT
//
//--------------------------------------------------------------------

#include "queueLnk.h"
#include "wtgraph.h"
//--------------------------------------------------------------------

template < class QE >
QueueNode<QE>::QueueNode(const QE &elem, QueueNode<QE> *nextPtr)

// Creates a queue node containing element elem and next pointer
// nextPtr.
{
	element = elem;
	next = nextPtr;
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue(int ignored)

// Creates an empty queue. Parameter is provided for compatability
// with the array implementation and is ignored.
{
	front = 0; rear = 0;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE &newElement)

// Inserts newElement at the rear of a queue.

{
	// pre-lab (Linked)
	if (empty() == 1) {//비었을 경우
		rear = new QueueNode<QE>(newElement, NULL);//head 생성
		front = rear;//첫 노드이기 때문에 front를 헤드에 가리키게 함
	}
	else
	{
		rear->next = new QueueNode<QE>(newElement, NULL);//rear의 다음에 새로운 노드 추가
		rear = rear->next;//rear +1
	}

}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently (front) element from a queue and
// returns it.

{
	// pre-lab (Linked)
	if (empty() == 1)
		return NULL;//비었을 경우
	else {
		QueueNode<QE> *temp;//임시로 front 값을 받을 노드 생성
		temp = front;//front 값을 임시로 받음
		front = front->next;//front +1
		return temp->element;//임시로 받은 front 값 return
	}
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	// pre-lab (Linked)
	if (front == NULL)//front에 아무것도 안담겨있으면 empty
		return 1;
	else
		return 0;
}

template < class QE >
int Queue<QE>::_front() const {
	return front->element;
}