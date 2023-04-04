#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

regex_t regex;

int Update();
int Delete();
void Add();
int Search();
int ShowAll();
int Menu();
int regVerify();

struct contact {
  char *numarTelefon[100];
  char *prenumeContact[25];
  char *numeContact[25];
  char *adresaEmail[50];
};

struct contact listaContacte[100];
int k = 0;
int Menu() {
  while (1) {
    printf("%s",
           "1 - Add contact \n2 - Show all contacts \n3 - Update contact \n4 - "
           "Delete contact \n5 - Search by name/phone number \n0 - Exit \n");
    int y;
    scanf("%d", &y);
    switch (y) {
    case 0:
      return 0;
    case 1:
      Add();
      break;
    case 2:
      ShowAll();
      break;
    case 3:
      Update(-1);
      break;
    case 4:
      Delete(-1);
      break;
    case 5:
      Search();
      break;
    default:
      printf("%s", "\nGive a correct option!\n\n");
      break;
    }
  }
}
void Read() {
  FILE *fp = fopen("data.txt", "r");
  char row[255];
  char *token;
  int count = 0;
  struct contact cnt;

  while (fgets(row, sizeof(row), fp) != NULL && count <= k) {
    if (count == 0) {
      char c = row[0];
      k = c - '0';
    } else {
      token = strtok(row, " ");
      strcpy(cnt.numeContact, token);

      token = strtok(NULL, " ");
      strcpy(cnt.prenumeContact, token);

      token = strtok(NULL, " ");
      strcpy(cnt.numarTelefon, token);

      token = strtok(NULL, " \n");
      strcpy(cnt.adresaEmail, token);

      listaContacte[count - 1] = cnt;
    }
    count++;
  }
  fclose(fp);
}
void Write() {
  FILE *fp = fopen("data.txt", "w+");
  fprintf(fp, "%d", k);
  fputs("\n", fp);
  for (int i = 0; i < k; i++) {
    fputs(listaContacte[i].numeContact, fp);
    fputs(" ", fp);

    fputs(listaContacte[i].prenumeContact, fp);
    fputs(" ", fp);

    fputs(listaContacte[i].numarTelefon, fp);
    fputs(" ", fp);

    fputs(listaContacte[i].adresaEmail, fp);
    fputs("\n", fp);
  }
  fclose(fp);
}
int regVerify(char check[100], char type[10]) {
  if (strcmp(type, "Name") == 0) {
    int return_value = -1;
    return_value = regcomp(&regex, "^[a-zA-Z]+$", REG_EXTENDED);
    return_value += regexec(&regex, check, 0, NULL, 0);
    return return_value;
  } else if (strcmp(type, "Surname") == 0) {
    int return_value = -1;
    return_value = regcomp(&regex, "^[a-zA-Z]+$", REG_EXTENDED);
    return_value += regexec(&regex, check, 0, NULL, 0);
    return return_value;
  }
  if (strcmp(type, "Number") == 0) {
    int return_value = -1;
    return_value = regcomp(&regex, "^07[0123456789]{8}$", REG_EXTENDED);
    return_value += regexec(&regex, check, 0, NULL, 0);
    return return_value;
  } else if (strcmp(type, "Email") == 0) {
    int return_value = -1;
    return_value = regcomp(&regex, "^([a-zA-Z0-9_.-]+@[a-z]{4,8}.[a-z]{2,4})$",
                           REG_EXTENDED);
    return_value += regexec(&regex, check, 0, NULL, 0);
    return return_value;
  }
}

void Add() {
  struct contact c;
  char aux[100];

  printf("%s", "Name: \n");
  getchar();
  scanf("%s", &aux);

  while (regVerify(aux, "Name") != 0) {
    printf("%s", "Wrong format! Input only letters! \n");
    getchar();
    scanf("%s", &aux);
  }
  strcpy(c.numeContact, aux);

  printf("%s", "Surname: \n");
  getchar();
  scanf("%s", &aux);

  while (regVerify(aux, "Surname") != 0) {
    printf("%s", "Wrong format! Input only letters! \n");
    getchar();
    scanf("%s", &aux);
  }
  strcpy(c.prenumeContact, aux);

  printf("%s", "Phone number: (RO format)\n");
  getchar();
  scanf("%s", &aux);

  while (regVerify(aux, "Number") != 0) {
    printf("%s", "Wrong format! Input a Romanian phone number! \n");
    getchar();
    scanf("%s", &aux);
  }
  strcpy(c.numarTelefon, aux);

  printf("%s", "Email: \n");
  getchar();
  scanf("%s", &aux);

  while (regVerify(aux, "Email") != 0) {
    printf("%s", "Wrong format! Enter a correct email address! \n");
    getchar();
    scanf("%s", &aux);
  }
  strcpy(c.adresaEmail, aux);

  listaContacte[k] = c;
  k++;
}

