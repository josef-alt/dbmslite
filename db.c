#define	_GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "io.c"

typedef enum {
	COMMAND_SUCCESS,
	COMMAND_UNRECOGNIZED
} CommandResult;

typedef enum {
	PREPARE_SUCCESS,
	PREPARE_UNRECOGNIZED // exception handling
} PrepareResult;

typedef enum {
	STATEMENT_INSERT,
	STATEMENT_SELECT
} StatementType;

typedef struct {
	StatementType type;
} Statement;

CommandResult execute(InputBuffer* command) {
	if(strcmp(command->buffer, ".exit") == 0) {
		exit(0);
	} else if(strcmp(command->buffer, "help") == 0) {
    printf("help will always be offered to those that ask\n");
    return COMMAND_SUCCESS;
  } else {
		return COMMAND_UNRECOGNIZED;
	}
}

PrepareResult prepare(InputBuffer* buffer, Statement* statement) {
	if(strncmp(buffer->buffer, "SELECT", 6) == 0) {
		statement->type = STATEMENT_SELECT;
    
    printf("select dummy code\n");

		return PREPARE_SUCCESS;
	} else if(strncmp(buffer->buffer, "INSERT", 6) == 0) {
		statement->type = STATEMENT_INSERT;

    printf("insert dummy code\n");

		return PREPARE_SUCCESS;
	} else {
		return PREPARE_UNRECOGNIZED;
	}
}

int main(int argc, char* argv[]) {
	InputBuffer* buffer = create_input_buffer();
	while(true) {
		print_prompt();
		read_input(buffer);

		if(buffer->buffer[0] == '.') {
			switch(execute(buffer)) {
				case COMMAND_SUCCESS:
					continue;
				case COMMAND_UNRECOGNIZED:
					printf("invalid command %s\n", buffer->buffer);
					continue;
			}
		}

		Statement statement;
		switch(prepare(buffer, &statement)) {
			case PREPARE_SUCCESS:
				break;
			case PREPARE_UNRECOGNIZED:
				printf("unrecognized keyword %s\n", buffer->buffer);
				continue;
		}
	}
	return 0;
}
