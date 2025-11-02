#include <stdio.h>
#include <ctype.h>
#include <string.h>
char keywords[][20] = {
    "const","extern","auto","register","static","signed","union","enum","void","typedef",
    "int","float","if","else","while","return","goto","do","switch","case","default","sizeof"
};
char operators[] = {'/','+','*','-','%','=','<','>','&','.','!','^','|','"'};  
char symbols[]   = {'(',')','{','}',';',','};
int isKeyword(char *word) 
{
    int j;
    for (j=0;j<23;j++) 
    {
        if (!strcmp(word,keywords[j])) 
        {
            return 1;
        }
    }
    return 0;
}
int isOperator(char ch) 
{
    int j;
    for (j=0;j<15;j++) 
    {
        if (ch==operators[j]) 
        {
            return 1;
        }
    }
    return 0;
}
int isSymbol(char ch) 
{
    return strchr(symbols,ch)!=NULL;
}
void printSymbol(char ch) 
{
    switch(ch) 
    {
        case '(': printf("( -> open_brace\n"); 
        break;
        case ')': printf(") -> close_brace\n"); 
        break;
        case '{': printf("{ -> open_curly\n"); 
        break;
        case '}': printf("} -> close_curly\n"); 
        break;
        case ';': printf("; -> end of the line\n"); 
        break;
        case ',': printf(", -> comma\n"); 
        break;
    }
}
void processWord(char *word) 
{
    if (isKeyword(word)) 
    {
        printf("%s -> reserved keyword\n",word);
    }
    else if (isdigit(word[0]))
    {
        int valid=1;
        int i;
        for (i=0;word[i];i++) 
        {
            if (!isdigit(word[i])) 
            {
                valid=0;
                break;
            }
        }
        if (valid)
            printf("%s -> numeric constant\n",word);
        else
            printf("%s -> ERROR (invalid identifier)\n",word);
    }
    else if (isalpha(word[0])||word[0]=='_') 
    {
        printf("%s -> identifier\n",word);
    }
    else 
    {
        printf("%s -> ERROR (invalid numeric constant)\n",word);
    }
}
int main() 
{
    FILE *fp=fopen("input.c","r");
    if (!fp) 
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }
    char ch,word[200];
    int i=0;
    while ((ch=fgetc(fp))!=EOF) 
    {
        if (ch=='#')
        {
            while ((ch=fgetc(fp))!=EOF && ch!='\n');
            continue; 
        }
        else if (isalnum(ch)||ch=='_') 
        {
            word[i++]=ch;
        }
        else 
        {
            if (i) 
            {
                word[i]='\0';
                processWord(word);
                i=0;
            }
            if (isOperator(ch)) 
            {
                printf("%c -> operator\n",ch);
            }
            else if (isSymbol(ch)) 
            {
                printSymbol(ch);
            }
            else if (!isspace(ch)) 
            {
                printf("%c -> ERROR\n",ch);
            }
        }
    }
    if (i) 
    {
        word[i]='\0';
        processWord(word);
    }
    fclose(fp);
    return 0;
}
