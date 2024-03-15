#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_LINE_LENGTH 83

void menu() {
    printf("1-Nhap diem. \n");
    printf("2-Xem diem. \n");
    printf("3-Sua diem. \n");
    printf("4-Sap xep. \n");
    printf("5-In ra danh sach. \n");
    printf("6-Thoat. \n");
}

void clrscr() { //clear man hinh
    #ifdef _WIN32 
        system("cls");
    #elif (__APPLE__ || __linux__)
        system("clear");
    #endif
}

void refreshcreen() { //buffer clear man hinh
    printf("Press anything to continue\n");
    getch();
    clrscr();
    menu();
}

void StringAlike(char *str,int num_of_spaces) {
    int len = strlen(str);
    memset(str+len, ' ', num_of_spaces );   
    str[len + num_of_spaces] = '\0';
}

char * NumberAlike(float a) {
    char c[7];
    char * score = (char *)malloc(10 * sizeof(char));
    score[0] = '\0';
    if (a == 10) return "10.00";
    strcat(score,"0");
    sprintf(c,"%g",a);
    strcat(score,c);
    if (strlen(score) == 4) strcat(score,"0");
    if (!(a - (int)a)) strcat(score,".00");
    return score;
}

int Xemdiem() {
    char subject[4][10] = {"Anh","DSTT","Toan","Triet"};
    FILE *file;
    int check = 0;
    char ID[9], line[MAX_LINE_LENGTH], *token;
    char test[20];
    // nhap ID
    printf("nhap ma sinh vien: ");
    scanf("%s",ID);

    // check DSSV co ID ko
    file = fopen("testdata\\DSSV.txt", "r");
    while (fgets(line, MAX_LINE_LENGTH, file) && check == 0) {
        token = strtok(line,",");
        if (strcmp(token,ID)) continue;
        else {
            token = strtok(NULL,",");
            printf("Ho ten: %s\n",token);
            check = 1;break;
    }}
    if (!check) {printf("Khong tim thay sinh vien\n");refreshcreen(); return 1;}
    // print thong tin
    printf("Subjects        Labs                         Exercises                    Diligence                    Mid-term                     Final\n");
    for (int i = 0; i < 4; i++) {
        char path[] = {"testdata\\\\"};
        strcat(path,subject[i]); // noi strings
        strcat(path,".txt");
        file = fopen(path, "r");
        if (!file) {
            perror(path); // bao loi neu ko mo dc file hay ko co file
            return EXIT_FAILURE;
        }
        /* lay tung line 1 */
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            /* split */
            token = strtok(line, ",");
            if(strcmp(token,ID)) continue;
            // strcmp tra ve 0 neu nhu 2 string = nhau; so sanh ID du lieu va ID nhap vao co bang nhau ko
            printf("%-8s        ",subject[i]);
            // chay qua het string
            while(token != NULL) {
                token = strtok(NULL,",");
                if (token != NULL) {
                    if ((int) token[5] == 10) printf("%s",token);
                    else printf("%-23s      ",token);
                }
            }
            break; // lay duoc du lieu roi thi out vong lap
        }
    }
    fclose(file);
    refreshcreen();
}

void Indanhsach() {
    clrscr();
    FILE *file;
    int i;
    char ID[9], line[MAX_LINE_LENGTH], *token;
    file = fopen("testdata\\DSSV.txt", "r");
    printf("ID  Ho ten                           Anh         DSTT        Toan        Triet       test        test        test        test\n");
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        token = strtok(line,",");
        printf("%s  ",token); 
        token = strtok(NULL,",");
        if (token == NULL) continue;
        printf("%-30s   ",token);
        while(token != NULL) {
            token = strtok(NULL,",");
            if (token == NULL) continue;
            if ((int) token[5] == 10) printf("%s",token);
            else printf("%-5s       ",token);
        }
    }
    fclose(file);
    refreshcreen();
}

