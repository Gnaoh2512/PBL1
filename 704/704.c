#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 80
#define MAX_NUMBER_OF_STUDENTS 60

void menu() {
    printf("-------------------------------------------------------------------------\nPBL1 | NHOM 2 | DE TAI 704 | UNG DUNG QUAN LY DIEM SINH VIEN THEO MON HOC\nGIANG VIEN HUONG DAN: Th.S NGUYEN CONG DANH\nNGUOI THUC HIEN: TRAN QUANG HOANG, LE ANH HAO\n-------------------------------------------------------------------------\nMENU\n-------------------------------------------------------------\n1-Nhap diem. \n2-Xem diem. \n3-Sua diem. \n4-Sap xep. \n5-In ra danh sach. \n6-Chinh sua cong thuc diem. \n7-Thoat.\n-------------------------------------------------------------\nNhung cot diem khong su dung xin vui long chinh he so thanh 0\nCo the chinh bang cach chon muc 6\nMac dinh se dat he so: 10, 10, 10, 20, 50\nCac cot diem trong mac dinh se la 0\n-------------------------------------------------------------\nSelect option: ");
}

void clrscr() { // clear man hinh
#ifdef _WIN32
    system("cls");
#elif (__APPLE__ || __linux__)
    system("clear");
#endif
}

void refreshcreen() { // buffer clear man hinh
    printf("Press anything to continue\n");
    getch();
    clrscr();
    menu();
}

int InOptions(int n) { // ngan chan input nguoi dung neu nhu ko co trong lua chon
    int input;
    while (1)
    {
        scanf("%d", &input);
        if (input > 0 && input <= n)
            break;
        printf("Option does not exist | Select again: ");
    }
    return input;
}

float InScore(float a) {
    while (a < 0 || a > 10)
    {
        printf("Score must be in range of 0 -> 10 | Type again: ");
        scanf("%f", &a);
    }
    return a;
}

