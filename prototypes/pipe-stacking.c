#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END  1

int main(void)
{
	int len = 13;
	char *read_text, *write_text = "hello_world\n";
	int reader_a[2], reader_b[2], reader_c[2], reader_d[2];
	int writer_a[2], writer_b[2], writer_c[2], writer_d[2];
	int linker_z[2];

	/* initiating pipes */
	pipe(writer_a);
	pipe(writer_b);
	pipe(writer_c);
	pipe(writer_d);

	pipe(linker_z);

	pipe(reader_a);
	pipe(reader_b);
	pipe(reader_c);
	pipe(reader_d);

	/*
	 * linking pipes
	 * the order of dup2 calls matter
	 * setting up the write end
	 */
	dup2(linker_z[WRITE_END], writer_d[WRITE_END]);
	dup2(writer_d[WRITE_END], writer_c[WRITE_END]);
	dup2(writer_c[WRITE_END], writer_b[WRITE_END]);
	dup2(writer_b[WRITE_END], writer_a[WRITE_END]);

	/* setting up the read end */
	dup2(linker_z[READ_END], reader_a[READ_END]);
	dup2(reader_a[READ_END], reader_b[READ_END]);
	dup2(reader_b[READ_END], reader_c[READ_END]);
	dup2(reader_c[READ_END], reader_d[READ_END]);

	/* closing all intermediate file descriptors  */
	close(linker_z[READ_END]);
	close(reader_a[READ_END]);
	close(reader_b[READ_END]);
	close(reader_c[READ_END]);

	close(reader_a[WRITE_END]);
	close(reader_b[WRITE_END]);
	close(reader_c[WRITE_END]);
	close(reader_d[WRITE_END]);

	close(linker_z[WRITE_END]);
	close(writer_d[WRITE_END]);
	close(writer_c[WRITE_END]);
	close(writer_b[WRITE_END]);

	close(writer_d[READ_END]);
	close(writer_c[READ_END]);
	close(writer_b[READ_END]);
	close(writer_a[READ_END]);

	/* testing pipe chain */
	read_text = malloc(sizeof(char) * len);
	write(writer_a[WRITE_END], write_text, 13);
	read(reader_d[READ_END], read_text, 13);
	printf("test %s", read_text);

	exit(EXIT_SUCCESS);
}
