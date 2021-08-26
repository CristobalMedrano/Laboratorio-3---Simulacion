#ifndef _OPTIONS_H
#define _OPTIONS_H

void getOptionsArguments(int argc, char *argv[], float *arrivalRate, float *departureRate, float *endTime);
void showCorrectUse(char *argv[]);
int isFloat(char *optarg, char *type);
int validateArgs(float arrivalRate, float departureRate, float endTime);
int validateNumber(float number);
#endif