int ShowAll() {
  char c[] = "";
  if (k == 0) {
    printf("%s", "There are no contacts yet! \n");
    return 0;
  } else {
    printf("%s", "Options: 0 to go back; 1 to add; 2 to edit; 3 to delete \n");
    for (int i = 0; i < k; i++)
      printf("%s %s %s %s\n", listaContacte[i].numeContact,
             listaContacte[i].prenumeContact, listaContacte[i].numarTelefon,
             listaContacte[i].adresaEmail);
  }
  scanf("%s", c);
  while (c[0] - '0' > 3) {
    printf("%s", "Input a correct option!\n");
    scanf("%s", c);
  }
  if (strcmp(c, "0") == 0)
    return 0;
  else if (strcmp(c, "1") == 0)
    Add();
  else if (strcmp(c, "2") == 0) {
    Update(-1);
  } else {
    Delete(-1);
  }
}

int Update(int index) {
  int i, aux, change;
  char c[10] = "";
  if (index == -1) {
    if (k == 0) {
      printf("%s", "There are no contacts yet! \n");
      return 0;
    } else {
      printf("%s", "Which is the contact you want to change? \n");
      for (i = 0; i < k; i++)
        printf("%d %s %s %s %s\n", i, listaContacte[i].numeContact,
               listaContacte[i].prenumeContact, listaContacte[i].numarTelefon,
               listaContacte[i].adresaEmail);
      scanf("%d", &aux);
      while (aux > k - 1 || aux == k == 1) {
        printf("%s", "Input a correct id!\n");
        scanf("%d", &aux);
      }
      printf("%s",
             "What would you like to change? (Name/Surname/Number/Email) \n");
      scanf("%s", &c);
      while (strcmp(c, "Name") && strcmp(c, "Surname") && strcmp(c, "Number") &&
             strcmp(c, "Email")) {
        printf("%s", "Input a correct option! \n");
        scanf("%s", &c);
      }
      char chAux[50] = "";
      if (strcmp(c, "Name") == 0) {
        printf("%s",
               "What would you like to be the new name for the contact? \n");
        scanf("%s", &chAux);
        while (regVerify(chAux, "Name") != 0) {
          printf("%s", "Wrong input! \n");
          scanf("%s", &chAux);
        }
        change = aux;
        strcpy(listaContacte[change].numeContact, chAux);
        printf("%s", "You are good to go! \n");
      } else if (strcmp(c, "Surname") == 0) {
        printf("%s",
               "What would you like to be the new surname for the contact? \n");
        scanf("%s", &chAux);
        while (regVerify(chAux, "Surname") != 0) {
          printf("%s", "Wrong input! \n");
          scanf("%s", &chAux);
        }
        change = aux;
        strcpy(listaContacte[change].prenumeContact, chAux);
        printf("%s", "You are good to go! \n");
      } else if (strcmp(c, "Number") == 0) {
        printf("%s",
               "What would you like to be the new number for the contact? \n");
        scanf("%s", &chAux);
        while (regVerify(chAux, "Number") != 0) {
          printf("%s", "Wrong input! \n");
          scanf("%s", &chAux);
        }
        change = aux;
        strcpy(listaContacte[change].numarTelefon, chAux);
        printf("%s", "You are good to go! \n");
      } else if (strcmp(c, "Email") == 0) {
        printf("%s",
               "What would you like to be the new email for the contact? \n");
        scanf("%s", &chAux);
        while (regVerify(chAux, "Email") != 0) {
          printf("%s", "Wrong input! \n");
          scanf("%s", &chAux);
        }
        change = aux;
        strcpy(listaContacte[change].adresaEmail, chAux);
        printf("%s", "You are good to go! \n");
      }
    }
  } else {
    char chAux[100] = "";
    printf("%s",
           "What would you like to change? (Name/Surname/Number/Email) \n");
    scanf("%s", &c);
    while (strcmp(c, "Name") && strcmp(c, "Surname") && strcmp(c, "Number") &&
           strcmp(c, "Email")) {
      printf("%s", "Input a correct option! \n");
      scanf("%s", &c);
    }
    if (strcmp(c, "Name") == 0) {
      printf("%s",
             "What would you like to be the new name for the contact? \n");
      scanf("%s", &chAux);
      while (regVerify(chAux, "Name") != 0) {
        printf("%s", "Wrong input! \n");
        scanf("%s", &chAux);
      }
      strcpy(listaContacte[index].numeContact, chAux);
      printf("%s", "You are good to go! \n");
    } else if (strcmp(c, "Surname") == 0) {
      printf("%s",
             "What would you like to be the new surname for the contact? \n");
      scanf("%s", &chAux);
      while (regVerify(chAux, "Surname") != 0) {
        printf("%s", "Wrong input! \n");
        scanf("%s", &chAux);
      }
      strcpy(listaContacte[index].prenumeContact, chAux);
      printf("%s", "You are good to go! \n");
    } else if (strcmp(c, "Number") == 0) {
      printf("%s",
             "What would you like to be the new number for the contact? \n");
      scanf("%s", &chAux);
      while (regVerify(chAux, "Number") != 0) {
        printf("%s", "Wrong input! \n");
        scanf("%s", &chAux);
      }
      strcpy(listaContacte[index].numarTelefon, chAux);
      printf("%s", "You are good to go! \n");
    } else if (strcmp(c, "Email") == 0) {
      printf("%s",
             "What would you like to be the new email for the contact? \n");
      scanf("%s", &chAux);
      while (regVerify(chAux, "Email") != 0) {
        printf("%s", "Wrong input! \n");
        scanf("%s", &chAux);
      }
      strcpy(listaContacte[index].adresaEmail, chAux);
      printf("%s", "You are good to go! \n");
    }
  }
}

