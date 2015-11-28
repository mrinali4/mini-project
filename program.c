#include<stdio.h>
#include<conio.h>
#include<string.h>

void main()
{
char label[10],opcode[10],operand[10],symbol[10],ch,byte_character_size,a[10],ad[10],name[10],op1[10],op2[10];
int st,diff,i=0,address,add,actual_len,finaddr,prevaddr,j=0,k=0,locctr=0X0,start=0X0,len=0,byte_operand_length=0,prevaddr1,lendif=0,counter=0,c=0,icounter=0;
FILE *fp1,*fp2,*fp3,*fp4,*text;
printf("Enter Input file name:");
scanf("%s",&name);
fp1=fopen(name,"r");
fp2=fopen("symtab.txt","w");
fp3=fopen("intermediate.txt","w");
fp4=fopen("quesoptab.txt","r");

fscanf(fp1,"%s%s%X",label,opcode,&locctr);

if(strcmp(opcode,"START")==0)
{
prevaddr=locctr;
fprintf(fp3,"\t%s\t%s\t%0X\n",label,opcode,locctr);
fscanf(fp1,"%s%s%s",label,opcode,operand);
}
else
locctr=0X0;

while(strcmp(opcode,"END")!=0)
{
fprintf(fp3,"%0X",locctr);

if(strcmp(label,"**")!=0)
{

fprintf(fp2,"%s\t%0X\n",label,locctr);
}
rewind(fp4);
fscanf(fp4,"%s %s",op1,op2);
k=1;
while(k<=6)
{
if(strcmp(opcode,op1)==0)
{
locctr=locctr+3;
break;
}
fscanf(fp4,"%s %s",op1,op2);
k++;
}

if(strcmp(opcode,"WORD")==0)
locctr=locctr+3;
else if(strcmp(opcode,"RESW")==0)
locctr=locctr+(3*(atoi(operand)));
else if(strcmp(opcode,"RESB")==0)
locctr=locctr+(atoi(operand));
else if(strcmp(opcode,"BYTE")==0)
{

byte_operand_length=strlen(operand);
if(operand[0]=='X')
{
    locctr=locctr+1;

}
else
locctr=locctr+byte_operand_length-3;
}

fprintf(fp3,"\t%s\t%s\t%s\n",label,opcode,operand);
fscanf(fp1,"%s%s%s",label,opcode,operand);
}

fprintf(fp3,"%0X\t%s\t%s\t%s\n",locctr,label,opcode,operand);

finaddr=locctr;
fclose(fp1);
fclose(fp2);
fclose(fp3);
fclose(fp4);

// DO NOT LOOK DOWN

printf("\n\nThe contents of Input Table:\n\n");
fp1=fopen(name,"r");
ch=fgetc(fp1);
while(ch!=EOF)
{
    printf("%c",ch);
    ch=fgetc(fp1);
}

len=finaddr-prevaddr;

printf("\nThe length of the prog.:%0X \n\n",len);
printf("\n\nThe contents of SYMTAB :\n\n");
    fp2=fopen("symtab.txt","r");
    ch=fgetc(fp2);
    while(ch!=EOF)
    {

        printf("%c",ch);
        ch=fgetc(fp2);
    }
    fclose(fp2);
    fclose(fp1);





//PASS 2
fp2=fopen("symtab.txt","r");
fp3=fopen("intermediate.txt","r");
fp4=fopen("quesoptab.txt","r");
text=fopen("text.txt","w");
fscanf(fp3,"%s%s%s",label,opcode,operand);

if(strcmp(opcode,"START")==0)
{
fprintf(text,"\n\n\nH^%s^%s^%0X\n",label,operand,len);

fscanf(fp3,"%X%s%s%s",&address,label,opcode,operand);
fprintf(text,"T^%0X^",len);

}
while(strcmp(opcode,"END")!=0)
{

    if(strcmp(opcode,"BYTE")==0)
    {

        len=strlen(operand);
        actual_len=len-3;

        if(operand[0]=='C')
        {
        for(i=2;i<(actual_len+2);i++)
        {
            itoa(operand[i],ad,16);
            fprintf(text,"%s",ad);
            }
        }
        else
        {
            for(i=2;i<(actual_len+2);i++)
            {


            fprintf(text,"%c",operand[i]);

            }
        }
        fprintf(text,"^");

        }

    else if(strcmp(opcode,"WORD")==0)
    {

        len=strlen(operand);
        itoa(atoi(operand),a,16);
        len=strlen(a);
        lendif=6-len;

        for(j=0;j<lendif;j++)
        {

            fprintf(text,"0");
        }

        fprintf(text,"%s^",a);
    }
   else if(strcmp(opcode,"RESB")==0||(strcmp(opcode,"RESW")==0))
      {

      }
    else
    {
        rewind(fp4);
        fscanf(fp4,"%s %s",op1,op2);

        while(strcmp(opcode,op1)!=0)
               fscanf(fp4,"%s %s",op1,op2);
       if(strcmp(opcode,"RSUB")==0)
            {

              fprintf(text,"%s0000^",op2);
            }
        else
        {

            rewind(fp2);
            fscanf(fp2,"%s%X",symbol,&add);
            while(strcmp(operand,symbol)!=0)
                fscanf(fp2,"%s %X",symbol,&add);

            fprintf(text,"%s%0X^",op2,add);

        }
    }
         fscanf(fp3,"%X\t%s\t%s\t%s\n",&address,label,opcode,operand);

        }
    fprintf(text,"\nE^%0X\n",prevaddr);
        fclose(fp2);
        fclose(fp3);

        fclose(text);




        printf("\n\nThe contents of Intermediate file:\n\n\t");
            fp3=fopen("intermediate.txt","r");
            ch=fgetc(fp3);
            while(ch!=EOF)
            {
                printf("%c",ch);
                ch=fgetc(fp3);

            }



text=fopen("text.txt","r");

  ch=fgetc(text);
    while(ch!=EOF)
    {

        printf("%c",ch);
        ch=fgetc(text);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
fclose(text);
}
