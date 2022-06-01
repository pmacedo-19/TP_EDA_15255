
#include "Header.h"

#define TAM 15

int main() {

	char c[15];

	ListJob* listjob = NULL;
	ListOperations* listoperations = NULL;

	FILE* fp = NULL;

	fp = fopen("Job1.txt", "r");

	if (fp == NULL)
	{
		perror("Error loading file!\n");
		getche();
		return(-1);
	}

	char job[5];
	int id = 0, machine = 0, duration = 0;

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


	ListOperations* op = NULL; // Aux list for the duration tests

	/** Test of the path with least duration
	*	Gets the shortest duration path with "GetShortPathJob"
	*	Shows the resulting list with "ShowOperations"
	*/
	//op = GetShortPathJob(listjob, "pr1.2");
	//ShowOperations(op);
	

	/** Test of the path with longest duration
	*	Gets the longest duration path with "GetLongPathJob"
	*	Shows the resulting list with "ShowOperations"
	*/
	//op = GetLongPathJob(listjob, "pr1.2");
	//ShowOperations(op);

	/** Test of the mean for each operation in a job
	*	Gets the mean for each operation in a selected job
	*	Shows the resulting list with "ShowOperations" --- Discard machine id (not relevant in this case)
	*/
	op = GetMeanPathJob(listjob, "pr1.2");
	ShowOperations(op);

	/** Test of the removal of an operation
	*	Removes the operation by giving the identifier "RemoveOperation"
	*	Shows the resulting list with "ShowOperations"
	*/
	//op = GetLongPathJob(listjob, "pr1.2");
	//op = RemoveOperation(op, 1);
	//ShowOperations(op);
	
	getchar();

	//return(0);
}