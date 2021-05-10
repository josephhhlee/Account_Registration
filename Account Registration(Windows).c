#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<Windows.h>

#define MAX 50

bool reg, login, input = false;
char reg_email[MAX], reg_pw[MAX], dis_pw[MAX], reg_name[MAX], reg_address[MAX], reg_postal[MAX], reg_number[MAX], line[MAX], *count;
int len, i;
FILE *fp;
char filename[] = "Account Details.csv";

void dotdotdot(char *title,int time)
{
    float loop = 0;
    int i;
    fflush(stdout);
    fflush(stdin);
    system("cls");
    printf("%s", title);
    for(i = 1; i < 4; i++)
    {
        fflush(stdout);
        fflush(stdin);
        usleep(500000);
        printf(".");
        fflush(stdout);
        fflush(stdin);
        loop += 0.5;
        if(i == 3 )
        {
            usleep(500000);
            loop += 0.5;
            system("cls");
            printf("%s", title);
            fflush(stdout);
            fflush(stdin);
            i = 0;
        }
        if(loop >= time)
        {
            system("cls");
            break;
        }
    }
}

bool main_page(void)
{
    fflush(stdout);
    fflush(stdin);
    char choose;
    do{
        printf("\n\n\t[SIGNUP(1)]\n");
        if(fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("Input error.\n");
            exit(1);
        }
        len = strlen(line);
        if(len == 2)
        {
            choose = line[0];
            line[0] = '\0';
            if(choose == 'x' || choose == '1' || choose == '2')
            {
                input = true;
            }
            else
            {
                dotdotdot("Invalid Input, please try again", 3);
                continue;
            }
        }
        else if(len != 2)
        {
            dotdotdot("Invalid Input, please try again", 3);
            continue;
        }
    }while(!input);
    input = false;
    if(choose == '1')
    {
        login = false;
        reg = true;
        dotdotdot("Loading Registration Page", 3);
    }
    else if(choose == '2')
    {
        login = true;
        reg = false;
        dotdotdot("Loading Login Page", 3);
    }
    else
    {
        dotdotdot("System is shutting down", 5);
        exit(1);
    }
    return reg;
}

void create_csv(char *file) //function for creating csv
{
    time_t rawtime; 
    struct tm* timeinfo;
    char buffer[80]; 
  
    time(&rawtime); 
    timeinfo = localtime(&rawtime); 
    strftime(buffer, 80, "%I:%M%p", timeinfo);
    fp = fopen(file,"w");
    fprintf(fp,"Time: %s,\t\n" ,buffer);
    fprintf(fp,"\nName,Email,Password,Address,Postal Code,Phone No.");
    fclose(fp);
}

void title(char* name) //function to capitalize 1st letter of every word
{
    int i;
    for(i = 0; name[i] != '\0'; i++)
    {
        if(i == 0)
        {
            if(name[i] >= 'a' && name[i] <= 'z')
            {
                name[i] = name[i] - 32;
                continue;
            }
        }
        else if(name[i] == ' ')
        {
            ++i;
            if(name[i] >= 'a' && name[i] <= 'z')
            {
                name[i] = name[i] - 32;
                continue;                    
            }
        }
        else
        {
            if(name[i] >= 'A' && name[i] <= 'Z')
            {
                name[i] = name[i] - 32;
            }
        }
    }
}

void ask_name(void)
{
    fflush(stdin);
    fflush(stdout);
    printf("Name(as in NRIC)\n ");
    do{
        if(fgets(reg_name, sizeof(reg_name), stdin)==NULL)
        {
            printf("Input error.\n");
            exit(1);
        }
        title(reg_name);
        reg_name[strcspn(reg_name, "\n")] = 0; //remove newline char from fgets
        for(count = reg_name; *count; *count++) //check if there is space between full name
        {
            if(*count == ' ')
            {
                input = true;
                system("cls");
                printf("Name(as in NRIC)\n %s\n",reg_name);
            }
        }
        if(!input)
        {
            system("cls");
            printf("Invalid NRIC Name for \'%s\', please try again\n\nName(as in NRIC)\n", reg_name);
            input = false;
        }
    }while(!input);
    input = false;
}

void ask_email(void)
{
    fflush(stdin);
    fflush(stdout);
    printf("\nEmail\n ");
    do{
        int x = 0;
        if(fgets(reg_email, sizeof(reg_email), stdin) == NULL)
        {
            printf("Input error.\n");
            exit(1);            
        }
        reg_email[strcspn(reg_email, "\n")] = 0;
        len = strlen(reg_email);
        for(count = reg_email; *count; *count++)
        {
            if(*count != ' ')
            {
                for(i = 0; i <= len; i++) //check if input email has '@' follow by '.'
                {
                    x += 1;
                    if(reg_email[i] == '@')
                    {
                        for(i = x; i <= len; i++)
                        {
                            if(reg_email[i] == '.')
                            {
                                system("cls");
                                printf("Name(as in NRIC)\n %s\n\nEmail\n %s\n", reg_name, reg_email);
                                input = true;
                                break;
                            }
                        }
                    }
                    if(input)
                    {
                        break;
                    }
                }
            }
            if(input)
            {
                break;
            }
        }
        if(!input)
        {
            system("cls");
            printf("Invalid Email for \'%s\', please try again\n\nEmail\n " ,reg_email);
        }
    }while(!input);
    input = false;
}

