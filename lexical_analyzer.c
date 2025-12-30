#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Simple lexical analyzer for a C-like language
   Features:
   - Identifies keywords, identifiers, numbers
   - Recognizes operators, separators, comments
   - Builds a small symbol table for identifiers
   - Basic error handling for unknown characters and unterminated strings/chars
*/

/* 32 C keywords */
const char *keywords[] = {
 "auto","break","case","char","const","continue","default","do","double",
 "else","enum","extern","float","for","goto","if","int","long","register",
 "return","short","signed","sizeof","static","struct","switch","typedef",
 "union","unsigned","void","volatile","while",NULL};

typedef struct {
    char name[64];
    int first_line;
    int count;
} Symbol;

Symbol symtab[500];
int symcount=0;

int is_keyword(const char *s) {
    for (const char **k=keywords; *k; k++)
        if (strcmp(*k,s)==0) return 1;
    return 0;
}

void add_symbol(const char *name,int line){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            symtab[i].count++;
            return;
        }
    }
    strncpy(symtab[symcount].name,name,63);
    symtab[symcount].first_line=line;
    symtab[symcount].count=1;
    symcount++;
}

FILE *in;
int line=1,col=0;

int nextc(){
    int c=fgetc(in);
    if(c=='\n'){line++;col=0;}
    else col++;
    return c;
}
int peekc(){
    int c=fgetc(in);
    if(c!=EOF)ungetc(c,in);
    return c;
}

void tokenize(){
    int c=nextc();
    while(c!=EOF){
        /* skip spaces */
        while(isspace(c)) c=nextc();
        if(c==EOF)break;

        /* identifiers or keywords */
        if(isalpha(c)||c=='_'){
            char buf[64];int i=0;
            while((isalnum(c)||c=='_')&&i<63){buf[i++]=c;c=nextc();}
            buf[i]='\0'; if(c!=EOF)ungetc(c,in),col--;
            if(is_keyword(buf)) printf("KEYWORD  %-15s (line %d)\n",buf,line);
            else {printf("IDENT    %-15s (line %d)\n",buf,line);add_symbol(buf,line);}
            c=nextc();continue;
        }

        /* numbers */
        if(isdigit(c)){
            char buf[64];int i=0;
            while((isdigit(c)||c=='.')&&i<63){buf[i++]=c;c=nextc();}
            buf[i]='\0';if(c!=EOF)ungetc(c,in),col--;
            printf("NUMBER   %-15s (line %d)\n",buf,line);
            c=nextc();continue;
        }

        /* string literal */
        if(c=='"'){
            char buf[128];int i=0;buf[i++]='"';c=nextc();int closed=0;
            while(c!=EOF && i<127){buf[i++]=c;if(c=='"'){closed=1;break;}if(c=='\\'){c=nextc();buf[i++]=c;}c=nextc();}
            buf[i]='\0';
            if(!closed)printf("ERROR    Unterminated string at line %d\n",line);
            else printf("STRING   %-15s (line %d)\n",buf,line);
            c=nextc();continue;
        }

        /* char literal */
        if(c=='\''){
            char buf[64];int i=0;buf[i++]='\'';c=nextc();int closed=0;
            while(c!=EOF&&i<63){buf[i++]=c;if(c=='\''){closed=1;break;}if(c=='\\'){c=nextc();buf[i++]=c;}c=nextc();}
            buf[i]='\0';
            if(!closed)printf("ERROR    Unterminated char at line %d\n",line);
            else printf("CHAR     %-15s (line %d)\n",buf,line);
            c=nextc();continue;
        }

        /* comments or divide */
        if(c=='/'){
            int p=peekc();
            if(p=='/'){ /* single line */
                char buf[128];int i=0;buf[i++]='/';buf[i++]='/';nextc();
                c=nextc();while(c!=EOF&&c!='\n'&&i<127){buf[i++]=c;c=nextc();}
                buf[i]='\0';printf("COMMENT  (single-line) at line %d\n",line);continue;
            }
            if(p=='*'){ /* multi line */
                nextc();c=nextc();int closed=0;
                while(c!=EOF){if(c=='*'&&peekc()=='/'){nextc();closed=1;break;}c=nextc();}
                if(!closed)printf("ERROR    Unterminated comment at line %d\n",line);
                else printf("COMMENT  (multi-line) ending at line %d\n",line);
                c=nextc();continue;
            }
            printf("OPERATOR / at line %d\n",line);c=nextc();continue;
        }

        /* operators/separators */
        if(strchr("+-*%=<>!&|^~?:",c)){
            printf("OPERATOR %c at line %d\n",c,line);c=nextc();continue;
        }
        if(strchr(";,(){}[].",c)){
            printf("SEPARATOR %c at line %d\n",c,line);c=nextc();continue;
        }

        /* unknown */
        printf("ERROR    Unknown char '%c' at line %d\n",c,line);
        c=nextc();
    }
}

int main(int argc,char**argv){
    if(argc<2){printf("Usage: %s <file>\n",argv[0]);return 1;}
    in=fopen(argv[1],"r");if(!in){perror("fopen");return 1;}
    tokenize();
    printf("\nSymbol Table:\n");
    for(int i=0;i<symcount;i++)
        printf("%-15s first at line %d, count=%d\n",symtab[i].name,symtab[i].first_line,symtab[i].count);
    fclose(in);
    return 0;
}
