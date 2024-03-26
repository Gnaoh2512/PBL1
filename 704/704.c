#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 80
#define MAX_NUMBER_OF_STUDENTS 60

void menu() {
    printf("1-Nhap diem. \n2-Xem diem. \n3-Sua diem. \n4-Sap xep. \n5-In ra danh sach. \n6-Thoat. \n");
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

int InOptions(int n) {
    int input;scanf("%d",&input);
    while (input < 1 || input > n) {printf("khong co trong cac lua chon | nhap lai lua chon: ");scanf("%d",&input);}
    return input;
}

char *NumberAlike(float a) { // bien diem nhap vao thanh string dang xx.xx
    a = ceilf(a * 100) / 100;
    char c[7];
    char * score = (char *)malloc(10 * sizeof(char));
    score[0] = '\0';
    if (a >= 10) return "10.00";
    strcat(score,"0");
    sprintf(c,"%g",a);
    strcat(score,c);
    if (strlen(score) == 4) strcat(score,"0");
    if (!(a - (int)a)) strcat(score,".00");
    return score;
}
void swap(float *a, float *b) {
  float t = *a;
  *a = *b;
  *b = t;
}
void printArray(float array[][2], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%f  %f\n", array[i][0],array[i][1]);
  }
  printf("\n");
}
int partition(float array[][2], int low, int high) {
  float pivot = array[high][1];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j][1] >= pivot) {
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
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

void Indanhsach(int z) {
    clrscr();
    FILE *file1;
    int i;
    char ID[3], line1[MAX_LINE_LENGTH], *token1;
    if(z>0) i=2;
    else if (z == -1) i=1;
    else {printf("Danh sach can xem\n1. Danh sach sinh vien    2.Danh sach mon hoc\n");i = InOptions(2);}
    if(i == 1) {
        file1 = fopen("testdata\\DSSV.txt", "r");
        printf("ID  Ho ten\n");
        while (fgets(line1, MAX_LINE_LENGTH, file1)) {
            token1 = strtok(line1,",");
            printf("%s  ",token1); 
            token1 = strtok(NULL,",");
            if (token1 == NULL) continue;
            printf("%s",token1);
        }
        printf("\n");
        fclose(file1);
    } else if (i == 2) {
        char subject[4][10] = {"Anh","DSTT","Toan","Triet"};
        int input1;
        if (!z) {
            for (int i = 1; i < 5; i++) {
                printf("%d.%s   ",i,subject[i-1]);
            }
            printf("\nChon mon hoc: "); input1 = InOptions(4);
        } else input1 = z;
        clrscr();
        char path[] = {"testdata\\\\"};
        strcat(path,subject[input1-1]); // noi strings tao thanh path toi file mon hoc
        strcat(path,".txt");
        FILE *file2;
        char line2[MAX_LINE_LENGTH], *token2;
        file1 = fopen(path, "r");
        fseek(file1,13,SEEK_SET); // bo qua dong 1
        file2 = fopen("testdata\\DSSV.txt", "r");
        char *str1[MAX_NUMBER_OF_STUDENTS]; int i = 0;
        while(fgets(line2, MAX_LINE_LENGTH, file2)) {
            str1[i] = malloc(strlen(line2) + 1);
            line2[33] = '\0';
            strcpy(str1[i], line2);
            i++;
        }
        int k = i;i--;
        char *c, line1copy[MAX_LINE_LENGTH];
        printf("ID  Ho ten                        Labs                         Exercises                    Diligence     Mid-term      Final         Average\n");
        while (fgets(line1, MAX_LINE_LENGTH, file1)) {
            int check = 0;
            strcpy(line1copy,line1);
            token1 = strtok(line1,",");
            for (int pos = 0; pos <= i; pos++) {
                strcpy(line2,str1[pos]);
                token2 = strtok(line2,",");
                if (strcmp(token1,token2)) continue;
                c = str1[pos];
                str1[pos] = str1[i];
                str1[i] = c;
                i--;
                check = 1;
                break;
            }
            if (!check) continue;
            printf("%s  ",token2);
            token2 = strtok(NULL,",");
            printf("%-30s",token2);
            token1 = strtok(line1copy,",");
            while(token1 != NULL) {
                token1 = strtok(NULL,",");
                if (token1 != NULL) printf("%-8s      ",token1);
            } printf("\n");
        }
        for (int i = 0; i < k; i++) {
            free(str1[i]);
        }
    }
    if (!z) refreshcreen();
}

int Xemdiem() {
    char subject[4][10] = {"Anh","DSTT","Toan","Triet"};
    FILE *file;
    int check = 0;
    char ID[9], line[MAX_LINE_LENGTH], *token;
    char test[20];
    
    Indanhsach(-1);
    // nhap ID
    printf("nhap ma sinh vien: ");scanf("%s",ID);

    // check DSSV co ID ko
    file = fopen("testdata\\DSSV.txt", "r");
    while (fgets(line, MAX_LINE_LENGTH, file) && check == 0) {
        token = strtok(line,",");
        if (strcmp(token,ID)) continue;
        else {
            token = strtok(NULL,",");
            printf("Ho ten: %s",token);
            check = 1;break;
    }}
    if (!check) {printf("Khong tim thay sinh vien\n");refreshcreen(); return 1;}
    
    // print thong tin
    printf("Subjects        Labs                         Exercises                    Diligence    Mid-term     Final        Average\n");
    for (int i = 0; i < 4; i++) {
        char path[] = {"testdata\\\\"};
        strcat(path,subject[i]); // noi strings tao thanh path den file mon hoc
        strcat(path,".txt");
        file = fopen(path, "r");
        fgets(line, MAX_LINE_LENGTH, file); // bo qua dong 1
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            token = strtok(line, ",");
            if(strcmp(token,ID)) continue;
            // tim sinh vien trong file cac mon hoc
            printf("%-8s        ",subject[i]);
            for (int i = 0; i < 2; i++) {
                token = strtok(NULL,",");
                printf("%-23s      ",token);
            }
            for (int i = 0; i < 3; i++) {
                token = strtok(NULL,",");
                printf("%-s        ",token);
            }
            token = strtok(NULL,",");
            printf("%s",token);
            break; // lay duoc du lieu roi thi out vong lap
        }
    }
    fclose(file);
    refreshcreen();
}