void ask_pw(void)
{
    fflush(stdin);
    fflush(stdout);
    char *c, confirm_pw[MAX];
    printf("\nPassword\n");
    pw_check:
    c = getpass(" Hidden Input (Enter once  done)");
    for(i = 0; i <= strlen(c); i++)
    {
        reg_pw[i] = c[i];
    } 
    fflush(stdout);
    len = strlen(reg_pw);
    if(len > 3)
    {
        for(i = 0; reg_pw[i] != '\0'; i++)
        {
            if(reg_pw[i] != ' ')
            {
                for(i = 0; i <= len; i++)
                {
                    if(isdigit(reg_pw[i]))
                    {
                        for(i = 0; i <= len; i++)
                        {
                            if(reg_pw[i] >= 'a' && reg_pw[i] <= 'z')
                            {
                                for(i = 0; i <= len; i++)
                                {
                                    if(reg_pw[i] >= 'A' && reg_pw[i] <= 'Z')
                                    {
                                        input = true;
                                        break;
                                    }
                                }
                            }
                            if(input)
                            {
                                break;
                            }
                        }
                    }
                    if(input)
                    {
                        break;
                    }
                }
            }
            if(input)
            {
                break;
            }
        }
    }
    dis_pw[0] = '\0';
    if(!input)
    {
        system("cls");
        printf("Invalid password, please try again\n- Password has to be more than 3 characters\n- Password has to contain at least one Number\n- Password has to contain at least one Uppercase & Lowercase Aplhabat\n\nPassword\n ");
        goto pw_check;
    }
    if(input)
    {
        dis_pw[0] = '\0';
        for(i = 0; i < strlen(reg_pw); i++)
        {
            dis_pw[i] = '*';
        }
        system("cls");
        printf("Name(as in NRIC)\n %s\n\nEmail\n %s\n\nPassword\n %s\n\nRe-confirm your Password\n", reg_name, reg_email, dis_pw);
        c = getpass(" Hidden Input (Enter once done)");
        for(i = 0; i <= strlen(c); i++)
        {
            confirm_pw[i] = c[i];
        }
        fflush (stdout);
        fflush(stdin);
        if(strcmp(confirm_pw, reg_pw) != 0)
        {
            system("cls");
            printf("Name(as in NRIC)\n %s\n\nEmail\n %s\n\n*Password does not match, please try again*\nPassword\n ", reg_name, reg_email);
            c[0] = '\0';
            dis_pw[0] = '\0';
            reg_pw[0] = '\0';
            input = false;
            goto pw_check;
        }
        system("cls");
        printf("Name(as in NRIC)\n %s\n\nEmail\n %s\n\nPassword\n %s\n", reg_name, reg_email, dis_pw);
        input = false;
    }
}

void ask_address(void)
{
    fflush(stdin);
    fflush(stdout);
    printf("\nAddress\n ");
    do{
        if(fgets(reg_address, sizeof(reg_address), stdin)==NULL)
        {
            printf("Input error.\n");
            exit(1);
        }
        reg_address[strcspn(reg_address, "\n")] = 0;
        len = strlen(reg_address);
        for(i = 0; i <= len; i ++)
        {
            reg_address[i] = toupper(reg_address[i]);
        }
        if(len > 7)
        {
            for(count = reg_address; *count; *count++)
            {
                if(*count == ' ')
                {
                    input = true;
                    break;
                }
            }
            if(input)
            {
                input = false;
                for(count = reg_address; *count; *count++)
                {
                    if(isdigit(*count))
                    {
                        input = true;
                        break;
                    }
                }
            }
            if(input)
            {
                system("cls");
                printf("Name(as in NRIC)\n %s\n\nEmail\n %s\n\nPassword\n %s\n\nAddress\n %s\n", reg_name, reg_email, dis_pw, reg_address);
            }
        }
        if(!input)
        {
            system("cls");
            printf("Invalid Address for \'%s\', please try again\n\nAddress\n ", reg_address);
        }
    }while(!input);
    input = false;
}

