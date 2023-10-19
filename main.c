nclude "monty.h"

/**
 * main - Monty ByteCode Interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	vglo.fd = fopen(argv[1], "r");
	if (vglo.fd == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&(vglo.buffer), &len, vglo.fd)) != -1)
	{
		vglo.cont++;
		char *opcode = _strtoky(vglo.buffer, " \t\n");

		if (opcode != NULL)
		{
			void (*op_func)(stack_t **stack, unsigned int line_number);

			op_func = get_opcodes(opcode);

			if (op_func != NULL)
				op_func(&(vglo.head), vglo.cont);
			else
			{
				fprintf(stderr, "L%u: unknown instruction %s\n", vglo.cont, opcode);
				free_vglo();
				return (EXIT_FAILURE);
			}
		}
	}

	free_vglo();
	return (EXIT_SUCCESS);
}
