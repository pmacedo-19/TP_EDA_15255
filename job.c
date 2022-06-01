
#include "Header.h"

/**
* @brief Creates a new job
* @param [in]	id		ID of the job to be created
*/
Job* CreateJob(char* id)
{
	Job* aux = (Job*)calloc(1, sizeof(Job));
	strcpy(aux->id, id);
	return aux;
}

/**
* @brief Creates a new Node to add a job into the list of jobs
* @param [in]	job		Job to be added to the list
*/
ListJob* CreateNodeListJob(Job* job)
{
	ListJob* new = (ListJob*)calloc(1, sizeof(ListJob));
	strcpy(new->job.id, job->id);
	new->operations = NULL;
	new->next = NULL;
	return new;
}

/**
* @brief Inserts a job in the list of jobs
* @param [in]	list	Pointer to the list of Jobs
* @param [in]	job		Job to be added to the list
*/
ListJob* InsertJobListJob(ListJob* list, Job* job)
{
	if (job == NULL) return list;

	ListJob* new = CreateNodeListJob(job);
	if (list == NULL) list = new;
	else
	{
		new->next = list;
		list = new;
	}
	return list;
}

/**
* @brief Searches for a job with the ID given
* @param [in]	list	Pointer to the list of Jobs
* @param [in]	id		Identification of the job
*/
ListJob* SearchJob(ListJob* start, char* id)
{
	ListJob* aux = start;
	while (aux)
	{
		if (strcmp((aux->job).id, id) == 0) return aux;
		aux = aux->next;
	}
	return NULL;
}

/**
* @brief Inserts one operation in the list of operations belonging to the job with the ID given
* @param [in]	list	Pointer to the list of Jobs
* @param [in]	op		Operation to be added to the list
* @param [in]	id		Identification of the job
*/
ListJob* InsertOperationJob(ListJob* list, Operation* op, char* id)
{
	if (list == NULL) return NULL;
	if (op == NULL) return list;

	ListJob* aux = SearchJob(list, id);
	if (aux)
	{
		aux->operations = InsertListOperations(aux->operations, op);
	}
	return list;
}

/**
* @brief Shows all the operations present in one job identified by his ID
* @param [in]	list	Pointer to the list of Jobs
* @param [in]	id		Identification of the operation
*/
void ShowJobOperations(ListJob* list, char* id)
{
	ListJob* aux = list;
	aux = SearchJob(list, id);
	if (aux)
	{
		ListOperations* listOp = aux->operations;
		printf("Job: %s\n", aux->job.id);
		ShowOperations(listOp);
	}
}

void WriteJobsFile(char filename[], ListJob* lst)
{
	ListJob* aux = lst;
	ListOperations* temp = NULL;

	FILE* file;
	file = fopen(filename, "wb");
	if (file == NULL)
	{
		fprintf(stderr, "\nCouldn't Open File'\n");
		exit(1);
	}

	// writing all the nodes of the linked list to the file
	while (aux != NULL)
	{ 
		temp = aux->operations;
		
		while (temp != NULL)
		{
			fprintf(file, "%s,%d,%d,%d\n",aux->job.id, temp->operation.id, temp->operation.machine, temp->operation.duration);
			temp = temp->next;
		}
		aux = aux->next;
	}
	// Final status feedback
	if (fwrite != 0)
	{
		printf("List stored successfully\n");
	}
	else
	{
		printf("Error While Writing\n");
	}

	fclose(file);
}