void ask_postal(void)
{   
    fflush(stdin);
    fflush(stdout);
    printf("\nPostal Code\n S");
    scanf("%s",reg_postal);
    postal_check:
    if(strlen(reg_postal) != 6)
    {
        system("cls");
        printf("Invalid Postal Code for \'%s\', please try again\n\nPostal Code\n S", reg_postal);
        scanf("%s", reg_postal);
        goto postal_check;
    }
    for(count = reg_postal; *count; *count++)
    {
        if(!isdigit(*count))
        {
            system("cls");
            printf("Invalid Postal Code for \'%s\', please try again\n\nPostal Code\n ", reg_postal);
            scanf("%s", reg_postal);
            goto postal_check;
        }
    }
    system("cls");
    printf("Name(as in NRIC)\n %s\n\nEmail\n %s\n\nPassword\n %s\n\nAddress\n %s\n\nPostal Code\n S%s\n", reg_name, reg_email, dis_pw, reg_address, reg_postal);
}

void ask_number(void)
{
    fflush(stdin);
    fflush(stdout);
    printf("\nPhone Number\n +65 ");
    pw_check:
    do{
        if(fgets(reg_number, sizeof(reg_number), stdin) == NULL)
        {
            printf("Invalid error\n");
            exit(1);
        }
        reg_number[strcspn(reg_number,"\n")] = 0;
        len = strlen(reg_number);
        if(len != 8)
        {
            system("cls");
            printf("Invalid Number for \'%s\', please try again\n\nPhone Number\n +65 ", reg_number);
            goto pw_check;
        }
        else if(len == 8)
        {
            for(i = 0; reg_number[i] != '\0'; i++)
            {
                if(!isdigit(reg_number[i]))
                {
                    system("cls");
                    printf("Invalid Number for \'%s\', please try again\n\nPhone Number\n +65 ", reg_number);
                    goto pw_check;
                }
            }
            input = true;
        }
    }while(!input);
    input = false;
}

bool reg_confirmation(void) //function after filling registration
{
    fflush(stdin);
    fflush(stdout);
    char confirmation;
    system("cls");
    //Display input Email & PW for Confirmation
    printf("\nConfirm Registration?\n\n\nName: %s\n\nEmail: %s\tPassword: %s\n\nAddress: %s\n\t SINGAPORE %s\n\nPhone Number: +65 %s\n\n\n(Y/N)\t\t X to Exit Registration\n", reg_name, reg_email, dis_pw, reg_address, reg_postal, reg_number);
    //do-while function for reading a single character input
    do {
        if(fgets(line, sizeof(line), stdin)==NULL)
        {
            printf("Input error.\n");
            exit(1);
        }
        len = strlen(line);
        if(len == 2)
        {
            confirmation = toupper(line[0]);
            line[0] = '\0';
            if(confirmation != 'Y' || confirmation != 'X' || confirmation != 'N')
            {
                system("cls");
                printf("\nConfirm Registration?\n\n\nName: %s\n\nEmail: %s\tPassword: %s\n\nAddress: %s\n\t SINGAPORE %s\n\nPhone Number: +65 %s\n\n\n! Please enter a valid input\n(Y/N)\t\t X to Exit Registration\n", reg_name, reg_email, dis_pw, reg_address, reg_postal, reg_number);
            }
        }
        else
        {
            system("cls");
            printf("\nConfirm Registration?\n\n\nName: %s\n\nEmail: %s\tPassword: %s\n\nAddress: %s\n\t SINGAPORE %s\n\nPhone Number: +65 %s\n\n\n! Please enter a valid input\n(Y/N)\t\t X to Exit Registration\n", reg_name, reg_email, dis_pw, reg_address, reg_postal, reg_number);
        }
    } while(confirmation != 'Y' && confirmation != 'N' && confirmation != 'X');
    if(confirmation == 'Y')
    {
        dotdotdot("Processing Registration", 5);
        printf("Registration is complete!\n");
        fp = fopen(filename,"a");
        fprintf(fp,"\n%s,%s,%s,%s,S%s,+65 %s", reg_name, reg_email, reg_pw, reg_address, reg_postal, reg_number);
        fclose(fp);
        reg = false;
    }
    else if(confirmation == 'N')
    {
        dotdotdot("Refreshing Registration Page", 5);
        reg = true;
    }
    else if(confirmation == 'X')
    {
        dotdotdot("Exiting Registration Page", 5);
        reg = false;
    }
    return reg;
}

void registration(void)
{
    reg = true;
    int i;
    while(reg)
    {
        ask_name();
        ask_email();
        ask_pw();
        ask_address();
        ask_postal();
        ask_number();
        reg_confirmation();
    }
}

int main(void)
{
    mainpage:
    system("cls");
    create_csv(filename);
    main_page();
    if(reg)
    {
        system("cls");
        registration();
    }
    else if(login)
    {
        system("cls");
        //signin();
    }
    goto mainpage;
    return 0;
}