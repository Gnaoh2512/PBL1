#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_LINE_LENGTH 40

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
int Xemdiem() {
    char subject[4][10] = {"Anh","DSTT","Toan","Triet"};
    FILE *file;
    int check = 0;
    char ID[9], line[MAX_LINE_LENGTH], *token;

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
    printf("Subjects        Labs            Exercises       Diligence       Mid-term        Final\n");
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
                    if ((int) token[1] != 10) printf("%-10s      ",token);
                    else printf("%c",token[0]);
                }
            }
            printf("\n");
            break; // lay duoc du lieu roi thi out vong lap
        }
    }
    fclose(file);
    refreshcreen();
}

void Indanhsach() {
    clrscr();
    char subject[4][10] = {"Triet","Toan","Anh","DSTT"};
    FILE *file;
    char ID[9], line[MAX_LINE_LENGTH], *token;
    file = fopen("testdata\\DSSV.txt", "r");
    printf("ID  Ho ten                        Anh        DSTT       Toan       Triet\n");
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        token = strtok(line,",");
        printf("%s  ",token);
        token = strtok(NULL,",");
        printf("%-30s",token);
        while(token != NULL) {
            token = strtok(NULL,",");
            if (token != NULL) {
                if ((int) token[1] != 10) printf("%-5s      ",token);
                else printf("%c",token[0]);
            }
        } printf("\n");
    }
    refreshcreen();
}
void action() {
    int input;
    while (1 != 0) {
        scanf("%d",&input);
        if (input == 6) {printf("Enter key is typed"); break;}
        switch (input) {
        // case 1: Nhapdiem();
        // break;

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