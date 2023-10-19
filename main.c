#include "monty.h"
stack_t *head = NULL; /** Initialize an empty stack**/

/**
 * main - Entry point of the Monty interpreter.
 * @argc: Number of arguments
 * @argv: Array of arguments
 * Return: 0 on success, non-zero on failure
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    open_file(argv[1]); /**Open the Monty file**/
    free_nodes();       /** Free dynamically allocated memory**/
    return 0;
}

/**
 * create_node - Creates a new stack node.
 * @n: Number to store in the node
 * Return: A pointer to the newly created node or NULL on failure
 */
stack_t *create_node(int n)
{
    stack_t *node = malloc(sizeof(stack_t));
    if (node == NULL)
        err(4); /** Handle memory allocation error**/

    node->n = n;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/**
 * free_nodes - Frees all stack nodes
 */
void free_nodes(void)
{
    stack_t *tmp;

    if (head == NULL)
        return;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

/**
 * add_to_queue - Adds a new node to the end of the stack.
 * @new_node: Pointer to the new node to add
 * @ln: Line number (unused in this function)
 */
void add_to_queue(stack_t **new_node, __attribute__((unused)) unsigned int ln)
{
    stack_t *tmp;

    if (new_node == NULL || *new_node == NULL)
        exit(EXIT_FAILURE);

    if (head == NULL) {
        head = *new_node;
        return;
    }

    tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = *new_node;
    (*new_node)->prev = tmp;
}