int Delete(int index) {
  if (index == -1) {
    if (k == 0) {
      printf("%s", "There are no contacts yet! \n");
      return 0;
    } else {
      printf("%s", "Which is the contact you want to delete? (by Id)\n");
      for (int i = 0; i < k; i++)
        printf("%d %s %s %s %s\n", i, listaContacte[i].numeContact,
               listaContacte[i].prenumeContact, listaContacte[i].numarTelefon,
               listaContacte[i].adresaEmail);
      int delete;
      scanf("%d", &delete);
      while (delete > k) {
        printf("%s", "Enter a correct id! \n");
        scanf("%d", &delete);
      }
      while (k == 1 && delete != 0) {
        printf("%s", "Enter a correct id! \n");
        scanf("%d", &delete);
      }
      listaContacte[delete] = listaContacte[--k];
      printf("%s", "Deleted! \n");
    }
  } else {
    listaContacte[index] = listaContacte[--k];
    printf("%s", "Deleted! \n");
  }
}

int Search() {
  char search[100] = "";
  if (k == 0) {
    printf("%s", "There are no contacts yet! \n");
    return 0;
  } else {
    printf("%s", "Who are you searching for: (by Name/Phone number) \n");
    scanf("%s", &search);
    int count = 0, one;
    for (int i = 0; i < k; i++) {
      if (strstr(listaContacte[i].numeContact, search) != NULL) {
        one = i;
        count++;
        printf("%d %s %s %s %s\n", i, listaContacte[i].numeContact,
               listaContacte[i].prenumeContact, listaContacte[i].numarTelefon,
               listaContacte[i].adresaEmail);
      } else if (strstr(listaContacte[i].numarTelefon, search) != NULL) {
        one = i;
        count++;
        printf("%d %s %s %s %s\n", i, listaContacte[i].numeContact,
               listaContacte[i].prenumeContact, listaContacte[i].numarTelefon,
               listaContacte[i].adresaEmail);
      }
    }
    if (count > 1) {
      char c[100] = "";
      int aux;
      printf("%s", "Select a contact for more options! \n");
      scanf("%d", &aux);
      while (aux > k - 1) {
        printf("%s", "Input a correct id!\n");
        scanf("%d", &aux);
      }
      printf("%s",
             "Options: 0 to go back; 1 to edit; 2 to delete (0 to go back) \n");
      scanf("%s", &c);
      if (strcmp(c, "1") == 0) {
        Update(aux);
      }
      if (strcmp(c, "2") == 0) {
        Delete(aux);
      }
      if (strcmp(c, "0") == 0) {
        return 0;
      }
    }
    if (count == 1) {
      char c[100] = "";
      printf("%s", "Options: 0 to go back; 1 to edit; 2 to delete \n");
      scanf("%s", &c);
      if (strcmp(c, "1") == 0) {
        Update(one);
      }
      if (strcmp(c, "2") == 0) {
        Delete(one);
      }
      if (strcmp(c, "0") == 0) {
        return 0;
      }
    }
    if (count == 0) {
      printf("%s", "Contact not found!\n");
      return 0;
    }
  }
}

int main() {
  printf("%s", "Welcome to PhoneBook ! \n");
  Read();
  Menu();
  Write();
  return 0;
}