int Nhapdiem() {
    int input1;
    char line2[MAX_LINE_LENGTH],line1[MAX_LINE_LENGTH],*token1,*token2;
    char subject[4][10] = {"Triet","Toan","Anh","DSTT"};
    for (int i = 1; i < 5; i++) {
        printf("%d.%s   ",i,subject[i-1]);
    }
    printf("\nChon mon hoc: "); scanf("%d",&input1);
    clrscr();
    char path[] = {"testdata\\\\"};
    strcat(path,subject[input1-1]); // noi strings
    strcat(path,".txt");
    FILE *file1,*file2;
    file1 = fopen(path, "r+");
    file2 = fopen("testdata\\DSSV.txt", "r");
    printf("ID  Ho ten                         Labs                     Exercises                    Diligence     Mid-term      Final\n");
    while (fgets(line1, MAX_LINE_LENGTH, file1) && fgets(line2, MAX_LINE_LENGTH, file2)) {
        token2 = strtok(line2,",");
        printf("%s  ",token2);
        token2 = strtok(NULL,",");
        printf("%-30s ",token2);
        token1 = strtok(line1,",");
        token1 = strtok(NULL,",");
        printf("%-8s  ",token1);
        while(token1 != NULL) {
            token1 = strtok(NULL,",");
            if (token1 != NULL) {
                if ((int) token1[1] != 10) printf("%-8s      ",token1);
                else printf("%c",token1[0]);
            }
        } printf("\n");
    }
    fclose(file1);fclose(file2);
    char ID[9];
    printf("nhap ma sinh vien: ");
    scanf("%s",ID);
    int check = 0;
    file2 = fopen("testdata\\DSSV.txt", "r");
    while (fgets(line1, MAX_LINE_LENGTH, file2) && check == 0) {
        token1 = strtok(line1,",");
        if (strcmp(token1,ID)) continue;
        token1 = strtok(NULL,",");
        printf("Ho ten: %s\n",token1);
        check = 1;break;
    }
    if (!check) {printf("Khong tim thay sinh vien\n");refreshcreen(); return 1;}

    char marks[5][20] = {"Labs","Exercises","Diligence","Mid-term","Final"};
    for (int i = 1; i < 6; i++) {
        printf("%d.%s   ",i,marks[i-1]);
    }
    fclose(file1);fclose(file2);
    int input2;
    printf("\nCot diem can nhap: "); scanf("%d",&input2);
    int pointed = -input2,seekn = 0;
    file1 = fopen(path,"r+");
    char a[MAX_LINE_LENGTH] = "", *b;
    while(fgets(line1, MAX_LINE_LENGTH, file1)) {
        strcpy(line2,line1);
        check = strlen(line1) - 1;
        token1 = strtok(line1,",");
        if (strcmp(token1,ID)) {seekn += check; continue;}
        break;
    }
    int i1 = 0, i2 = 0;
    while(pointed < 1 && i2 != check) {
        if (pointed < 0) i1++;
        i2++;
        if ((int)line2[i1] == 44 && (int)line2[i2] == 44) pointed++;
    }
    if (input2 == 5) i2 = i1 + 5;
    memcpy(a,line2,i1+1);
    b = strstr(line2,a) + i2;
    int input3 = input2;
    if (input2 == 1 || input2 == 2) {
        printf("So diem can nhap(Max = 4): ");
        scanf("%d",&input3);
    } else input3 = 1;
    char scores[50] = "";float s;
    for (int i = 0; i < input3; i++) {
        if (input2 == 1 || input2 == 2) printf("%s[%d]: ",marks[input2-1],i+1);
        else printf("%s: ",marks[input2-1]);
        scanf("%f",&s);
        strcat(scores,NumberAlike(s));
        if (!(i == input3 -1)) strcat(scores," ");
    }
    if (input2 < 3) StringAlike(scores,23-strlen(scores));
    else StringAlike(scores,5-strlen(scores));
    strcat(a,scores);
    strcat(a,b);
    fseek(file1,seekn,SEEK_SET);
    fputs(a,file1);
    fclose(file1);
    fclose(file2);
    refreshcreen();
}
void action() {
    int input;
    while (1 != 0) {
        scanf("%d",&input);
        if (input == 6) {printf("Enter key is typed"); break;}
        switch (input) {
        case 1: Nhapdiem();
        break;

        case 2: Xemdiem();
        break;

        // case 3: Suadiem();
        // break;

        // case 4: Sapxep();
        // break;

        case 5: Indanhsach();
        break;

        default: clrscr();menu();
        break;
        }
    }
}

int main() {
    menu();
    action();
    return 0;
}