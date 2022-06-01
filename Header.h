/**
*
*
*
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

/*!
* @brief	Struct that defines an operation
*/
typedef struct Operation {
	int id;
	int machine;
	int duration;
}Operation;

/*!
* @brief	Struct that defines a List of Operations
*/
typedef struct ListOperations {
	struct Operation operation;
	struct ListOperations* next;
}ListOperations;

/*!
* @brief	Struct that defines a Job
*/
typedef struct Job
{
	char id[6];
}Job;

/*!
* @brief	Struct that defines a List of Jobs
*/
typedef struct ListJob {
	struct Job job;
	struct ListOperations* operations;
	struct ListJob* next;
}ListJob;

/**/
Operation* CreateOperation(int id, int machine, int duration);
ListOperations* CreateNodeListOperations(Operation* op);
//bool ExistOperation(ListOperations* list, int id);
ListOperations* InsertListOperations(ListOperations* list, Operation* op);
ListOperations* GetShortPathJob(ListJob* list, char* id);
ListOperations* GetLongPathJob(ListJob* list, char* id);
void ShowOperations(ListOperations* h);
ListOperations* RemoveOperation(ListOperations* list, int id);
ListOperations* GetMeanPathJob(ListJob* list, char* id);
void WriteOpFile(char filename[], ListOperations* job);

void WriteFile(char filename[], ListOperations* job);

/**/
Job* CreateJob(char* id);
ListJob* CreateNodeListJob(Job* job);
ListJob* InsertJobListJob(ListJob* list, Job* job);
ListJob* SearchJob(ListJob* start, char* id);
ListJob* InsertOperationJob(ListJob* list, Operation* op, char* id);
void ShowJobOperations(ListJob* list, char* id);
void WriteJobsFile(char filename[], ListJob* lst);