char *NumberAlike(float a) { // bien diem nhap vao thanh string dang xx.xx
    a = ceilf(a * 100) / 100;
    if (a >= 10)
        return "10.00";
    if (a <= 0)
        return "00.00";
    char c[7];
    char *score = (char *)malloc(10 * sizeof(char));
    score[0] = '\0';
    strcat(score, "0");
    sprintf(c, "%g", a);
    strcat(score, c);
    if (strlen(score) == 4)
        strcat(score, "0");
    if (!(a - (int)a))
        strcat(score, ".00");
    return score;
}
// quicksort
void swap(float *a, float *b) {
    float t = *a;
    *a = *b;
    *b = t;
}
int partition(float array[][2], int low, int high) {
    float pivot = array[high][1];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (array[j][1] >= pivot)
        {
            i++;
            swap(&array[i][0], &array[j][0]);
            swap(&array[i][1], &array[j][1]);
        }
    }
    swap(&array[i + 1][0], &array[high][0]);
    swap(&array[i + 1][1], &array[high][1]);
    return (i + 1);
}
void quickSort(float array[][2], int low, int high) {
    if (low < high)
    {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// z = 0 -> in ra cac lua chon in (danh sach sinh vien, danh sach mon hoc)
// z tu 1 -> 4 -> in ra danh sach mon hoc theo lua chon
// z = -1 -> in danh sach sinh vien
int Indanhsach(short int z) {
    clrscr();
    FILE *file1;
    unsigned short int i;
    char ID[3], line1[MAX_LINE_LENGTH], *token1;
    if (z > 0)
        i = 2;
    else if (z == -1)
        i = 1;
    else
    {
        printf("1.Student list    2.Subject list\nSelect list: ");
        i = InOptions(2);
    }
    clrscr();
    if (i == 1)
    { // in danh sach sinh vien
        file1 = fopen("testdata2\\DSSV.txt", "r");
        if (file1 == NULL)
        {
            printf("Failed to open file | File does not exist\n");
            refreshcreen();
            return 0;
        }
        printf("ID  Name\n");
        while (fgets(line1, MAX_LINE_LENGTH, file1))
        {
            token1 = strtok(line1, ",");
            printf("%s  ", token1);
            token1 = strtok(NULL, ",");
            if (token1 == NULL)
                continue;
            printf("%s", token1);
        }
        printf("\n");
        fclose(file1);
    }
    else if (i == 2)
    { // in danh sach mon hoc theo thu tu
        char subject[4][10] = {"Anh", "DSTT", "Toan", "Triet"};
        if (!z)
        {
            for (int i = 0; i < 4; i++)
            {
                printf("%d.%s   ", i + 1, subject[i]);
            }
            printf("\nSelect subject: ");
            i = InOptions(4);
        }
        else
            i = z;
        clrscr();
        char path[] = {"testdata2\\\\"};
        strcat(path, subject[i - 1]); // noi strings tao thanh path toi file mon hoc
        strcat(path, ".txt");
        FILE *file2;
        char line2[MAX_LINE_LENGTH], *token2;
        file1 = fopen(path, "r");
        if (file1 == NULL)
        {
            printf("Failed to open file | File does not exist\n");
            refreshcreen();
            return 0;
        }
        fseek(file1, 16, SEEK_SET); // bo qua dong 1
        file2 = fopen("testdata2\\DSSV.txt", "r");
        if (file2 == NULL)
        {
            printf("Failed to open file | File does not exist\n");
            refreshcreen();
            return 0;
        }
        char *str[MAX_NUMBER_OF_STUDENTS];
        unsigned short int i = 0;
        while (fgets(line2, MAX_LINE_LENGTH, file2))
        { // lay du lieu tu file DSSV (ID,Name) va truyen vao mang str
            str[i] = malloc(strlen(line2) + 1);
            line2[33] = '\0';
            strcpy(str[i], line2);
            i++;
        }
        int k = i;
        i--;
        char *c, line1copy[MAX_LINE_LENGTH];
        printf("ID  Name                          Lab          Exercise     Diligence     Mid-term        Final         Average\n");
        while (fgets(line1, MAX_LINE_LENGTH, file1))
        {
            unsigned short int check = 0;
            strcpy(line1copy, line1); // tao copy de tranh huy hoai du lieu cua line1
            token1 = strtok(line1, ",");
            for (int pos = 0; pos <= i; pos++)
            {                                // lay ID tu file mon hoc va compare voi ID trong danh sach sinh vien
                strcpy(line2, str[pos]);     // sau khi compare xong thi chuyen sinh vien vua duoc compare xuong duoi
                token2 = strtok(line2, ","); // va chuyen sinh vien truoc sinh vien duoc chuyen len tren
                if (strcmp(token1, token2))
                    continue;
                c = str[pos];
                str[pos] = str[i];
                str[i] = c;
                i--;
                check = 1;
                break;
            }
            if (!check)
                continue;
            printf("%s  ", token2); // print ID
            token2 = strtok(NULL, ",");
            printf("%-30s", token2); // print Name
            token1 = strtok(line1copy, ",");
            token1 = strtok(NULL, ","); // bo qua ID
            while (token1 != NULL)
            {
                printf("%-8s      ", token1);
                token1 = strtok(NULL, ",");
            }
            printf("\n");
        }
        for (int i = 0; i < k; i++)
        {
            free(str[i]);
        }
    }
    if (!z)
        refreshcreen();
}

int Xemdiem() {
    char subject[4][10] = {"Anh", "DSTT", "Toan", "Triet"};
    FILE *file;
    unsigned short int check = 0;
    char ID[9], line[MAX_LINE_LENGTH], *token;
    char test[20];

    Indanhsach(-1);
    // nhap ID
    printf("Type in ID: ");
    scanf("%s", ID);
    clrscr();

    // check DSSV co ID ko
    file = fopen("testdata2\\DSSV.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    while (fgets(line, MAX_LINE_LENGTH, file) && check == 0)
    {
        token = strtok(line, ",");
        if (strcmp(token, ID))
            continue;
        else
        {
            token = strtok(NULL, ",");
            printf("Full Name: %s", token);
            check = 1;
            break;
        }
    }
    if (!check)
    {
        printf("ID does not exist\n");
        refreshcreen();
        return 1;
    }

    // print thong tin
    printf("Subjects        Lab         Exercise    Diligence     Mid-term      Final        Average\n");
    for (int i = 0; i < 4; i++)
    {
        char path[] = {"testdata2\\\\"};
        strcat(path, subject[i]); // noi strings tao thanh path den file mon hoc
        strcat(path, ".txt");
        file = fopen(path, "r");
        if (file == NULL)
        {
            printf("Failed to open file | File does not exist\n");
            refreshcreen();
            return 0;
        }
        fgets(line, MAX_LINE_LENGTH, file); // bo qua dong 1
        while (fgets(line, MAX_LINE_LENGTH, file))
        {
            token = strtok(line, ",");
            if (strcmp(token, ID))
                continue;
            // tim sinh vien trong file cac mon hoc
            printf("%-8s        ", subject[i]);
            for (int i = 0; i < 5; i++)
            {
                token = strtok(NULL, ",");
                printf("%-s        ", token); // print diem Diligence,Mid,Final
            }
            token = strtok(NULL, ",");
            printf("%s", token);
            break; // lay duoc du lieu roi thi out vong lap
        }
    }
    fclose(file);
    refreshcreen();
}

void Heso(char *str, int *sum) {
    char hs[10];
    while (1)
    {
        scanf("%s", hs);
        int num = strtof(hs, NULL);
        if (num < 10 || num > 99)
        {
            printf("He so must be in range from 10 -> 99\n");
            continue;
        }
        *sum += num;
        strcat(str, hs);
        break;
    }
}

int ChinhHeSo() {
    clrscr();
    char subject[4][10] = {"Anh", "DSTT", "Toan", "Triet"};
    unsigned short int input;
    for (int i = 0; i < 4; i++)
    {
        printf("%d.%s   ", i + 1, subject[i]);
    }
    printf("\n");
    printf("Select subject: ");
    input = InOptions(4);
    FILE *file;
    char path[] = "testdata2\\\\";
    strcat(path, subject[input - 1]); // noi strings tao thanh path den file mon hoc
    strcat(path, ".txt");
    file = fopen(path, "r+");
    if (file == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    char output[11] = "";
    int sum;
    while (1)
    {
        sum = 0;
        strcpy(output, "");
        printf("Vui long nhap cac he so theo %% (vi du: 10,20,30,...) va xem xet tong cac he so = 100\n");
        printf("He so Lab: ");
        Heso(output, &sum);
        strcat(output, ",");
        printf("He so Exercise: ");
        Heso(output, &sum);
        strcat(output, ",");
        printf("He so Diligence: ");
        Heso(output, &sum);
        strcat(output, ",");
        printf("He so Midterm: ");
        Heso(output, &sum);
        strcat(output, ",");
        printf("He so Final: ");
        Heso(output, &sum);
        if (sum != 100)
        {
            printf("Not in regulations | press anything to continue \n");
            getch();
            clrscr();
        }
        else
            break;
    }
    fseek(file, 0, SEEK_SET);
    fputs(output, file);
    fclose(file);
    printf("Sua diem thanh cong\n");
    refreshcreen();
}
int Nhapdiem() {
    clrscr();
    unsigned short int input1;
    char line2[MAX_LINE_LENGTH], line1[MAX_LINE_LENGTH], *token1, *token2;
    char subject[4][10] = {"Anh", "DSTT", "Toan", "Triet"};
    for (int i = 0; i < 4; i++)
    {
        printf("%d.%s   ", i + 1, subject[i]);
    }
    printf("\nSelect subject: ");
    input1 = InOptions(4);
    clrscr();
    char path[] = {"testdata2\\\\"};
    strcat(path, subject[input1 - 1]); // noi strings tao thanh path toi file mon hoc
    strcat(path, ".txt");
    FILE *file1;
    // in ra danh sach va diem cua mon hoc
    FILE *file2;
    file1 = fopen(path, "r");
    if (file1 == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    file2 = fopen("testdata2\\DSSV.txt", "r");
    if (file2 == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    char *str[MAX_NUMBER_OF_STUDENTS];
    unsigned short int i = 0;
    fseek(file1, 16, SEEK_SET); // bo qua dong 1
    while (fgets(line1, 43, file1))
    { // lay du lieu tu file mon hoc va truyen vao mang str
        str[i] = malloc(strlen(line1) + 1);
        strcpy(str[i], line1);
        i++;
    }
    int k = i;
    i--;
    char *c, line2copy[MAX_LINE_LENGTH], line1copy[MAX_LINE_LENGTH];
    printf("ID  Name                          Lab          Exercise     Diligence      Mid-term       Final\n");
    while (fgets(line2, MAX_LINE_LENGTH, file2))
    {
        line2[33] = '\0';
        unsigned short int check = 0;
        strcpy(line2copy, line2); // tao copy de tranh huy hoai du lieu cua line2
        token2 = strtok(line2, ",");
        for (int pos = 0; pos <= i; pos++)
        {                            // lay ID tu file mon hoc va compare voi ID trong danh sach sinh vien
            strcpy(line1, str[pos]); // sau khi compare xong thi chuyen sinh vien vua duoc compare xuong duoi
            strcpy(line1copy, line1);
            token1 = strtok(line1, ","); // va chuyen sinh vien truoc sinh vien duoc chuyen len tren
            if (strcmp(token1, token2))
                continue;
            c = str[pos];
            str[pos] = str[i];
            str[i] = c;
            i--;
            check = 1;
            break;
        }
        if (!check)
            continue;
        token2 = strtok(line2copy, ",");
        printf("%s  ", token2); // print ID
        token2 = strtok(NULL, ",");
        printf("%-30s", token2); // print Name
        token1 = strtok(line1copy, ",");
        token1 = strtok(NULL, ","); // bo qua ID
        for (int i = 0; i < 5; i++)
        {
            printf("%-8s      ", token1);
            token1 = strtok(NULL, ",");
        }
        printf("\n\n");
    }
    for (int i = 0; i < k; i++)
    {
        free(str[i]);
    }
    // check ID sinh vien co ton tai ko
    char ID[9];
    unsigned short int check = 0;
    printf("-----------------------------------------------------------------------\nCo the nhap nhieu lan cho 1 sinh vien\nCot diem da nhap khong the nhap lai lan nua\nSua diem o menu\nNhap 6 de thoat vong lap sau khi nhap ID\n-----------------------------------------------------------------------\n");
    printf("Type in ID: ");
    scanf("%s", ID);
    file1 = fopen(path, "r");
    if (file1 == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    while (fgets(line1, MAX_LINE_LENGTH, file1) && check == 0)
    {
        token1 = strtok(line1, ",");
        if (strcmp(token1, ID))
            continue;
        check = 1;
        break;
    }
    if (!check)
    {
        printf("ID does not exist\n");
        refreshcreen();
        return 1;
    }
    fclose(file1);

    int input2, stop = 0;
    char marks[5][20] = {"Lab", "Exercise", "Diligence", "Mid-term", "Final"};
    for (int i = 1; i < 6; i++)
    {
        printf("%d.%s   ", i, marks[i - 1]); // print cac lua chon mon hoc
    }
    printf("6.close");
    while (!stop)
    {
        printf("\nSelect scores section or close: ");
        input2 = InOptions(6);
        if (input2 == 6)
        {
            fclose(file1);
            refreshcreen();
            return 1;
        }
        // tim vi tri can sua diem
        int pointed = -input2, seekn = 0, limit = 0;
        file1 = fopen(path, "r+");
        if (file1 == NULL)
        {
            printf("Failed to open file | File does not exist\n");
            refreshcreen();
            return 0;
        }
        fseek(file1, 16, SEEK_SET); // bo qua dong 1
        while (fgets(line1, MAX_LINE_LENGTH, file1))
        {
            strcpy(line2, line1);
            token1 = strtok(line1, ",");
            if (strcmp(token1, ID))
            {
                seekn += 43;
                continue;
            }
            for (int i = 0; i < input2; i++)
            {
                seekn += strlen(token1) + 1;
                token1 = strtok(NULL, ",");
            };
            for (int i = 0; i < strlen(token1); i++)
                if ((int)token1[i] == 46)
                    limit++; // xem thu cot diem do da nhap het hay chua
            break;
        }
        if (limit == 1)
        {
            printf("Reached limited number of scores | Change scores in Sua diem\n");
            continue;
        }
        float a;
        printf("Type score you want to add in %s: ", marks[input2 - 1]);
        scanf("%f", &a);
        a = InScore(a);                     // lay diem nhap vao
        fseek(file1, seekn + 16, SEEK_SET); // dua con tro SEEK den vi tri can nhap diem
        fputs(NumberAlike(a), file1);
        fclose(file1);
    }
    refreshcreen();
}

int Suadiem() {
    clrscr();
    unsigned short int input1;
    char line2[MAX_LINE_LENGTH], line1[MAX_LINE_LENGTH], *token1, *token2;
    char subject[4][10] = {"Anh", "DSTT", "Toan", "Triet"};
    for (int i = 0; i < 4; i++)
    {
        printf("%d.%s   ", i + 1, subject[i]);
    }
    printf("\nSelect subject: ");
    input1 = InOptions(4);
    clrscr();
    char path[] = {"testdata2\\\\"};
    strcat(path, subject[input1 - 1]); // noi strings tao path den mon hoc
    strcat(path, ".txt");
    FILE *file1;
    // in ra man hinh bang diem mon hoc
    FILE *file2;
    file1 = fopen(path, "r");
    if (file1 == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    file2 = fopen("testdata2\\DSSV.txt", "r");
    if (file2 == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    char *str[MAX_NUMBER_OF_STUDENTS];
    unsigned short int i = 0;
    fseek(file1, 16, SEEK_SET); // bo qua dong 1
    while (fgets(line1, 43, file1))
    { // lay du lieu tu file mon hoc va truyen vao mang str
        str[i] = malloc(strlen(line1) + 1);
        strcpy(str[i], line1);
        i++;
    }
    int k = i;
    i--;
    char *c, line2copy[MAX_LINE_LENGTH], line1copy[MAX_LINE_LENGTH];
    printf("ID  Name                          Lab          Exercise     Diligence      Mid-term       Final\n");
    while (fgets(line2, MAX_LINE_LENGTH, file2))
    {
        line2[33] = '\0';
        unsigned short int check = 0;
        strcpy(line2copy, line2); // tao copy de tranh huy hoai du lieu cua line2
        token2 = strtok(line2, ",");
        for (int pos = 0; pos <= i; pos++)
        {                            // lay ID tu file mon hoc va compare voi ID trong danh sach sinh vien
            strcpy(line1, str[pos]); // sau khi compare xong thi chuyen sinh vien vua duoc compare xuong duoi
            strcpy(line1copy, line1);
            token1 = strtok(line1, ","); // va chuyen sinh vien truoc sinh vien duoc chuyen len tren
            if (strcmp(token1, token2))
                continue;
            c = str[pos];
            str[pos] = str[i];
            str[i] = c;
            i--;
            check = 1;
            break;
        }
        if (!check)
            continue;
        token2 = strtok(line2copy, ",");
        printf("%s  ", token2); // print ID
        token2 = strtok(NULL, ",");
        printf("%-30s", token2); // print Name
        token1 = strtok(line1copy, ",");
        token1 = strtok(NULL, ","); // bo qua ID
        for (int i = 0; i < 5; i++)
        {
            printf("%-8s      ", token1);
            token1 = strtok(NULL, ",");
        }
        printf("\n\n");
    }
    for (int i = 0; i < k; i++)
    {
        free(str[i]);
    }
    // check ID sinh vien co ton tai hay ko
    printf("-----------------------------------------------------------------------\nCo the sua nhieu lan cho 1 sinh vien\nCot diem trong khong the sua diem\nNhap diem o menu\nNhap 6 de thoat vong lap sau khi nhap ID\n-----------------------------------------------------------------------\n");
    char ID[9];
    printf("Type in ID: ");
    scanf("%s", ID);
    unsigned short int check = 0;
    file1 = fopen(path, "r");
    if (file1 == NULL)
    {
        printf("Failed to open file | File does not exist\n");
        refreshcreen();
        return 0;
    }
    fgets(line1, MAX_LINE_LENGTH, file1);
    while (fgets(line1, MAX_LINE_LENGTH, file1) && check == 0)
    {
        token1 = strtok(line1, ",");
        if (strcmp(token1, ID))
            continue;
        check = 1;
        break;
    }
    if (!check)
    {
        printf("ID does not exist\n");
        refreshcreen();
        return 1;
    }
    fclose(file1);

    char marks[5][20] = {"Lab", "Exercise", "Diligence", "Mid-term", "Final"};
    for (int i = 1; i < 6; i++)
    {
        printf("%d.%s   ", i, marks[i - 1]); // in ra cac lua chon mon hoc
    }
    printf("6.close");

    unsigned short int input2, stop = 0;
    while (!stop)
    {
        printf("\nSelect scores section or close: ");
        input2 = InOptions(6); // lay cot diem can sua
        if (input2 == 6)
        {
            fclose(file1);
            refreshcreen();
            return 1;
        }
        int pointed = -input2, seekn = 0, locate = 0, rep;
        float a;
        file1 = fopen(path, "r+");
        if (file1 == NULL)
        {
            printf("Failed to open file | File does not exist\n");
            refreshcreen();
            return 0;
        }
        fgets(line1, MAX_LINE_LENGTH, file1); // bo qua dong 1
        while (fgets(line1, MAX_LINE_LENGTH, file1))
        { // tim sinh vien trong danh sach
            strcpy(line2, line1);
            token1 = strtok(line1, ",");
            if (strcmp(token1, ID))
            {
                seekn += 43;
                continue;
            } // lay vi tri can sua string
            for (int i = 0; i < input2; i++)
            {
                seekn += strlen(token1) + 1;
                token1 = strtok(NULL, ",");
            };
            break;
        }
        for (int i = 0; i < strlen(token1); i++)
            if ((int)token1[i] == 46)
                locate++; // coi co bao nhieu diem trong cot
        if (locate == 0)
        {
            printf("There're no scores to change | Add score in Nhap diem\n");
            continue;
        }
        printf("Replace %s with: ", token1);
        scanf("%f", &a);
        a = InScore(a);                     // lay diem thay the
        fseek(file1, seekn + 16, SEEK_SET); // dua con tro SEEK den vi tri can sua
        fputs(NumberAlike(a), file1);       // dua du lieu can sua vao
        fclose(file1);
    }
    refreshcreen();
}

char *grading(float n) { // chuyen diem he 10 sang diem chu
    if (n < 4)
        return "(F)";
    char *grade[5] = {"(D)", "(C)", "(B)", "(A)", "(A)"};
    return grade[(int)((n - 4) / 1.5 + 0.01)];
}

int Sapxep() {
    char line[MAX_LINE_LENGTH], *token1, *token2, *pend, cal[15];
    char subject[4][10] = {"Anh", "DSTT", "Toan", "Triet"};
    float x, s, mul[5];
    for (int i = 0; i < 4; i++)
    {
        char path[] = {"testdata2\\\\"};
        strcat(path, subject[i]); // noi strings tao path
        strcat(path, ".txt");
        FILE *file;
        file = fopen(path, "r+");
        if (file == NULL)
        {
            printf("Failed to open file | File does not exist\n");
            refreshcreen();
            return 0;
        }
        fgets(cal, 15, file); // lay du lieu dong 1
        token1 = strtok(cal, ",");
        for (int i = 0; i < 5; i++)
        {
            x = strtof(token1, &pend); // chuyen string thanh float
            mul[i] = x;
            token1 = strtok(NULL, ","); // cac float vua duoc them vao mang "mul" la cac he so tinh diem
        }
        fseek(file, 16, SEEK_SET);
        char *str1[MAX_NUMBER_OF_STUDENTS][6]; // mang chua du lieu cua sinh vien
        float sor[MAX_NUMBER_OF_STUDENTS][2];  // mang dung de sort theo diem cao -> thap
        int i = 0, j;
        while (fgets(line, MAX_LINE_LENGTH, file))
        {
            line[32] = '\0';
            token1 = strtok(line, ",");
            str1[i][0] = malloc(strlen(token1) + 1); // lay du lieu truyen vao mang str1
            strcpy(str1[i][0], token1);
            for (int j = 1; j < 6; j++)
            {
                token1 = strtok(NULL, ",");
                str1[i][j] = malloc(strlen(token1) + 1);
                strcpy(str1[i][j], token1);
            }
            i++;
        }
        int k = i;
        char str1cpy[5]; // optimizeable ?  5 cot diem thi string du lieu lay ra co chieu dai max la 23
        for (int f = 0; f < k; f++)
        { // khong biet co the toi uu ko vi chiem qua nhieu du lieu
            s = 0;
            x = strtof(str1[f][1], &pend);
            s += x * mul[0]; // s += Diligence
            x = strtof(str1[f][2], &pend);
            s += x * mul[1]; // s += Diligence
            x = strtof(str1[f][3], &pend);
            s += x * mul[2]; // s += Diligence
            x = strtof(str1[f][4], &pend);
            s += x * mul[3]; // s += Midterm
            x = strtof(str1[f][5], &pend);
            s += x * mul[4];
            s /= 100; // s += Final
            sor[f][0] = f;
            sor[f][1] = s; // chuyen du lieu vao mang sor de sort
        }
        quickSort(sor, 0, k - 1);
        fseek(file, 16, SEEK_SET); // chuyen vi tri con tro seek den dong 2
        for (int l = 0; l < k; l++)
        { // tao thanh string hoan chinh cua sinh vien (ID,Lab,Exs,Diligence,Midterm,Final,Average)
            char out[45] = "";
            for (int f = 0; f < 6; f++)
            {
                strcat(out, str1[(int)sor[l][0]][f]);
                strcat(out, ",");
            }
            strcat(out, NumberAlike(sor[l][1]));
            strcat(out, grading(sor[l][1])); // optimizable ?
            strcat(out, "\n");
            fputs(out, file);
        }
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < 6; j++)
            { // giai phong du lieu tu cac con tro
                free(str1[i][j]);
            }
        }
        fclose(file);
    }
}

void action() {
    int input;
    while (1)
    {
        Sapxep();
        scanf("%d", &input);
        if (input == 7)
        {
            printf("Exit successfully");
            break;
        }
        switch (input)
        {
        case 1:
            Nhapdiem();
            break;

        case 2:
            Xemdiem();
            break;

        case 3:
            Suadiem();
            break;

        case 4:
            Sapxep();
            clrscr();
            printf("Sap xep thanh cong\n");
            refreshcreen();
            break;

        case 5:
            Indanhsach(0);
            break;

        case 6:
            ChinhHeSo();
            break;

        default:
            printf("Option does not exist | press anything to continue");
            getch();
            clrscr();
            menu();
            break;
            break;
        }
    }
}

int main() {
    menu();
    action();
    return 0;
}