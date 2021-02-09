#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ltrim(char *s) {
	while (*s == ' ' || *s == '\t') s++;
	return s;
}

char getRegister(char *text) {
	if (*text == 'r' || *text=='R') text++;
	return atoi(text);
}

int assembleLine(char *text, unsigned char* bytes) {
	text = ltrim(text);
	char *keyWord = strtok(text," ");
	if (strcmp("add",keyWord) == 0) {
		bytes[0] = 0x10;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 2 | getRegister(strtok(NULL," "));
                  printf ("%x" , bytes[0]);
                  printf ("%x\n" , bytes[1]);
		return 2;
	}
        else if(strcmp("subtract",keyWord) == 0) {
            bytes[0] = 0x50;
            bytes[0] |= getRegister(strtok(NULL," "));
            bytes[5] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL," "));
             printf ("%x" , bytes[0]);
             printf ("%x\n" , bytes[5]);
            return 2;
        }
        else if(strcmp("multiply",keyWord) == 0) {
            bytes[0] = 0x40;
            bytes[0] |= getRegister(strtok(NULL," "));
            bytes[4] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL," "));
             printf ("%x" , bytes[0]);
             printf ("%x\n" , bytes[4]);
            return 2;
        }
        else if(strcmp("divide",keyWord) == 0) {
            bytes[0] = 0x30;
            bytes[0] |= getRegister(strtok(NULL," "));
            bytes[3] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL," "));
             printf ("%x" , bytes[0]);
             printf ("%x\n" , bytes[3]);
            return 2;  
        }
        else if(strcmp("and",keyWord) == 0) {
            bytes[0] = 0x20;
            bytes[0] |= getRegister(strtok(NULL," "));
            bytes[2] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL," "));
             printf ("%x" , bytes[0]);
             printf ("%x\n" , bytes[2]);
            return 2;
        }
         else if(strcmp("or",keyWord) == 0) {
            bytes[0] = 0x60;
            bytes[0] |= getRegister(strtok(NULL," "));
            bytes[6] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL," "));
             printf ("%x" , bytes[0]);
             printf ("%x\n" , bytes[6]);
            return 2;
        }
                 else if(strcmp("or",keyWord) == 0) {
            bytes[0] = 0x60;
            bytes[0] |= getRegister(strtok(NULL," "));
            bytes[6] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL," "));
             printf ("%x" , bytes[0]);
             printf ("%x\n" , bytes[6]);
            return 2;
        }
}

int main(int argc, char **argv) {
	FILE *src = fopen("input.txt","r");
	FILE *dst = fopen("output.txt","w");
	while (!feof(src)) {
		unsigned char bytes[4];
		char line[1000];
		if (NULL != fgets(line, 1000, src)) {
			printf ("read: %s\n",line);
			int byteCount = assembleLine(line,bytes);
			fwrite(bytes,byteCount,1,dst);
		}
	}
	fclose(src);
	fclose(dst);
	return 0;
}