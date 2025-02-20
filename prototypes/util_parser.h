#ifndef _UTIL_PARSER_
#define _UTIL_PARSER_

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

char **serializer(char *cmdstr, int (*partitions)[], part p);
char *get_redir_str(int code);
char *get_sep_str(int code);
/* char *get_partition(char *cmdline, int *sep, part p); */
char *get_separation(const char *line, int *sep);
char *get_redirection(const char *line, int *part);

#endif /* _UTIL_PARSER_ */
