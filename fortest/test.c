#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

char *NumberAlike(float a) { // bien diem nhap vao thanh string dang xx.xx
    a = ceilf(a * 100) / 100;
    if (a >= 10) return "10.00";
    if (a <= 0) return "00.00";
    char c[7];
    char * score = (char *)malloc(10 * sizeof(char));
    score[0] = '\0';
    strcat(score,"0");
    sprintf(c,"%g",a);
    strcat(score,c);
    if (strlen(score) == 4) strcat(score,"0");
    if (!(a - (int)a)) strcat(score,".00");
    return score;
}

// Function to generate a random floating-point number between min and max
float random_float(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

// Function to generate a line in the specified format
void generate_line(FILE *file, int number) {
    // Generate sequences of hours for group 1 and group 2
    char group1_hours[50], group2_hours[50];
    float ran1 = random_float(0,10);
    float ran2 = random_float(0,10);
    if (ran1 < 2.5) sprintf(group1_hours, "%s                  ",NumberAlike(random_float(0,10)));
    else if (ran1 >= 2.5 && ran1 < 5) sprintf(group1_hours, "%s %s            ",NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)));
    else if (ran1 >= 5 && ran1 < 7.5) sprintf(group1_hours, "%s %s %s      ",NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)));
    else if (ran1 >= 7.5) sprintf(group1_hours, "%s %s %s %s",NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)));
    if (ran2 < 2.5) sprintf(group2_hours, "%s %s %s %s",NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)));
    else if (ran2 >= 2.5 && ran2 < 5) sprintf(group2_hours, "%s %s %s      ",NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)));
    else if (ran2 >= 5 && ran2 < 7.5) sprintf(group2_hours, "%s %s            ",NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)));
    else if (ran2 >= 7.5) sprintf(group2_hours, "%s                  ",NumberAlike(random_float(0,10)));
    char str[3] = "",temp[3]; 
    if (number < 10) strcat(str,"0");
    // Using sprintf to convert int to string
    sprintf(temp, "%d", number);strcat(str,temp);
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n",
            str, group1_hours, group2_hours, NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)), NumberAlike(random_float(0,10)));
}

int main() {
    int start_number = 10;
    int end_number = 50;
    
    // Open a file for writing
    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        perror("Failed to open file");
        return 1;
    }
    
    // Seed the random number generator with current time
    srand(time(NULL));
    
    // add Heso
    fprintf(output_file, "10,20,20,50\n");
    // Generate lines for numbers 41 to 90 and write them to the file
    for (int num = start_number; num <= end_number; num++) {
        generate_line(output_file, num);
    }
    
    // Close the file
    fclose(output_file);
    
    printf("Generated %d lines and wrote to 'output.txt'\n", end_number - start_number + 1);
    
    return 0;
}
