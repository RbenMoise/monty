#include "monty.h"

/**
 * mul_nodes - Multiplies the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void mul_nodes(stack_t **stack, unsigned int line_number)
{
    int product;

    /* Check if stack or top element are NULL or there are not enough elements */
    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        more_err(8, line_number, "mul");

    /* Advance the stack pointer to the next element and calculate the product */
    (*stack) = (*stack)->next;
    product = (*stack)->n * (*stack)->prev->n;

    /* Store the product in the current top element and clear the previous element */
    (*stack)->n = product;
    free((*stack)->prev);
    (*stack)->prev = NULL;
}

/**
 * mod_nodes - Computes the modulo of the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void mod_nodes(stack_t **stack, unsigned int line_number)
{
    int remainder;

    /* Check if stack or top element are NULL or there are not enough elements */
    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        more_err(8, line_number, "mod");

    /* Check if the divisor (the value at the previous top element) is zero */
    if ((*stack)->n == 0)
        more_err(9, line_number);

    /* Advance the stack pointer to the next element and calculate the remainder */
    (*stack) = (*stack)->next;
    remainder = (*stack)->n % (*stack)->prev->n;

    /* Store the remainder in the current top element and clear the previous element */
    (*stack)->n = remainder;
    free((*stack)->prev);
    (*stack)->prev = NULL;
}

