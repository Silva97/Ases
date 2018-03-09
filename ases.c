/*********************
 * Programmed by Luiz Felipe
 * GitHub: https://github.com/Silva97
 *
 * Distributed under the MIT license
 *
 * Ases v1.0 - Official interpreter for the esoteric programming language Ases.
 * To see help about the language Ases, read the README file in the repository:
 *         https://github.com/Silva97/Ases/
 *********************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  search(char* code, char start, int p, int d);
int  fsize(FILE* file);
void afilter(char* dest, char* source);
void showError(int errcode);

#define DATAFILE "ases-data.dat"
#define MAXSIZE 256
#define MEMSIZE 256
#define A 0
#define B 1
#define C 2
#define D 3


int main(int argc, char* argv[]){
	FILE* f;
	char  code[MAXSIZE + 1];
	char  reg[4];
	char  mem[MEMSIZE];
	char  stack = 0;
	char* source;
	int ip = 0, dp = 0, i;

	memset(mem,  0, MEMSIZE);
	memset(code, 0, MAXSIZE+1);
	memset(reg,  0, 4);

	if(argc > 1){
		if(strcmp(argv[1], "-h") == 0){
			printf("Ases v1.0 - 'Official' interpreter for the esoteric programming language Ases\n");
			printf("\tProgrammed by Luiz Felipe\n");
			printf("\tGitHub: https://github.com/Silva97/\n\n");
			printf("Use: ases [-c] [file]\n");
			printf("\t-c   - Compact the code and show this. Otherwise run the code\n");
			printf("\tfile - File for read the Ases code.\n");
			printf("\t       Otherwise read the code from the input\n\n");

			printf("Ases is an esoteric programming language developed by me.\n");
			printf("Read the README file in the GitHub repository for help:\n");
			printf("\thttps://github.com/Silva97/Ases/\n");

		} else if(strcmp(argv[1], "-c") == 0){
			f = fopen(argv[2], "r");
			if(f == NULL) showError(2);

			i      = fsize(f);
			source = malloc(i+1);
			memset(source, 0, i+1);

			fread(source, 1, i, f);
			fclose(f);

			afilter(code, source);
			printf("Size: %d Bytes\n", strlen(code));
			printf("Compacted code: %s\n\n", code);
			exit(0);

		} else {
			f = fopen(argv[1], "r");
			if(f == NULL) showError(2);

			i      = fsize(f);
			source = malloc(i+1);
			memset(source, 0, i+1);

			fread(source, 1, i, f);
			fclose(f);
		}

	} else {
		source = malloc(1025);

		printf("Ases code: ");
		fgets(source, 1024, stdin);
	}

	afilter(code, source); // Remove any non-instruction character

	// If insert or remove instruction, edit the "ac" string in the afilter() function
	while(code[ip] != 0){
		switch(code[ip]){
			case '@':                      break;
			case 'a': reg[A]  = stack;     break;
			case 'b': reg[B]  = stack;     break;
			case 'c': reg[C]  = stack;     break;
			case 'd': reg[D]  = stack;     break;
			case 'A': stack   = reg[A];    break;
			case 'B': stack   = reg[B];    break;
			case 'C': stack   = reg[C];    break;
			case 'D': stack   = reg[D];    break;
			case 'p': dp      = stack;     break;
			case 'P': stack   = dp;        break;
			case '$': reg[D]  = ip;        break;
			case '*': ip      = reg[D];    break;
			case '!': mem[dp] = stack;     break;
			case '=': stack   = mem[dp];   break;
			case '+': stack++;             break;
			case '-': stack--;             break;
			case '.': stack = 0;           break;
			case '#': if(stack != 0) ip++; break;
			case '%': if(stack == 0) ip++; break;

			case '(':
				i = search(code, '(', ip, 1);
				if(i == -1) showError(3);
				ip = i;
			break;

			case ')':
				i = search(code, ')', ip, -1);
				if(i == -1) showError(4);
				ip = i;
			break;

			case '>':
				dp++;
				if(dp >= MEMSIZE) showError(5);
			break;

			case '<':
				dp--;
				if(dp < 0) showError(6);
			break;

			case '0': stack = getchar();         break;
			case '1': putc(stack, stdout);       break;
			case '2': showError(7);              break;
			case '3': printf("\n"); exit(stack); break;
			case '4': reg[A] += stack;           break;
			case '5': reg[A] -= stack;           break;

			case '6':
				f = fopen(DATAFILE, "w");
				fwrite(mem, 1, MEMSIZE, f);
				fclose(f);
			break;

			case '7':
				f = fopen(DATAFILE, "r");
				if(f == NULL) showError(8);

				fread(mem, 1, MEMSIZE, f);
				fclose(f);
			break;

			case '8':
				f = fopen(DATAFILE, "r");

				if(f == NULL){
					stack = 0;
				} else {
					stack = 1;
				}

				fclose(f);
			break;

			case '9':
				if(reg[A] > reg[B]){
					stack = 2;
				} else if(reg[A] == reg[B]){
					stack = 1;
				} else {
					stack = 0;
				}
			break;
		}

		ip++;
	}

	printf("\n");
	return 0;
}

int search(char* code, char start, int p, int d){
	int n = 1;
	while(1){
		p += d;

		if(code[p] == '@')        n--;
		else if(code[p] == start) n++;

		if(n == 0) break;
		if(p <= 0 || p >= MAXSIZE) return -1;
	}

	return p;
}

int fsize(FILE* file){
	int s;

	fseek(file, 0, SEEK_END);
	s = ftell(file);
	fseek(file, 0, SEEK_SET);

	return s;
}

void afilter(char* dest, char* source){
	char ac[] = "abcdABCDpP$*()@!=><+-.#%0123456789";
	int  comm = 0, size = 0;

	while(*source != 0){
		if(strchr(ac, *source) != NULL && comm == 0){
			*dest = *source;
			dest++;
			size++;

			if(size > MAXSIZE){
				showError(1);
			}

		} else if(*source == '\n'){
			comm = 0;
		} else if(*source == ';'){
			comm = 1;
		}

		source++;
	}

	*dest = 0;
}

void showError(int errcode){
	switch(errcode){
		case 1: fprintf(stderr, "Program size exceed %d Bytes\n", MAXSIZE);  break;
		case 2: fprintf(stderr, "File not found\n");                         break;
		case 3: fprintf(stderr, "Instruction '@' expected after '('\n");     break;
		case 4: fprintf(stderr, "Instruction '@' expected before ')'\n");    break;
		case 5: fprintf(stderr, "Data pointer exceeded the maximum size\n"); break;
		case 6: fprintf(stderr, "Data pointer exceeded the minimum size\n"); break;
		case 7: fprintf(stderr, "ERROR!\n");                                 break;
		case 8: fprintf(stderr, "Instruction 7 ERROR: Data not saved\n");    break;
	}

	exit(errcode);
}
