
#include "Header.h"

/**
* @brief Creates a new element of the Operation struct
* @param [in]	id		Identification of the operation
* @param [in]	machine		Machine used in the operation
* @param [in]	duration	Time it takes to run the operation
*/
Operation* CreateOperation(int id, int machine, int duration)
{
	Operation* aux = (Operation*)calloc(1, sizeof(Operation));
	aux->id = id;
	aux->machine = machine;
	aux->duration = duration;
	return aux;
}

/**
* @brief Creates a new Node in the Operations list to add a new operation
* @param [in]	op	Operation to be inserted in the list
*/
ListOperations* CreateNodeListOperations(Operation* op)
{
	ListOperations* new = (ListOperations*)calloc(1, sizeof(ListOperations));
	new->operation.id = op->id;
	new->operation.machine = op->machine;
	new->operation.duration = op->duration;
	new->next = NULL;
	return new;
}

/**
* @brief Inserts one operation in a Operations list
* @param [in]	list	Pointer to the Operations list
* @param [in]	op	Operation to be inserted in the list
*/
ListOperations* InsertListOperations(ListOperations* list, Operation* op)
{
	if (op == NULL)	return list;

	ListOperations* new = CreateNodeListOperations(op);
	if (list == NULL) list = new;
	else 
	{
		new->next = list;
		list = new;
	}
	return list;
}

/**
* @brief Gets the path with least duration from one job
* @param [in]	list	Pointer to the job list
* @param [in]	id	Job ID to avaluate
*/
ListOperations* GetShortPathJob( ListJob* list, char* id)
{
	int i = 7;
	ListJob* l = list;
	Operation* aux = NULL;
	ListOperations* lOp = NULL;

	if (l != NULL)
	{
		if (strcmp(l->job.id, id) == 0)
		{
			ListOperations* op = l->operations;
			while (op != NULL)
			{
				
				if (op->operation.id == i)
				{
					if (aux == NULL)
					{
						//printf("%d", i);
						aux = CreateOperation(op->operation.id, op->operation.machine, op->operation.duration);
						op = op->next;
					}
					else if (op->operation.duration < aux->duration)
					{
						aux->id = op->operation.id;
						aux->machine = op->operation.machine;
						aux->duration = op->operation.duration;
						op = op->next;
					}
					else { op = op->next; }
				}
				else if (aux == NULL)
				{
					i--;
				}
				else
				{
					lOp = InsertListOperations(lOp, aux);
					i--;
					//printf("%d", aux->id);
					aux = NULL;
				}

			}
			if (aux != NULL)
			{
				lOp = InsertListOperations(lOp, aux);
				aux = NULL;
			}
		}
		else { l = l->next; }
	}
	return lOp;
}

/**
* @brief Gets the path with most duration from one job
* @param [in]	list	Pointer to the job list
* @param [in]	id	Job ID to avaluate
*/
ListOperations* GetLongPathJob(ListJob* list, char* id)
{
	int i = 7;
	ListJob* l = list;
	Operation* aux = NULL;
	ListOperations* lOp = NULL;

	if (l != NULL)
	{
		if (strcmp(l->job.id, id) == 0)
		{
			ListOperations* op = l->operations;
			while (op != NULL)
			{

				if (op->operation.id == i)
				{
					if (aux == NULL)
					{
						//printf("%d", i);
						aux = CreateOperation(op->operation.id, op->operation.machine, op->operation.duration);
						op = op->next;
					}
					else if (op->operation.duration > aux->duration)
					{
						aux->id = op->operation.id;
						aux->machine = op->operation.machine;
						aux->duration = op->operation.duration;
						op = op->next;
					}
					else { op = op->next; }
				}
				else if (aux == NULL)
				{
					i--;
				}
				else
				{
					lOp = InsertListOperations(lOp, aux);
					i--;
					//printf("%d", aux->id);
					aux = NULL;
				}

			}
			if (aux != NULL)
			{
				lOp = InsertListOperations(lOp, aux);
				aux = NULL;
			}
		}
		else { l = l->next; }
	}
	return lOp;
}
/**
* @brief Shows all the elements from the operations list 
* @param [in]	h	Pointer to the list
*/
void ShowOperations(ListOperations* h)
{
	ListOperations* aux = h;
	while (aux)
	{
		printf("\nOperation: %d\nMachine: %d\nDuration: %d\n", aux->operation.id, aux->operation.machine, aux->operation.duration);
		aux = aux->next;
	}
}


/**
* @brief Removes Operation from Job with the Operation ID
* @param [in] list	pointer to list start
* @param [in] id	ID of the Operation to be removed
* @return	Pointer to the list
*/
ListOperations* RemoveOperation(ListOperations* list, int id)
{
	if (list == NULL) return NULL;

	if (list->operation.id == id) // Removes in list start
	{
		ListOperations* aux = list;
		list = list->next;
		free(aux);
	}
	else
	{
		ListOperations* aux = list;
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
	return list;
}