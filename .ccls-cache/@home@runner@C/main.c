#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include<stdbool.h>
#include <stdlib.h>

regex_t regex;

void Update();
void Delete();
void Add();
void Search();
void ShowAll();
void Menu();
int regVerify();

struct contact{
    char *numarTelefon[100];
    char *prenumeContact[25];
    char *numeContact[25];
    char *adresaEmail[50];
};

struct contact listaContacte[50];
int k = 0;
void Menu(){
    int x = 1;
    while(x) {
        printf("%s", "1 - Add contact \n2 - Show all contacts \n3 - Update contact \n4 - Delete contact \n5 - Search by name/surname/phone number \n0 - Exit \n");
        int y;
        scanf("%d", &y);

        switch (y) {
            case 0:
                x = 0;
                break;
            case 1:
                Add();
                break;
            case 2:
                ShowAll();
                break;
            case 3:
                Update();
                break;
            case 4:
                Delete();
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
void Read(){
    FILE *fp = fopen("data.txt", "r");
    char row[255];
    char *token;
    int count = 0;
    struct contact cnt;

    while (fgets(row, sizeof(row), fp) != NULL && count<=k)
    {
        if (count == 0)
        {
            char c = row[0];
            k = c - '0';
        }
        else{
            token = strtok(row, " ");
            strcpy(cnt.numeContact, token);

            token = strtok(NULL, " ");
            strcpy(cnt.prenumeContact, token);

            token = strtok(NULL, " ");
            strcpy(cnt.numarTelefon, token);

            token = strtok(NULL, " \n");
            strcpy(cnt.adresaEmail, token);

            listaContacte[count-1] = cnt;
        }
        count++;
    }
    fclose(fp);
}
void Write(){
    FILE *fp = fopen("data.txt","w+");
    fprintf(fp, "%d", k);
    fputs("\n", fp);
        for(int i=0; i<k; i++) {
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
int regVerify(char check[100], char type[10])
{
    if (strcmp(type, "Name") == 0)
    {
        int return_value = -1;
        return_value = regcomp(&regex, "^[a-zA-Z]+$", REG_EXTENDED);
        return_value += regexec(&regex, check, 0, NULL, 0);
        return return_value;
    }
    else if (strcmp(type, "Surname") == 0)
    {
        int return_value = -1;
        return_value = regcomp(&regex, "^[a-zA-Z]+$", REG_EXTENDED);
        return_value += regexec(&regex, check, 0, NULL, 0);
        return return_value;
    }
    if (strcmp(type, "Number") == 0)
    {
        int return_value = -1;
        return_value = regcomp(&regex, "^07[0123456789]{8}$", REG_EXTENDED);
        return_value += regexec(&regex, check, 0, NULL, 0);
        return return_value;
    }
    else if (strcmp(type, "Email") == 0)
    {
        int return_value = -1;
        return_value = regcomp(&regex, "^([a-zA-Z0-9_]+@(gmail)?(yahoo)?([.]com)?([.]ro)?)$", REG_EXTENDED);
        return_value += regexec(&regex, check, 0, NULL, 0);
        return return_value;
    }
}

void Add()
{
    struct contact c;
    char aux[100];

    printf("%s", "Name: \n");
    getchar();
    scanf("%s", &aux);

    while(regVerify(aux, "Name") != 0)
    {
        printf("%s", "Wrong format! Input only letters! \n");
        getchar();
        scanf("%s", &aux);
    }
    strcpy(c.numeContact, aux);

    printf("%s", "Surname: \n");
    getchar();
    scanf("%s", &aux);

    while(regVerify(aux, "Surname") != 0)
    {
        printf("%s", "Wrong format! Input only letters! \n");
        getchar();
        scanf("%s", &aux);
    }
    strcpy(c.prenumeContact, aux);

    printf("%s", "Phone number: (RO format)\n");
    getchar();
    scanf("%s", &aux);

    while(regVerify(aux, "Number") != 0)
    {
        printf("%s", "Wrong format! Input a Romanian phone number! \n");
        getchar();
        scanf("%s", &aux);
    }
    strcpy(c.numarTelefon, aux);

    printf("%s", "Email: \n");
    getchar();
    scanf("%s", &aux);

    while(regVerify(aux, "Email") != 0)
    {
        printf("%s", "Wrong format! Enter a correct email address! \n");
        getchar();
        scanf("%s", &aux);
    }
    strcpy(c.adresaEmail, aux);

    listaContacte[k] = c;
    k++;
}

void ShowAll()
{
    char c[] = "";
    if (k == 0)
    {
        printf("%s", "There are no contacts yet! \n");
        Menu();
    }
    else{
        printf("%s", "These are all the contacts: (0 to go back)\n");
        for(int i=0; i<k; i++)
            printf("%s %s %s %s\n", listaContacte[i].numeContact,listaContacte[i].prenumeContact, listaContacte[i].numarTelefon, listaContacte[i].adresaEmail);
        scanf("%s", &c);
        if(strcmp(c, "0")==0)
            Menu();
    }
}

void Update()
{
    int i, aux, change;
    char c[10] = "";
    if (k == 0)
    {
        printf("%s", "There are no contacts yet! \n");
        Menu();
    }
    else{
        printf("%s", "Which is the contact you want to change? \n");
        for(i=0; i<k; i++)
            printf("%d %s %s %s %s\n", i, listaContacte[i].numeContact, listaContacte[i].prenumeContact, listaContacte[i].numarTelefon, listaContacte[i].adresaEmail);
        scanf("%d", &aux);
        if (aux <= k)
        {
            printf("%s", "What would you like to change? (Name/Surname/Number/Email) \n");
            scanf("%s", &c);
            change = aux;
            if(c != NULL || c!= "")
            {
                char chAux[] = "";
                if(strcmp(c, "Name")==0)
                {
                    printf("%s","What would you like to be the new name for the contact? \n");
                    scanf("%s", &listaContacte[change].numeContact);
                    printf("%s", "You are good to go!\n");
                }
                else if(strcmp(c, "Surname")==0)
                {
                    printf("%s","What would you like to be the new surname for the contact? \n");
                    scanf("%s", &listaContacte[change].prenumeContact);
                    printf("%s", "You are good to go!\n");
                }
                else if(strcmp(c, "Number")==0)
                {
                    printf("%s","What would you like to be the new number for the contact? \n");
                    scanf("%s", &chAux);

                    if(regVerify(chAux, "Number") == 0)
                    {
                        strcpy(listaContacte[change].numarTelefon, chAux);
                        printf("%s", "You are good to go! \n");
                    }
                    else
                    {
                        printf("%s", "Wrong input! \n");
                    }
                }
                else if(strcmp(c, "Email")==0)
                {
                    printf("%s","What would you like to be the new email for the contact? \n");
                    scanf("%s", &chAux);

                    if(regVerify(chAux, "Email") == 0)
                    {
                        strcpy(listaContacte[change].adresaEmail, chAux);
                        printf("%s", "You are good to go! \n");
                    }
                    else
                    {
                        printf("%s", "Wrong input! \n");
                    }
                }
                else
                {
                    printf("%s", "Choose a correct option! \n");
                }
            }
        }
        else
        {
            printf("%s", "Choose a correct option! \n");
        }
        Menu();
    }
}

void Delete()
{
    int delete;
    if (k == 0)
    {
        printf("%s", "There are no contacts yet! \n");
        Menu();
    }
    else{
        printf("%s", "Which is the contact you want to delete? (by Id)\n");
        for(int i=0; i<k; i++)
            printf("%d %s %s %s %s\n", i, listaContacte[i].numeContact,listaContacte[i].prenumeContact, listaContacte[i].numarTelefon, listaContacte[i].adresaEmail);
        scanf("%d", &delete);
        while (delete > k)
            printf("%s", "Enter a correct id! \n");
        listaContacte[delete] = listaContacte[--k];
        printf("%s", "Deleted! \n");
        Menu();
    }
}

void Search()
{
    char search[] = "";
    if (k == 0)
    {
        printf("%s", "There are no contacts yet! \n");
        Menu();
    }
    else{
        printf("%s", "Who are you searching for: (by Name/Surname/Phone number) \n");
        scanf("%s", &search);
        int i,flag = 0;
        for (int i = 0 ; i<k && flag == 0; i++)
        {
            if(strstr(search, listaContacte[i].numeContact) != NULL)
            {
                char c[] = "";
                printf("%s", "Found it!\n");
                flag = 1;
                printf("%s %s %s %s\n", listaContacte[i].numeContact,listaContacte[i].prenumeContact, listaContacte[i].numarTelefon, listaContacte[i].adresaEmail);
                printf("%s", "Do you want to change/delete something?  \n");
                scanf("%s", &c);
                if(strcmp(c, "change") == 0)
                {
                    Update();
                }
                if(strcmp(c, "delete") == 0)
                {
                    Delete();
                }
            }

            else if(strstr(search, listaContacte[i].numarTelefon) != NULL)
            {
                char c[] = "";
                printf("%s \n", "Found it! \n");
                flag = 1;
                printf("%s %s %s %s\n", listaContacte[i].numeContact,listaContacte[i].prenumeContact, listaContacte[i].numarTelefon, listaContacte[i].adresaEmail);
                printf("%s", "Do you want to add/change/delete something?\n");
                scanf("%s", &c);
                if(strcmp(c, "add") == 0)
                {
                    Add();
                }
                if(strcmp(c, "change") == 0)
                {
                    Update();
                }
                if(strcmp(c, "delete") == 0)
                {
                    Delete();
                }
            }

            else if(strstr(search, listaContacte[i].prenumeContact) != NULL)
            {
                char c[] = "";
                printf("%s \n", "Found it! \n");
                flag = 1;
                printf("%s %s %s %s\n", listaContacte[i].numeContact, listaContacte[i].prenumeContact, listaContacte[i].numarTelefon, listaContacte[i].adresaEmail);
                printf("%s", "Do you want to add/change/delete something?\n");
                scanf("%s", &c);
                if(strcmp(c, "add") == 0)
                {
                    Add();
                }
                if(strcmp(c, "change") == 0)
                {
                    Update();
                }
                if(strcmp(c, "delete") == 0)
                {
                    Delete();
                }
            }
        }
        if (flag == 0)
        {
            printf("%s", "Contact not found!");
            Menu();
        }
        Menu();
    }
}

int main() {
    printf("%s", "Welcome to PhoneBook ! \n");
    Read();
    Menu();
    Write();
    return 0;
}