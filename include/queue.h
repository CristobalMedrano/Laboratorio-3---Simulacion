#ifndef _QUEUE_H
#define _QUEUE_H

Queue *createNodeQueue();
Queue *insertElementQueue(float time, Queue *currentQueue);
float getTime(Queue *currentQueue, int position);
int lengthQueue(Queue *currentQueue);
void showQueue(Queue *currentQueue);
void freeQueue(Queue *currentQueue);

#endif