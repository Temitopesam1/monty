#include "monty.h"

/* global struct to hold flag for queue and stack length */
var_t var;

/**
 * free_stack - frees malloced in stack nodes memory
 * @arg: double pointer to the stack
 * @status: exit status
 */


void free_stack(int status, void *arg)
{
	stack_t **stack;
	stack_t *tmp;

	(void) status;
	stack = (stack_t **)arg;

	if (*stack)
	{
		(*stack)->prev->next = NULL;
		(*stack)->prev = NULL;
	}
	while (*stack != NULL)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	var.len_stack = 0;
}

/**
 * free_lineptr - free line pointer returned by getline
 * @status: exit status
 * @arg: pointer to line
 */
void free_lineptr(int status, void *arg)
{
	char **lineptr = arg;

	(void) status;

	if (*lineptr != NULL)
		free(*lineptr);
}

/**
 * myfile_close - close file stream
 * @status: status passed to exit
 * @arg: pointer to file stream
 */

void myfile_close(int status, void *arg)
{
	FILE *myfile;

	(void) status;
	myfile = (FILE *) arg;
	fclose(myfile);
}
/**
 * main - monty bytecode interpreter
 * @argc: size of command line arguments
 * @argv: array of strings holding command line arguments
 * Return: exitcodes for failure or 0 Success
 */

int main(int argc, char *argv[])
{
	int status = 0;
	stack_t *stack = NULL;
	unsigned int line = 0;
	FILE *myfile = NULL;

	char lineptr[BUF_SIZE], *oper = NULL;                                                 

	var.len_queue = 0;
	var.len_stack = 0;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	myfile = fopen(argv[1], "r");
	if (myfile == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(lineptr, BUF_SIZE, myfile))
	{

		line++;
		oper = strtok(lineptr, "\n\t\r ");
		if (oper != NULL && oper[0] != '#')
		{
			call_oper(&stack, oper, line);
		}
	}
/**	free_lineptr(status, &lineptr);**/
	free_stack(status, &stack);
	myfile_close(status, myfile);
	exit(EXIT_SUCCESS);
}
