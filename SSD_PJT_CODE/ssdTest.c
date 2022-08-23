#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "C:\\Users\\SSAFY\\source\\repos\\SSD_PJ\\Debug\\ssdProject.exe" // �������� ���� ���
#define FILEDIR "C:\\Users\\SSAFY\\source\\repos\\ssdTest\\ssdTest\\nand.txt" // �������� �����
#define TESTDIR "C:\\Users\\SSAFY\\source\\repos\\ssdTest\\ssdTest\\test.txt" // �񱳴�� ���� ����

//�⺻ �Լ� ����///////////////////////////////////////////////////////////////////////////////////////
void write(int i, char* str) {
    int idx; char mem[15];
    char cmd[120];
    memset(cmd, '\0', 120 * sizeof(char));

    if (i == -1) {
        scanf("%d", &idx);
        scanf("%s", mem);
    }
    else {
        idx = i;
        strcpy(mem, str);
    }

    //argv[0] : ������ || argv[2] : �ε��� || argv[3] : ������ ��
    sprintf(cmd, "%s ssd W %d %s", PATH, idx, mem);
    system(cmd);
}

void read(int i) {
    int idx;
    char cmd[120];
    memset(cmd, '\0', 120 * sizeof(char));

    if (i == -1)
        scanf("%d", &idx);
    else
        idx = i;

    //argv[0] : PATH || argv[2] : �ε���
    sprintf(cmd, "%s ssd R %d", PATH, idx);
    system(cmd);
}

//exit�� �Ʒ� while ������ ����

void fullwrite() {
    char mem[20];
    char cmd[120];
    scanf("%s", mem);

    // �Ʒ��� �׽�Ʈ ��ũ��Ʈ���� ����
    for (int i = 0; i < 100; i++) {
        // argv[0] : PATH, argv[3] : idx, argv[4] : mem
        memset(cmd, '\0', 120 * sizeof(char));
        sprintf(cmd, "%s ssd W %d %s", PATH, i, mem);
        printf("%d\n", i);
        system(cmd);
    }
}

void fullread() {
    char cmd[120];
    memset(cmd, '\0', 120 * sizeof(char));


    // �Ʒ��� ssd���� �������� ���
    //sprintf(cmd, "%s FR", PATH);

    // �Ʒ��� �׽�Ʈ ��ũ��Ʈ���� ����
    for (int i = 0; i < 100; i++) {
        // argv[0] : PATH, argv[2] : idx
        sprintf(cmd, "%s ssd R %d", PATH, i);
        system(cmd);
        printf("%d\n", i);
    }
}

void help() { // �̿ϼ�
    printf("write �Է°� |idx[������] value[16���� 0x....]\n");
    printf("read �Է°� | idx\n");
    printf("fullewrite �Է°� |idx[������] value[16���� 0x....]\n");
    printf("fullread | �Է°� ���� \n");
    printf("exit | �Է°� ����\n");
    printf("testapp1");
    printf("testappexte2");
}


//�⺻ �Լ� ����////////////////////////////////////////////////////////////////////////////////////////
//���� ����/////////////////////////////////////////////////////////////////////////////////////////////
//
void Test1() { // �̿ϼ�
    // 1 �׽�Ʈ ����
    fullwrite();
    fullread();

    // 2 �� ȯ�� ����
    FILE* fp;
    FILE* cfp;

    fp = fopen(FILEDIR, "r");
    //char p[120]; sprintf(p, "%s/%s", TESTDIR, "test.txt");
    cfp = fopen(TESTDIR, "r");

    char buf[100], cfpbuf[100];
    memset(buf, '\0', 100 * sizeof(char));
    memset(cfpbuf, '\0', 100 * sizeof(char));

    // 3 ��
    for (int i = 0; i < 100; i++) {
        fgets(buf, 100, fp);
        fgets(cfpbuf, 100, cfp);
        //printf("buf : %s\ncfpbuf : %s\n",buf, cfpbuf);
        // ���� ����
        if (strcmp(buf, cfpbuf)) {
            printf("Test1 failed...\n");
            return;
        }
    }
    printf("Test1 passed...\n");
}

void Test2() {
    char test[15] = "0XAAAABBBB";
    char chg[15] = "0X12345678";
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d %d\n", i, j);
            write(j, test);
        }
    }
    for (int i = 0; i < 5; i++)
        read(i);
    for (int i = 0; i < 5; i++) {
        write(i, chg);
    }
    for (int i = 0; i < 5; i++)
        read(i);

    return;
}

//���� ����/////���� ����////////////////////////////////////////////////////////////////////////////
//main.c/////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {
    // �� â �����ϱ�
    char s[20];
    while (1) {
        printf("shell > ");
        scanf("%s", &s);
        if (!strncmp(s, "help", 4)) {
            help();
        }
        else if (!strncmp(s, "exit", 4)) {
            break;
        }
        else if (!strncmp(s, "testapp1", 8)) {
            Test1();
        }
        else if (!strncmp(s, "testapp2", 8)) {
            Test2();
        }
    }
    int de = -1;
    return 0;
}