int Nhapdiem() {
    int input1;
    char line2[MAX_LINE_LENGTH],line1[MAX_LINE_LENGTH],*token1,*token2;
    char subject[4][10] = {"Anh","DSTT","Toan","Triet"};
    for (int i = 1; i < 5; i++) {
        printf("%d.%s   ",i,subject[i-1]);
    }
    printf("\nChon mon hoc: "); input1 = InOptions(4);
    clrscr();
    char path[] = {"testdata\\\\"};
    strcat(path,subject[input1-1]); // noi strings tao thanh path toi file mon hoc
    strcat(path,".txt");
    FILE *file1;
    // in ra danh sach va diem cua mon hoc
    Indanhsach(input1);
    // check ID sinh vien co ton tai ko
    char ID[9]; int check = 0;
    printf("nhap ma sinh vien: ");scanf("%s",ID);
    file1 = fopen(path, "r");
    while (fgets(line1, MAX_LINE_LENGTH, file1) && check == 0) {
        token1 = strtok(line1,",");
        if (strcmp(token1,ID)) continue;
        check = 1;break;
    }
    if (!check) {printf("Khong tim thay sinh vien trong mon hoc nay hoac ID khong ton tai\n");refreshcreen(); return 1;}
    fclose(file1);

    char marks[5][20] = {"Labs","Exercises","Diligence","Mid-term","Final"};
    for (int i = 1; i < 6; i++) {
        printf("%d.%s   ",i,marks[i-1]);
    }

    int input2;
    printf("\nCot diem can nhap: "); input2 = InOptions(5);

    // tim vi tri can sua diem 
    int pointed = -input2, seekn = 0, limit = 0;
    file1 = fopen(path,"r+");
    fseek(file1,13,SEEK_SET); //bo qua dong 1
    while(fgets(line1, MAX_LINE_LENGTH, file1)) {
        strcpy(line2,line1);
        token1 = strtok(line1,",");
        if (strcmp(token1,ID)) {seekn += 79;continue;}
        for (int i = 0; i < input2; i++) {seekn += strlen(token1)+1;token1 = strtok(NULL,",");};
        for (int i = 0; i < strlen(token1); i++) if ((int)token1[i] == 46) limit++; // xem thu cot diem do da nhap het hay chua
        if ((limit == 4 && input2 < 3) || (limit == 1 && input2 >= 3))
        {printf("Reached limited number of scores\nChange scores in SuaDiem\n");refreshcreen();return 0;}
        break;
    }
    seekn +=limit*6; // lay vi tri can nhap diem
    float a;
    printf("Type score you want to add in %s: ",marks[input2-1]);scanf("%f",&a); // lay diem nhap vao
    fseek(file1,seekn + 13,SEEK_SET); // dua con tro SEEK den vi tri can nhap diem
    fputs(NumberAlike(a),file1);
    fclose(file1);
    refreshcreen();
}

