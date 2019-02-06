#include "queue.h"


typedef struct queueNode
{
  int value;
  struct queueNode * next;
}queueStruct;

queueStruct * head, *tail;

 void enqueue(int value)
{
  if(head == NULL)
  {
    head = tail = (queueStruct*)malloc(sizeof(queueStruct));

  }
  else
  {
    tail = tail->next = malloc(sizeof(queueStruct));
  }
  tail->value = value;
}

int dequeue()
{
  queueStruct * ptr = head;
  int tmp = head->value;
  if(head == tail)
    head = tail = NULL;
  else
    head = head->next;
  free(ptr);
  return tmp;
}

int isEmpty()
{
  return (head == NULL);
}
