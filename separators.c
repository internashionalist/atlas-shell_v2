/*

COMMAND SEPARATORS

: && ||

- parse command string into multiple segments
- struct? array? linked list?

/*
 * parse_separators - splits input line by whatever separators
 * @line: initial command line
 * 
 * Return: hopefully an array of the segments
 */

command_segment *parse_separators(char *line)
{
    command_segment *segments = NULL; /* init array */
    size_t count = 0; /* segments count */
    size_t capacity = 4; /* I have no idea - there could be more? */

    segments = malloc(sizeof(command_segment) * capacity);
    if (!segments)
        return (NULL); /* workable malloc for array */

    /* init line index */
    while (line[i] != '\0')
    {
        /* get command until separator */
        
        /* identify separator type */
        
        /* store command and separator in segments array */

        /* mark end of array */
    }
}
