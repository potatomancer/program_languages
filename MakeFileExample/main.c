#include<stdio.h>
#include<math.h>
#include"queue.h"

int main()
{
  int i;
  for(i = 0; i < 5; i++)
    enqueue(i);
  while(!isEmpty())
    printf("%d\n", dequeue());  
  return 0;
}
