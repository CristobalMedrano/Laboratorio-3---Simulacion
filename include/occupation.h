#ifndef _OCCUPATION_H
#define _OCCUPATION_H

Occupation *createNodeOccupation();
Occupation *createOccupationQueue(Occupation *currentOccupation);
Occupation *insertElementOccupationQueue(Occupation *queue, int lengthQueue, float occupancyTime);
void showOccupation(Occupation *currentOccupation);
int lengthOccupation(Occupation *currentOccupation);
float getTimeOccupation(Occupation *currentOccupation, int position);
void freeOccupation(Occupation *currentOccupation);
#endif