int Suadiem() {
    int input1;
    char line2[MAX_LINE_LENGTH],line1[MAX_LINE_LENGTH],*token1,*token2;
    char subject[4][10] = {"Anh","DSTT","Toan","Triet"};
    for (int i = 1; i < 5; i++) {
        printf("%d.%s   ",i,subject[i-1]);
    }
    printf("\nChon mon hoc: "); input1 = InOptions(4);
    clrscr();
    char path[] = {"testdata\\\\"};
    strcat(path,subject[input1-1]); // noi strings tao path den mon hoc
    strcat(path,".txt");
    FILE *file1;
    // in ra man hinh bang diem mon hoc
    Indanhsach(input1);
    // check ID sinh vien co ton tai hay ko
    char ID[9];
    printf("nhap ma sinh vien: ");scanf("%s",ID);
    int check = 0;
    file1 = fopen(path,"r");
    fgets(line1, MAX_LINE_LENGTH, file1);
    while (fgets(line1, MAX_LINE_LENGTH, file1) && check == 0) {
        token1 = strtok(line1,",");
        if (strcmp(token1,ID)) continue;
        check = 1;break;
    }
    if (!check) {printf("Khong tim thay sinh vien trong nganh hoc nay hoac ID khong ton tai\n");refreshcreen(); return 1;}
    fclose(file1);

    char marks[5][20] = {"Labs","Exercises","Diligence","Mid-term","Final"};
    for (int i = 1; i < 6; i++) {
        printf("%d.%s   ",i,marks[i-1]); // in ra cac lua chon mon hoc
    }

    int input2;
    printf("\nCot diem can sua: "); input2 = InOptions(5); // lay cot diem can sua

    int pointed = -input2, seekn = 0, locate = 0, rep; float a;
    file1 = fopen(path,"r+");
    fgets(line1, MAX_LINE_LENGTH, file1); // bo qua dong 1
    while(fgets(line1, MAX_LINE_LENGTH, file1)) { // tim sinh vien trong danh sach
        strcpy(line2,line1);
        token1 = strtok(line1,",");
        if (strcmp(token1,ID)) {seekn += 79; continue;} // lay vi tri can sua string
        for (int i = 0; i < input2; i++) {seekn += strlen(token1)+1;token1 = strtok(NULL,",");};
        break;
    }
    if (input2 < 3) { // Labs,Exercises can lua chon diem can sua
        for (int i = 0; i < strlen(token1); i++) if ((int)token1[i] == 46) locate++; // coi co bao nhieu diem trong cot
        token1 = strtok(token1," ");
        printf("1. %s   ",token1); // in ra cac diem
        for (int i = 1; i < locate; i++) { // cho nay de fix bug
            token1 = strtok(NULL," ");
            printf("%d. %s   ",i+1,token1);
        }
        printf("\nType score you want to replace: "); rep = InOptions(locate); // lay diem thay the
    } else rep = 1; // Diligence,Midterm,Final ko can in nhieu lua chon
    printf("Replace score with: ");scanf("%f",&a); // lay diem thay the
    fseek(file1,seekn + 13 + (rep-1)*6,SEEK_SET); // dua con tro SEEK den vi tri can sua
    fputs(NumberAlike(a),file1); // dua du lieu can sua vao
    fclose(file1);
    refreshcreen();
}

