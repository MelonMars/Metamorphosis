#include <stdio.h>


int main() {
	int sz;
	char path[1024];
	ssize_t cnt = readlink("/proc/self/exe", path, sizeof(path) - 1);
	path[cnt] = '\0';
	printf("Filepath: %s\n", path);
	char* string;
	FILE* self;
	self = fopen(path, "r");
	fseek(self, 0L, SEEK_END); 
	sz = ftell(self);
	int ch;
	int offset;
	fseek(self, 0L, SEEK_SET);
	while ((ch = fgetc(self)) != EOF) {
	if (ch == 0x90) {
            offset = ftell(self);
	    printf("NOP Found at offset %d\n", offset);
            break;
        }
    }
	fclose(self);
	printf("Hello");
	FILE* file;
	file = fopen(path, "w");
	if( fseek(file, offset, SEEK_SET) != 0) {
		perror("Error seeking at offset");
		fclose(file);
		return 1;
	}

	if (fputc(9, file) == EOF) {
		perror("Error writing file");
		fclose(file);
		return 1;
	}
	if (fputc(0, file) == EOF) {
		perror("Error writing file 2");
		fclose(file);
		return 1;
	}
	return 0;
}
