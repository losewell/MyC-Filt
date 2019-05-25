#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mycfilt.h"

#define TRUE 1
#define FALSE 0

int caculen(char *s, int i, int *rv) {
	int cnt = 0;
	while (isdigit(s[i])) {
		*rv = (*rv) * 10 + s[i] - '0';
		i++, cnt++;
	}
	return cnt;
}

void cfilt (char *s) {
	if (strlen(s) < 2) {
		printf("%s\n", s);
		return;
	}

	if (s[0] != '_' || s[1] != 'Z') {
		printf("%s\n", s);
		return;
	}

	int index = 2, cnt = 0;
	int isNest = FALSE;
        int slen = strlen(s);
	char *rv = malloc(sizeof(char) * MAXNAMELEN);
	if (!rv) {
		fprintf(stderr, "No enough space!\n");
		exit(1);
	}

		if (s[index] == nest_st) {
			isNest = TRUE;
			index ++;
		} else if (!isdigit(s[index])) {
			free(rv);
			printf("%s\n", s);
			return;
		}

		while (index < slen) {
			int namelen = 0;
			int nameindex = caculen(s, index, &namelen);
			if (nameindex == 0) {
				break;
			}
			strncat(rv, s+index+nameindex, namelen);
			index += nameindex + namelen;
			cnt += namelen;
			if (isdigit(s[index])) {
				strcat(rv, spaceflag);
				cnt += strlen(spaceflag);
			}
		}
		if (index >= slen) {
			free(rv);
			printf("%s\n", s);
			return;
		}

		if (isNest && s[index] != nest_en) {
			free(rv);
			printf("%s\n", s);
			return;
		}

		strcat(rv, "(");
		cnt += 1;
		while (++index < slen) {
			switch(s[index]) {
				case 'i':
					strcat(rv, "int");
					cnt += 3;
					break;
				case 'f':
					strcat(rv, "float");
					cnt += 5;
					break;
				case 'd':
					strcat(rv, "double");
					cnt += 6;
					break;
				case 'v':
				default:
					break;
			}
			if (index != slen - 1) {
				strcat(rv, ",");
				cnt += 1;
			}
		}
		strcat(rv, ")");
		cnt += 1;

		rv[cnt] = '\0';
		printf("%s\n", rv);
		free(rv);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "%s:You need at least two arguments!\n", argv[0]);
			exit(1);
	}

	int i;
	for (i = 1; i < argc; ++i) {
		cfilt(argv[i]);
	}

	return 0;
}
