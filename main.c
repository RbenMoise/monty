#define _POSIX_C_SOURCE 200809L
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


global_t vglo;

/**
 * free_vglo - Function to free the global structure
 */
void free_vglo(void)
{
    if (vglo.head != NULL)
        free_dlistint(vglo.head);
    if (vglo.buffer != NULL)
        free(vglo.buffer);
    if (vglo.fd != NULL)
        fclose(vglo.fd);
}

/**
 * start_vglo - Function to initialize the global structure
 * @fd: File descriptor
 */
void start_vglo(FILE *fd)
{
    vglo.lifo = 1;
    vglo.cont = 1;
    vglo.arg = NULL;
    vglo.head = NULL;
    vglo.fd = fd;
    vglo.buffer = NULL;
}

/**
 * main - Monty ByteCode Interpreter
 * @argc: Number of arguments
 * @argv: Array of arguments
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
    FILE *fd;
    size_t size = 0;
    ssize_t nlines = 0;
    void (*f)(stack_t **stack, unsigned int line_number);
    char *lines[2];

    if (argc != 2)
    {

    }

    fd = fopen(argv[1], "r");
    if (fd == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    start_vglo(fd);

    while ((nlines = getline(&vglo.buffer, &size, fd)) != -1)
    {
        lines[0] = _strtoky(vglo.buffer, " \t\n");
        if (lines[0] == NULL)
            continue;

        f = get_opcodes(lines[0]);
        if (f == NULL)
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", vglo.cont, lines[0]);
            free_vglo();
            exit(EXIT_FAILURE);
        }

        vglo.arg = _strtoky(NULL, " \t\n");
        f(&vglo.head, vglo.cont);
        vglo.cont++;
    }

    free_vglo();
    exit(EXIT_SUCCESS);
}
