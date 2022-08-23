#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

	if (strcmp(argv[2], "W") != 0 && strcmp(argv[2], "R") != 0) {
		printf("Wrong input1\n");
		return 0;
	}

	if (strcmp(argv[2], "W") == 0 && argc != 5) {
		printf("Wrong input2\n");
		if (atoi(argv[4]) < 0x00000000 || atoi(argv[4]) > 0xFFFFFFFF) {
			printf("Wrong input6\n");
		}
		return 0;
	}

	if (strcmp(argv[2], "R") == 0 && argc != 4) {
		printf("Wrong input3\n");
		return 0;
	}

	if (strcmp(argv[1], "ssd") != 0) {
		printf("Wrong input4\n");
		return 0;
	}

	if (atoi(argv[3]) < 0 || atoi(argv[3]) > 100) {
		printf("Wrong input5\n");
		return 0;
	}
	
	if (strcmp(argv[2], "W") == 0) {
		printf("It's Write\n");
		FILE* file;
		file = fopen("nand.txt", "r+t");

		if (file == NULL) {
			file = fopen("nand.txt", "a");
		}
		printf("file open\n");
		char* str = (char*)malloc(strlen(argv[3]) + strlen(argv[4]) + 2);
		char temp[256];
		*str = 0;

		strcat(str, argv[3]);
		strcat(str, " ");
		strcat(str, argv[4]);
		strcat(str, "\n");

		while (fgets(temp, 256, file) != NULL) {

			if (strlen(argv[3]) == 1 && temp[0] == str[0]) {
				fseek(file, (-1) * (strlen(str) + 1), SEEK_CUR);
				fputs(str, file);
				fseek(file, strlen(str)+1, SEEK_CUR);
				fclose(file);
				return 0;
			}

			if (strlen(argv[3]) == 2 && temp[0] == str[0] && temp[1] == str[1]) {
				fseek(file, (-1) * (strlen(str) + 1), SEEK_CUR);
				fputs(str, file);
				fseek(file, strlen(str) + 1, SEEK_CUR);
				fclose(file);
				return 0;
			}
		}
		fputs(str, file);
		printf("file write complete\n");
		if(file != NULL)
			fclose(file);
	}

	if (strcmp(argv[2], "R") == 0) {
		FILE* fp1 = fopen("nand.txt", "r");
		printf("file open\n");
		char buf[100]; // nand.txt 저장할 공간
		char add[100] = { 0 }; // 주소 저장할 공간
		while (1) {
			printf("finding~!~!~!\n");
			memset(buf, 0, 100);
			fgets(buf, 1000, fp1); // 파일 읽기
			char i_buf[100] = { 0 }; //인덱스 버퍼
			strcpy(i_buf, buf);
			char* r_idx = strtok(i_buf, " "); //인덱스 " " 기준 잘라서 저장
			if (atoi(argv[3]) == atoi(r_idx)) {
				strcpy(add, strstr(buf, "0X")); // 주소 저장
				printf("Find index\n");
				break;
			}
		}
		printf("address = %s\n", add);
		fclose(fp1);
		FILE* fp2 = fopen("result.txt", "w");
		fputs(add, fp2);
		printf("file write\n");
		fclose(fp2);
	}
	
	return 0;
}