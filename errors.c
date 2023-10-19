#include "monty.h"

/**
 * err - Handles error messages based on error codes.
 * @error_code: The error codes and their meanings:
 *   (1) => No input file or multiple files given.
 *   (2) => Unable to open or read the provided file.
 *   (3) => Invalid instruction found in the file.
 *   (4) => Memory allocation (malloc) failure.
 *   (5) => Invalid argument passed to the "push" instruction (not an integer).
 *   (6) => Stack is empty when executing "pint".
 *   (7) => Stack is empty when executing "pop".
 *   (8) => Stack is too short for a specific operation.
 */
void err(int error_code, ...)
{
	va_list ag;
	char *op;
	int l_num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 1:
			/* Display usage message */
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			/* Display file open error */
			fprintf(stderr, "Error: Can't open file %s\n",
				va_arg(ag, char *));
			break;
		case 3:
			/* Display unknown instruction error */
			l_num = va_arg(ag, int);
			op = va_arg(ag, char *);
			fprintf(stderr, "L%d: unknown instruction %s\n", l_num, op);
			break;
		case 4:
			/* Display memory allocation error */
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			/* Display "push" instruction usage error */
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(ag, int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * more_err - Handles additional error cases.
 * @error_code: The error codes and their meanings:
 *   (6) => Stack is empty when executing "pint".
 *   (7) => Stack is empty when executing "pop".
 *   (8) => Stack is too short for a specific operation.
 *   (9) => Division by zero error.
 */
void more_err(int error_code, ...)
{
	va_list ag;
	char *op;
	int l_num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 6:
			/* Display "pint" stack empty error */
			fprintf(stderr, "L%d: can't pint, stack empty\n",
				va_arg(ag, int));
			break;
		case 7:
			/* Display "pop" empty stack error */
			fprintf(stderr, "L%d: can't pop an empty stack\n",
				va_arg(ag, int));
			break;
		case 8:
			/* Display stack too short error */
			l_num = va_arg(ag, unsigned int);
			op = va_arg(ag, char *);
			fprintf(stderr, "L%d: can't %s, stack too short\n", l_num, op);
			break;
		case 9:
			/* Display division by zero error */
			fprintf(stderr, "L%d: division by zero\n",
				va_arg(ag, unsigned int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * string_err - Handles errors related to string operations.
 * @error_code: The error codes and their meanings:
 *   (10) ~> Value in a node is outside ASCII bounds.
 *   (11) ~> Stack is empty for the operation.
 */
void string_err(int error_code, ...)
{
	va_list ag;
	int l_num;

	va_start(ag, error_code);
	l_num = va_arg(ag, int);
	switch (error_code)
	{
		case 10:
			/* Display "pchar" value out of range error */
			fprintf(stderr, "L%d: can't pchar, value out of range\n", l_num);
			break;
		case 11:
			/* Display "pchar" stack empty error */
			fprintf(stderr, "L%d: can't pchar, stack empty\n", l_num);
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

