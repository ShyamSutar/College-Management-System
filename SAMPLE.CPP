#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<string.h>

struct student{
char na[30];
char cl[10];
int rl;
char date[11];
}s;

long si = sizeof(s);

void input();
void display();
void search();
void searchByRoll();
void searchByName();
void modify();
void del();
void sort();
void sortByRoll();
void sortByName();

FILE *fp;

void main(){
int ch;
while(1){
clrscr();
printf("<== College Managment ==>\n");
printf("1.Take Admission\n");
printf("2.Student Info\n");
printf("3.Search\n");
printf("4.Modify\n");
printf("5.Delete\n");
printf("6.Sort\n");
printf("0.Exit\n\n");
printf("Enter Your choice: ");
scanf("%d",&ch);
switch(ch){
case 0:
exit(0);

case 1:
input();
break;

case 2:
display();
break;

case 3:
search();
break;

case 4:
modify();
break;

case 5:
del();
break;

case 6:
sort();
break;

default:
printf("Invalid Choice");
}
getch();
}
}

void input(){
char myDate[11];

struct date d;
getdate(&d);
sprintf(myDate, "%02d/%02d/%d", d.da_day, d.da_mon, d.da_year);
strcpy(s.date, myDate);

fp = fopen("st.txt","ab");
printf("Enter Student Name: ");
fflush(stdin);
gets(s.na);
printf("Enter Class: ");
scanf("%s",s.cl);
printf("Enter Roll: ");
scanf("%d",&s.rl);
fwrite(&s, sizeof(s),1,fp);
printf("Record Saved Successfully");
fclose(fp);
}

void display(){
clrscr();
printf("<== Student Info ==>\n\n");
printf("%-30s %-20s %-10s %s\n","Name","Class","Roll","Date");
fp = fopen("st.txt","rb");
while(fread(&s,sizeof(s),1,fp)==1){
printf("%-30s %-20s %-10d %s\n",s.na,s.cl,s.rl,s.date);
}
fclose(fp);
printf("Press any key to continue...");
}

void search(){
int ch;

while(1){
clrscr();
printf("<== College Management ==>\n");
printf("<== Search ==>\n");
printf("1.Search By Roll\n");
printf("2.Search By Name\n");
printf("0.Back To Main Menu\n");
printf("\n\nEnter your choice: ");
scanf("%d",&ch);

switch(ch){
case 0:
main();
break;

case 1:
searchByRoll();
break;

case 2:
searchByName();
break;

default:
printf("Invalid Choice");

}
getch();
}
}

void searchByRoll(){
int rl,f=0;
printf("Enter Roll to search: ");
scanf("%d",&rl);
printf("%-30s %-20s %-10s %s\n","Name","Class","Roll","Date");
fp=fopen("st.txt","rb");
while(fread(&s,sizeof(s),1,fp)==1){
if(rl == s.rl){
f=1;
printf("%-30s %-20s %-10d %s\n",s.na,s.cl,s.rl,s.date);
break;
}
}
fclose(fp);
if(f==0)
printf("Record Not Found...");
else
printf("Record Found Successfully...");

}

void searchByName(){
char na[30];
int f=0;
printf("Enter Name to search: ");
fflush(stdin);
gets(na);
printf("%-30s %-20s %-10s %s\n","Name","Class","Roll","Date");
fp=fopen("st.txt","rb");
while(fread(&s,sizeof(s),1,fp)==1){
if(strcmpi(na,s.na)==0){
f=1;
printf("%-30s %-20s %-10d %s\n",s.na,s.cl,s.rl,s.date);
break;
}
}
fclose(fp);
if(f==0)
printf("Record Not Found...");
else
printf("Record Found Successfully...");

}

void modify(){
int rl, f=0;
printf("Enter Roll To Modifiy: ");
scanf("%d",&rl);
fp=fopen("st.txt","rb+");
while(fread(&s,sizeof(s),1,fp)==1){
if(rl == s.rl){
f=1;
printf("Enter New Name: ");
fflush(stdin);
gets(s.na);
printf("Enter Class: ");
scanf("%s",s.cl);
printf("Enter New Roll: ");
scanf("%d",&s.rl);
fseek(fp,-si,1);
fwrite(&s,sizeof(s),1,fp);
fclose(fp);
break;
}
}
if(f==0)
printf("Record Not Found...");
else
printf("Modified Successfully...");

}

void del(){
int rl, f=0;
printf("Enter roll to delete: ");
scanf("%d",&rl);

FILE *ft;
fp = fopen("st.txt","rb");
ft = fopen("temp.txt","ab");

while(fread(&s,sizeof(s),1,fp)==1){
if(rl == s.rl){
f=1;
}else{
fwrite(&s,sizeof(s),1,ft);
}

}
fclose(fp);
fclose(ft);
remove("st.txt");
rename("temp.txt","st.txt");

if(f==0)
printf("Record Not Found...");
else
printf("Record Deleted Successfully...");

}

void sort(){
int ch;

while(1){
clrscr();
printf("<== School Management ==>\n");
printf("<== Sort ==>\n");
printf("1.Sort By Roll\n");
printf("2.Sort By Name\n");
printf("0.Back To Main Menu\n");
printf("\n\nEnter your choice: ");
scanf("%d",&ch);

switch(ch){
case 0:
main();
break;

case 1:
sortByRoll();
break;

case 2:
sortByName();
break;

default:
printf("Invalid Choice");

}
getch();
}

}

void sortByRoll(){
clrscr();
int c=0, i, j;
struct student s1[50],t;
printf("<== School Management ==>\n");
printf("<== Sort By Roll ==>\n");
fp = fopen("st.txt","rb");
while(fread(&s,sizeof(s),1,fp)==1)
s1[c++]=s;

for(i=0; i<c-1; i++){
for(j=i+1; j<c; j++){
if(s1[i].rl >s1[j].rl){
t = s1[i];
s1[i]=s1[j];
s1[j]=t;

}

}
}

printf("%-30s %-20s %-10s %s\n","Name","Class","Roll","Date");

for(i=0; i<c; i++)
printf("%-30s %-20s %-10d %s\n",s1[i].na,s1[i].cl,s1[i].rl,s1[i].date);
}

void sortByName(){
clrscr();
int c=0, i, j;
struct student s1[50],t;
printf("<== School Management ==>\n");
printf("<== Sort By Name ==>\n");
fp = fopen("st.txt","rb");
while(fread(&s,sizeof(s),1,fp)==1)
s1[c++]=s;

for(i=0; i<c-1; i++){
for(j=i+1; j<c; j++){
if(strcmpi(s1[i].na, s1[j].na)>1){
t = s1[i];
s1[i]=s1[j];
s1[j]=t;

}

}
}

printf("%-30s %-20s %-10s %s\n","Name","Class","Roll","Date");

for(i=0; i<c; i++)
printf("%-30s %-20s %-10d %s\n",s1[i].na,s1[i].cl,s1[i].rl,s1[i].date);
}