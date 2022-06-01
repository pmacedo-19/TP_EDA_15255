
#include "Header.h"

/*!
* @brief Creates a new job
* @param [in]	id		ID of the job to be created
*/
Job* CreateJob(char* id)
{
	Job* aux = (Job*)calloc(1, sizeof(Job));
	strcpy(aux->id, id);
	return aux;
}

/*!
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

/*!
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

/*!
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

/*!
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

/*!
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

/*!
* @brief Writes all the jobs in listjob to an output file
* @param [in]	filename[]	Name of the file to write the output
* @param [in]	lst			List containing the jobs to write
*/
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
			// Write each element has a line
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


/*!
* @brief Reads all the jobs in file to an list of Jobs
* @param [in]	filename[]	Name of the file to write the output
* @param [in]	list		List to write the Jobs in
*/
ListJob* ReadJobsFile(char filename[], ListJob* list)
{
	FILE* fp;
	ListJob* listjob = list;
	char* job[5];
	int id = 0, machine = 0, duration = 0;
	char c[15];

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		perror("Error loading file!\n");
		getche();
		return(-1);
	}

	while (fscanf(fp, "%[^\n] ", c) != EOF) // Scans the file line by line
	{
		char* field;
		field = strtok(c, ","); // Declaration of the token to separate the variables read
		int i = 1;
		while (field != NULL)
		{
			strcpy(job, field); // Saves the job identifier

			field = strtok(NULL, ","); // Moves to the second token found

			id = atoi(field); // Saves the operation id

			field = strtok(NULL, ",");

			machine = atoi(field);	// Saves the machine id of the operation

			field = strtok(NULL, ",");

			duration = atoi(field);	// Saves the duration of the operation

			field = strtok(NULL, "\n"); // Reads the last token to end line

			//printf("%d\n", id);
		}

		if (listjob == NULL) // Creates the first element of the job list
		{
			Job* jobaux = CreateJob(job);
			listjob = InsertJobListJob(listjob, jobaux);
			Operation* opaux = CreateOperation(id, machine, duration);
			listjob = InsertOperationJob(listjob, opaux, job);
			//printf("Entrou\n");
		}
		else if (listjob != NULL) // Adds all the other jobs
		{
			ListJob* aux = SearchJob(listjob, job);

			if (strcmp(aux->job.id, job) == 0) // Adds operations to existing job
			{
				Operation* opaux = CreateOperation(id, machine, duration);
				listjob = InsertOperationJob(listjob, opaux, job);
				//printf("Entrou\n");
			}
			else	// Adds a new job in case the list isnt NULL
			{
				Job* jobaux = CreateJob(job);
				listjob = InsertJobListJob(listjob, jobaux);
				Operation* opaux = CreateOperation(id, machine, duration);
				listjob = InsertOperationJob(listjob, opaux, job);
				//printf("Entrou\n");
			}
		}
		//printf("%s\n", job);
		//printf("%d\n", listjob->operations->operation.machine);
	}
	fclose(fp);
	return listjob;
}


/*!
* @brief Removes a job from the list of Jobs by job id
* @param [in]	list	List that contains the jobs
* @param [in]	id		Id of the job to remove
*/
ListJob* RemoveJob(ListJob* list, char* id)
{
	if (list == NULL) return NULL;

	if (strcmp(list->job.id, id) == 0) // Removes in list start
	{
		ListJob* aux = list;
		
		/*for (int i = 1;list->operations != NULL; i++)
		{
			RemoveOperation(list->operations, i);
		}*/
		list = list->next;
		free(aux);
	}
	else
	{
		ListJob* aux = list;
		ListJob* auxAnt = aux;
		while (aux && strcmp(aux->job.id, id) != 0) // Searches to remove
		{
			auxAnt = aux;
			aux = aux->next;
		}
		if (aux != NULL)	// Case its found, removes
		{
			/*for (int i = 1; aux->operations != NULL; i++)
			{
				RemoveOperation(aux->operations, i);
			}*/
			auxAnt->next = aux->next;
			free(aux);
		}
	}
	return list;
}


ListJob* RemoveOperationJob(ListJob* list, int id, char* jobId)
{
	if (list == NULL) return NULL;

	if (strcmp(list->job.id, jobId) == 0)
	{
		if (list->operations->operation.id == id) // Removes in list start
		{
			ListOperations* aux = list->operations;
			list->operations = list->operations->next;
			free(aux);
		}
		else
		{
			ListOperations* aux = list->operations;
			ListOperations* auxAnt = aux;
			while (aux && aux->operation.id != id) // Searches to remove
			{
				auxAnt = aux;
				aux = aux->next;
			}
			if (aux != NULL)	// Case its found, removes
			{
				auxAnt->next = aux->next;
				free(aux);
			}
		}
	}
	else
	{
		list = list->next;
	}
	return list;
}