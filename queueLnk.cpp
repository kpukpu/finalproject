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
	if (empty() == 1) {//����� ���
		rear = new QueueNode<QE>(newElement, NULL);//head ����
		front = rear;//ù ����̱� ������ front�� ��忡 ����Ű�� ��
	}
	else
	{
		rear->next = new QueueNode<QE>(newElement, NULL);//rear�� ������ ���ο� ��� �߰�
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
		return NULL;//����� ���
	else {
		QueueNode<QE> *temp;//�ӽ÷� front ���� ���� ��� ����
		temp = front;//front ���� �ӽ÷� ����
		front = front->next;//front +1
		return temp->element;//�ӽ÷� ���� front �� return
	}
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	// pre-lab (Linked)
	if (front == NULL)//front�� �ƹ��͵� �ȴ�������� empty
		return 1;
	else
		return 0;
}

template < class QE >
int Queue<QE>::_front() const {
	return front->element;
}