
#include "Header.h"

#define TAM 15

int main() {

	ListJob* listjob = NULL;
	ListOperations* listoperations = NULL;
	ListOperations* op = NULL; // Aux list for the duration tests

	/*! Reads all the elements from a list of Jobs drom a file */
	listjob = ReadJobsFile("Job1.txt", listjob);
	
	/*! Test of the path with least duration
	*	Gets the shortest duration path with "GetShortPathJob"
	*	Shows the resulting list with "ShowOperations"
	*/
	//op = GetShortPathJob(listjob, "pr1.2");
	//ShowOperations(op);
	

	/*! Test of the path with longest duration
	*	Gets the longest duration path with "GetLongPathJob"
	*	Shows the resulting list with "ShowOperations"
	*/
	//op = GetLongPathJob(listjob, "pr1.2");
	//ShowOperations(op);
	//WriteOpFile("Output.txt", op);

	/*! Test of the mean for each operation in a job
	*	Gets the mean for each operation in a selected job
	*	Shows the resulting list with "ShowOperations" --- Discard machine id (not relevant in this case)
	*/
	//op = GetMeanPathJob(listjob, "pr1.2");
	//ShowOperations(op);

	/*! Test of the removal of an operation
	*	Removes the operation by giving the identifier "RemoveOperation"
	*	Shows the resulting list with "ShowOperations"
	*/
	//op = GetLongPathJob(listjob, "pr1.2");
	//op = RemoveOperation(op, 1);
	//ShowOperations(op);

	/*! Test to remove a job by id */
	//listjob = RemoveJob(listjob, "pr1.2");

	/*! Test of writing list of jobs to file
	*	Writes all the elements from the struct "ListJob" to the output file
	*/
	//WriteJobsFile("JobOutput.txt", listjob);

	getchar();

	//return(0);
}