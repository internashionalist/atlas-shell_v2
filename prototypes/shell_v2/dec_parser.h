#ifndef _PARSER_
#define _PARSER_

#define SCOL  0
#define BAR   1
#define BBAR  2
#define AND   3
#define AAND  4

#define LOUT  0
#define LLOUT 1
#define RIN   2
#define RRIN  3

typedef enum _part
{
	SEPAR,
	REDIR
} part;

char *remove_comment(char *text, char *comment);
char **tokenize(char *text, char *delims, int limit);
char *get_separation(const char *line, int *sep);
char *get_redirection(const char *line, int *part);

#endif /* _PARSER_ */
