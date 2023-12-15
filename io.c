typedef struct {
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

InputBuffer* create_input_buffer() {
	InputBuffer* buffer = (InputBuffer*) malloc(sizeof(InputBuffer));
	buffer->buffer = NULL;
	buffer->buffer_length = 0;
	buffer->input_length = 0;
	return buffer;
}

void print_prompt() {
	printf("dbmslite > ");
}

// https://www.w3.org/Library/src/vms/getline.c 
int getline(char **lineptr, size_t *n, FILE *stream)
{
	static char line[256];
	char *ptr;
	unsigned int len;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	if (ferror(stream))
		return -1;

	if (feof(stream))
		return -1;
     
	fgets(line, 256, stream);

	ptr = strchr(line, '\n');   
	if (ptr)
		*ptr = '\0';

	len = strlen(line);
	if (len+1 < 256)
	{
		ptr = realloc(*lineptr, 256);
		if (ptr == NULL)
			return -1;
		*lineptr = ptr;
		*n = 256;
	}

	strcpy(*lineptr, line); 
	return len;
}

void read_input(InputBuffer* buffer) {
	ssize_t bytes = getline(&(buffer->buffer), &(buffer->buffer_length), stdin);
	if(bytes <= 0) {
		printf("error reading");
		exit(1);
	}
	buffer->input_length = bytes;
	buffer->buffer[bytes] = 0;
}