char *grading(float n) {
    if (n < 4) return "F";
    char *grade[4] = {"D","C","B","A"};
    return grade[(int) ((n - 4)/1.5)];
}

void Sapxep() {
    char line[MAX_LINE_LENGTH],*token1,*token2,*pend,cal[11];
    char subject[4][10] = {"Anh","DSTT","Toan","Triet"};
    float x,s,mul[4];
    for (int i = 0; i < 4; i++) {
        char path[] = {"testdata\\\\"};
        strcat(path,subject[i]); // noi strings
        strcat(path,".txt");
        FILE *file;
        file = fopen(path, "r+");
        fgets(cal,12,file);
        token1 = strtok(cal,",");
        for (int i = 0; i < 4; i++) {
            x = strtof(token1,&pend);
            mul[i] = x;
            token1 = strtok(NULL,",");
        }
        fseek(file,13,SEEK_SET);
        char *str1[MAX_NUMBER_OF_STUDENTS][6];
        float sor[MAX_NUMBER_OF_STUDENTS][2];
        int i = 0,j;
        while(fgets(line, MAX_LINE_LENGTH, file)) {
            line[68] = '\0';
            token1 = strtok(line,",");
            str1[i][0] = malloc(strlen(token1) + 1);
            strcpy(str1[i][0], token1);
            for (int j = 1; j < 6;j++) {
                token1 = strtok(NULL,",");
                str1[i][j] = malloc(strlen(token1) + 1);
                strcpy(str1[i][j], token1);
            }
            i++;
        } int k = i;
        int count;
        char str1cpy[23]; //optimizeable ?
        for(int f = 0; f < k; f++) {
            count = 0; s = 0;
            for (int p = 1; p < 3; p++) {
                strcpy(str1cpy,str1[f][p]);
                token2 = strtok(str1cpy," ");
                while (token2 != NULL) {
                    count++;
                    x = strtof(token2,&pend);
                    s += x;
                    token2 = strtok(NULL," ");
                }
            }
            s/=count;
            x = strtof(str1[f][3],&pend);
            s = s*mul[0]+x*mul[1];
            x = strtof(str1[f][4],&pend);
            s += x*mul[2];
            x = strtof(str1[f][5],&pend);
            s += x*mul[3]; s/=100;
            sor[f][0] = f;
            sor[f][1] = s;
        }
        quickSort(sor,0,k-1);
        fseek(file,13,SEEK_SET);
        for (int l = 0; l < k; l++) {
            char out[76] = "";
            for(int f = 0; f < 6; f++) {strcat(out,str1[(int) sor[l][0]][f]);strcat(out,",");}
            strcat(out,NumberAlike(sor[l][1]));
            strcat(out,"(");
            strcat(out,grading(sor[l][1]));
            strcat(out,")");
            strcat(out,"\n");
            fputs(out,file);
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < 6; j++) {
                free(str1[i][j]);
            }
        }
    }printf("Sap xep thanh cong\n");refreshcreen();
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

        case 3: Suadiem();
        break;

        case 4: Sapxep();
        break;

        case 5: Indanhsach(0);
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