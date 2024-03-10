#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_LINE_LENGTH 40

void clrscr() {
    #ifdef _WIN32 
        system("cls");
    #elif (__APPLE__ || __linux__)
        system("clear");
    #endif
}

void menu() {
    printf("1-Nhap diem. \n");
    printf("2-Xem diem. \n");
    printf("3-Sua diem. \n");
    printf("4-Sap xep. \n");
    printf("5-In ra danh sach. \n");
    printf("6-Thoat. \n");
}
void refreshcreen() {
    printf("Press anything to continue\n");
    getch();
    clrscr();
    menu();
}
int Xemdiem() {
    char subject[4][10] = {"Triet","Toan","Anh","DSTT"};
    FILE *file;
    int check = 0;
    char ID[9], line[20], data[6][9];
    char *token;
    // check DSSV co ID ko
    printf("nhap ma sinh vien: ");
    scanf("%s",&ID);
    file = fopen("testdata\\DSSV", "r");
    while (fgets(line, MAX_LINE_LENGTH, file) && check == 0) {
        token = strtok(line," ");
        if (strcmp(token,ID)) continue;
        else {
            printf("Ho ten: ");
            while(token != NULL) {
                token = strtok(NULL," ");
                if (token != NULL) printf(" %s",token); //printing each token
            }
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
        while (fgets(line, MAX_LINE_LENGTH, file))
        {
        
        /* split */
        char *token = strtok(line, ",");
        if(strcmp(token,ID)) continue;
        // strcmp tra ve 0 neu nhu 2 string = nhau; so sanh ID du lieu va ID nhap vao co bang nhau ko
        printf("%-8s        ",subject[i]);
        // chay qua het string
        while(token != NULL) {
            token = strtok(NULL,",");
            (token != NULL)?printf("%-10s      ", token ):printf("\n"); //printing each token
        }
        break; // lay duoc du lieu roi thi out vong lap
        }
    }
    fclose(file);
    refreshcreen();
}

void action() {
    int input;
    while (1 != 0) {
    scanf("%d",&input);
    if (input == 6) {
    printf("Enter key is typed"); break;
    }
    switch (input)
    {
    // case 1: Nhapdiem();
    // break;

    case 2: Xemdiem();
    break;

    // case 3: Suadiem();
    // break;

    // case 4: Sapxep();
    // break;

    // case 5: Indanhsach();
    // break;
    }
    }
}
int main() {
    menu();
    action();
    return 0;
}