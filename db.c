#define	_GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "io.c"

int main(int argc, char* argv[]) {
	InputBuffer* buffer = create_input_buffer();
	while(true) {
		print_prompt();
		read_input(buffer);

		if(strcmp(buffer->buffer, ".exit") == 0) {
			exit(0);
		} else {
			printf("invalid command %s\n", buffer->buffer);
		}
	}
	return 0;
}
