/**
*
*
*
*/
#pragma once
#include <stdio.h>

typedef struct Operation {
	int id;
	int machine;
	int duration;
}Operation;

typedef struct ListOperations {
	struct Operation operation;
	struct ListOperations* next;
}ListOperations;

typedef struct Job
{
	char id[6];
}Job;

typedef struct ListJob {
	struct Job job;
	struct ListOperations* operations;
	struct ListJob* next;
}ListJob;


Operation* CreateOperation(int id, int machine, int duration);
ListOperations* CreateNodeListOperations(Operation* op);
ListOperations* InsertListOperations(ListOperations* list, Operation* op);