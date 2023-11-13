#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int date, month, year, amount, balance = 0;
  char s1[10] = "new_entry";
  char s2[10] = "show_file";
  char s3[10] = "exit";
  char s4[10] = "credit";
  char s5[10] = "debit";
  char command[10];
  char type[10];
  char cause[500];
  char buf, d;

  FILE *ptr;
  FILE *f;
  f = fopen("balance.txt", "r+");
  fscanf(f, "%d", &balance);
  fclose(f);

  while (strcmp(command, s1) != 0 && strcmp(command, s2) != 0 &&
         strcmp(command, s3) != 0) // to ensure legit command
  {
    printf("\n enter command : ");
    scanf("%s", command);
    scanf("%c", &buf);                          // to counter stdin buffer
    for (int i = 0; i < (strlen(command)); i++) // to handle weird inputs
    {
      command[i] = tolower(command[i]);
    }
  }
  while (strcmp(command, s1) == 0 ||
         strcmp(command, s2) == 0) // for all except "exit"
  {
    while (strcmp(command, s1) == 0 &&
           strcmp(command, s2) != 0) // for "new_entry"
    {
      printf("\n enter transaction type : ");
      scanf("%s", type);
      scanf("%c", &buf);                       // to counter stdin buffer
      for (int i = 0; i < (strlen(type)); i++) // to handle weird inputs
      {
        type[i] = tolower(type[i]);
      }
      if (strcmp(type, s3) == 0) {
        exit(0);
      }
      while (strcmp(type, s4) != 0 && strcmp(type, s5) != 0) {
        printf("\n invalid input. \n ");
        printf("\n enter transaction type : ");
        scanf("%s", type);
        scanf("%c", &buf);
      }

      printf("\n enter transaction amount(in Rs.) = ");
      scanf("%d", &amount);
      if (strcmp(type, s4) == 0) {
        balance += amount;
      }
      if (strcmp(type, s5) == 0) {
        balance -= amount;
      }

      printf("\n enter date = ");
      scanf("%d", &date);
      while (date > 31 || date < 1) {
        printf("\n invalid date. \n ");
        printf("\n enter date = ");
        scanf("%d", &date);
      }

      printf("\n enter month number = ");
      scanf("%d", &month);
      while (month > 31 || month < 1) {
        printf("\n invalid month. \n ");
        printf("\n enter month number = ");
        scanf("%d", &month);
      }

      printf("\n enter year = ");
      scanf("%4d", &year);
      scanf("%c", &buf);
      while (year < 2022) {
        printf("\n invalid year. \n");
        printf("\n enter year = ");
        scanf("%d", &year);
        scanf("%c", &buf);
      }

      scanf("%c", &buf);
      printf("\n enter cause : ");
      scanf("%[^\n]s", cause);
      scanf("%c", &buf);

      ptr = fopen("expenses.txt", "a+");

      fprintf(ptr, "\n\n ~date = %d/%d/%d ", date, month, year);

      if (strcmp(type, s4) == 0) {
        fprintf(ptr, "\n ~Rs.%d was credited. ", amount);
      } else if (strcmp(type, s5) == 0) {
        fprintf(ptr, "\n ~Rs.%d was debited. ", amount);
      }
      fprintf(ptr, "\n ~cause : ");
      for (int i = 0; i < strlen(cause); i++) {
        d = cause[i];
        fprintf(ptr, "%c", d);
      }
      fprintf(ptr, "\n ~balance = Rs. %d ", balance);
      fclose(ptr);
      f = fopen("balance.txt", "w");
      fprintf(f, "%d", balance);
      fclose(f);

      printf("\n enter command : ");
      scanf("%s", command);
      scanf("%c", &buf); // to counter stdin buffer

      for (int i = 0; i < (strlen(command)); i++) // to handle weird inputs
      {
        command[i] = tolower(command[i]);
      }
      while (strcmp(command, s1) != 0 && strcmp(command, s2) != 0 &&
             strcmp(command, s3) != 0) // to ensure legit command
      {
        printf("\n enter command : ");
        scanf("%s", command);
      }
    }

    while (strcmp(command, s1) != 0 && strcmp(command, s2) == 0 &&
           strcmp(command, s3) != 0) // for "show_file"
    {
      ptr = fopen("expenses.txt", "r");
      printf("\n");

      char c = '0'; /* if c isn't initialised arbitrarily,then once show_file is
                       done,c would be = EOF and thus the next loop would never
                       start again.took so long to figure out! */
      while (c != EOF) {
        c = fgetc(ptr);
        fprintf(stdout, "%c", c);
      }
      fclose(ptr);
      printf("\n");
      printf("\n enter command : ");
      scanf("%s", command);
      scanf("%c", &buf); // to counter stdin buffer

      for (int i = 0; i < (strlen(command)); i++) // to handle weird inputs
      {
        command[i] = tolower(command[i]);
      }
      while (strcmp(command, s1) != 0 && strcmp(command, s2) != 0 &&
             strcmp(command, s3) != 0) // to ensure legit command
      {
        printf("\n enter command : ");
        scanf("%s", command);
      }
    }
  }
  if (strcmp(command, s1) != 0 && strcmp(command, s2) != 0 &&
      strcmp(command, s3) == 0) // for 'exit_file'
  {
    exit(0);
  }
  return 0;
}


