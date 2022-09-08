#include "monty.c"


ssize_t _getline(char *buffer, ssize_t *bufsize, FILE *stream)
{
    int c;
    ssize_t position = 0;


    while(1)
    {
        c = getc(stream);


	if (c == EOF)
		return -1;

        if (c == EOF || c == '\n' || position == *bufsize)
        {
            buffer[position] = '\0';
            return (position);
        }
        else
        {
            buffer[position] = c;
        }
        position++;
    }
}
