#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include "colour.h"


void login();
void createacc();
int checkstrenght(char[]);
char generate(char[], char[], char[], char[]);

void dashboard(char[]);


struct user{
	char first_name[20];
	char last_name[20];
	char age[2]; 
	char username[50];
	char password[50];
	char birth[50];
	char veripass[50]; //to verify password
	float balance;
}us;

int main(){
	//file
	FILE *fuser;
	
	//variables
	int choice;
	
	//login page
	textcolor(3);
	printf("\n\t\t\t-------WELCOME TO SHAHPAY-------\t\t\t\n\n");
	textcolor(11);
	char welcome[100] = "\t1- Login \n\t2-Create an account\n\t";
	
	for(int i=0; welcome[i]!='\0'; i++){
			printf("\a");
			Sleep(10);
			if(welcome[i]==32){
				Sleep(100);
			}
			printf("%c", welcome[i]);
	}
	printf(":");
	scanf("%d", &choice);
	system("cls");
	
	switch(choice){
		case 1:
			login();
			break;
		case 2:
			createacc();
			system("cls");	
			login();
			break;
		}
			
	//All Copyright Reserved by S.Shahzain Zaidi 22k-4112
	
	return 0;
}

//login
void login(){

	FILE *fptr;
	char username[50], password[50], filename[50], pwdfile[50], ch, first[50], last[50];
	int i, flag=0, pwdflag = 0;
		
	textcolor(15);

	Login: //for Goto statement 
	printf("\n\t\t\t--------Login Now!--------\n\n\n");
	
	int checkpwd = 0;
	do{
		printf("\t\e[1mUsername\e[m: ");
		scanf("%s", &username);
		
		strcpy(filename, username);
		fptr= fopen(strcat(filename,".txt"), "r");
		
		if(fptr==NULL){
			textcolor(4);
			printf("\n\aUsername Doesn't Exist\nRe-enter your username\n");
			
		}
	}while(fptr==NULL);
	
	
	fscanf(fptr,"%s \n%s \n%s", first,last,pwdfile);
	
	do{
		
		
		if(checkpwd>=3){
			printf("\n\tYou exceed Limit\n"); //3 Limits
			Sleep(500); //pause for a while
			system("cls");
			goto Login;
		}
		
		if(checkpwd==0){
			printf("\tPassword: ");
		}
		else{
			printf("\n\tRe-Enter Password: ");
		}
		
		//Masking with *
		for(i=0; i<20; i++){
			ch = getch();
			if(ch == 13){
				break;
			}
			password[i] = ch;
			ch = '*';
			printf("%c", ch);
		}
		
		password[i] = '\0';
		

			
			if(strcmp(pwdfile,password)==0){
				pwdflag = 1;
			}
			else{
				pwdflag = 0;
			}	
		
//			if(pwdflag==1){
//				printf("Correct Password\n");
//			}	
//			else{
//				printf("\tIncorrect Password\n");
//			}

			checkpwd += 1;
			
	}while(pwdflag==0);
	     
	Sleep(500);
		
	fclose(fptr);
	
	dashboard(username);
}


//Account Creating then Storing in a file
void createacc(){
	//Sign up

	textcolor(15);
	FILE *fptr;
	char filename[50], proceed;
	int i, flag=0, choice; //to store function return of pswd strenght
	int verifyflag = 0; //for verify pswd
	printf("\n\t\t\t---------------Create Account!---------------\n\n\n");
	
	textcolor(11);
	printf("\tFirst Name: ");
	scanf("%s", us.first_name);
	
	printf("\tLast Name: ");
	scanf("%s", us.last_name);
	
	printf("\tAge: ");
	scanf("%s", us.age);

	printf("\tYear Of Birth: ");
	scanf("%s", us.birth);
	
	printf("\tUsername: ");
	scanf("%s", us.username);

	strcpy(filename, us.username);
	fptr = fopen(strcat(filename,".txt"),"w");

	
	do{
		if(flag==0){
			printf("\t1-Enter a Strong Password\n\t2-Generate a strong password for you\n\n");
			scanf("%d", &choice);
			
			switch(choice){
				case 1:
					break;
				case 2:
					
					generate(us.first_name, us.last_name, us.age, us.birth);
					break;
			}
		}
		
			textcolor(11);
			printf("\n\t\tPassword: ");
			scanf(" %[^\n]s", us.password); //[^\n] used to count spaces
			
			flag = checkstrenght(us.password);
//			printf("flag = %d\n", flag);
		
	}while(flag!=1);
		
		textcolor(11);
		do{
			printf("\t\tConfirm Password: ");
			scanf("%s", us.veripass);
			
			if(strcmp(us.password,us.veripass)==0){
				verifyflag = 1;
			}
			else if(strcmp(us.password,us.veripass)!=0){
				printf("\a\n\t----Password Doesn't Match----\n");
			}
		
		}while(verifyflag==0);
	
	us.balance = 0;
		
	fprintf(fptr, "%s \n%s \n%s \n%f", us.first_name, us.last_name, us.password, us.balance);
	
	
	textcolor(10);
			char message[100] = "\t\t----------------Thanks for Creating your Account----------------\n\t\t\t\tPress any key to sign\n";
		
			for(int i=0; message[i]!='\0'; i++){
				Sleep(20);
				printf("\a");
				printf("%c", message[i]);
			}
			
	scanf(" %c",&proceed);
	
	fclose(fptr);


}


int checkstrenght(char pass[]){
	
	int i=0 , lenght=0 , capital = 0, lower = 0, space = 0, special = 0, number = 0, n=0;

	//Check lenght
	while((pass[i]!='\0')){
		lenght++;
		
		if(pass[i]>=65 && pass[i]<=90){
			capital++;
		}
		else if(pass[i]>=97 && pass[i]<=122){
			lower++;
		}
		else if(pass[i]==32){
			space++;
		}
		else if(pass[i]>=48 && pass[i]<=57){
			number++;
		}
		else{
			special++;
		}
		
		i++;
	}
	
		
		if((lenght>=8 && capital>=2 && special>=2) || (lenght>=8 && capital>=1 && special>=1 && number>=2) || (lenght>8 && number>=5 && capital>=1)
		 || (lenght>=13 && (number==1 || special>=1 || space>=1))){
		 	textcolor(10);
			printf("\t\tSecured Password\n\n");
			return 1;
		}
		
		else if((lenght>=8 && capital==1 && (special==1 || space==1 || number==1) || (lenght>=8 && number>=4 && (space==1 || special==1)))){
			textcolor(11);
			printf("\t\tStrong Password\n\n");
			return 1;
		}
		
		else if(((lower>=8 || capital>=4) && number>=3) || ((lower>=8 && lower<=10 || capital>=4) && number==1 && special==0 && space==0)
		|| (lower>=13) || (lower>=5 && capital==1 && number>=2)){
			textcolor(3);
			printf("\t\tModerate Password\n\n");
			return 1;
		}
		
		else if((lenght<8 || (special==1 || space==1 || capital==1)) || (lenght<8 && capital==1) || (number>=1) || (lower<13)){
			textcolor(4);
			printf("\t\tWeek Password\n\n");
			return 0;
		}
		else
			printf("error in strenght function!\n\n");
			return 0;
	

	
	printf("lenght: %d\n", lenght);
	printf("capital: %d\n", capital);
	printf("lower: %d\n", lower);
	printf("Space: %d\n", space);
	printf("Number: %d\n", number);
	printf("Special: %d\n", special);
	printf("n: %d\n", n);
	
}

//genrating a strong password
char generate(char first[], char last[], char age[], char birth[]){

	int i, j, choice;
	char firstpwd[30], secpwd[30], thirdpwd[30];

	
	strcpy(firstpwd,first);
	
	if(strlen(firstpwd)<=4){
			strcat(firstpwd,last);
	}
	
	strcat(firstpwd,"@");
	strcat(firstpwd,age);
	textcolor(7);
	printf("\n [1] %s \n", firstpwd);
	
	//2nd Generated Password
		
	strcpy(secpwd,"Thisis");
	strcat(secpwd,last);
	
	for(i=1; secpwd[i]!='\0'; i++){
		if(secpwd[i]>=65 && secpwd[i]<=90){
			secpwd[i] = secpwd[i] + 32;
		}
	}	
	strcat(secpwd,"!");
	strcat(secpwd,"1");
	textcolor(14);
	printf("\n [2] %s \n", secpwd);
	
	//3rd Generated Password
	
	strcpy(thirdpwd,last);
	for(i=0; thirdpwd[i]!='\0'; i++){
		if(thirdpwd[i]>=97 && thirdpwd[i]<=122){
			thirdpwd[i] = thirdpwd[i] - 32;
		}
	}
	
	if(strlen(thirdpwd)<=4){
			strcat(thirdpwd,first);
	}
	
	strcat(strcat(thirdpwd,"_"), birth);
	textcolor(15);
	printf("\n [3] %s \n", thirdpwd);
	
//	printf("\n\tChoose Password you want\n");
//	scanf("%d", choice);
//	
//	switch(choice){
//		case 1:
//			ptr = firstpwd;
//			return ptr;
//	} 
	
}


//After Login
void dashboard(char usname[]){
	
	FILE *fptr;
	FILE *rfile;  //reciever file
	char filename[30], reciever[30], rfilename[30];
	float amount, service, total, rbalance;
	int key; //to logout or continue
	strcpy(filename,usname);
	
	fptr = fopen(strcat(filename,".txt"),"a+");
	fscanf(fptr,"%s \n%s \n%s", us.first_name, us.last_name, us.password);
	
	while(getc(fptr)!=EOF){
		fscanf(fptr,"%f\n", &us.balance);
	}
	
	dashboard:
	system("cls");
	printf("\n---------Welcome %s----------\n\n", us.first_name);
	
	int choice = 0;
	
	while(choice!=4){
		
		printf("\t[ 1 ] Check your Balance\n");
		printf("\t[ 2 ] Deposit Cash\n");
		printf("\t[ 3 ] Online transfer\n");
		printf("\t[ 4 ] Transfer History\n");
		printf("\t[ 5 ] Change Password\n");
		printf("\t[ 6 ] Logout\n");
		
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				textcolor(10);
				printf("Current Account Balance:\n\t %f\n", us.balance);
				textcolor(15);
				break;
				
			case 2:
				
				system("cls");
				
				fptr = fopen(filename,"r+");
				fscanf(fptr,"%s \n%s \n%s", us.first_name, us.last_name, us.password);
				
				while(getc(fptr)!=EOF){
					fscanf(fptr,"%f\n", &us.balance);
				}
							
				char useradmin[20], userpwd[20], uadmin[20]= "admin", upwd[20] = "admin";
				float deposit;
				
				printf("\n\t\tDeposite Cash in your Account\n");
				printf("\n\t\t------------------------------\n");
				printf("\t\tEnter Admin Username: ");
				scanf("%s", useradmin);
				
				printf("\t\tEnter Admin Password: ");
				scanf("%s", userpwd);
				
				
				if(strcmp(useradmin,"admin")==0 && strcmp(userpwd,"admin")==0 ){
					
					printf("\n\t\tEnter Amount:");
					scanf("%f", &deposit);
					
					us.balance = us.balance + deposit;
					
					printf("\n\t\tCurrent Balance:      Rs. %.2f \n", us.balance);
				
					textcolor(10);
					char message[100] = "\t\t----------------Money Deposited----------------\n\t\t\t\tThanks for choosing Shahpay\n";
				
					for(int i=0; message[i]!='\0'; i++){
						Sleep(20);
						printf("\a");
						printf("%c", message[i]);
					}
					
					//printing on file
					fprintf(fptr,"\nRs.%.2f Deposited \nBalance Remaining: %.2f", deposit, us.balance);
					fclose(fptr);
				}
				 	
				 	
					textcolor(15);
						
					printf("\n\n\n\n");
					textcolor(14);
					break;
				
			case 3:
				system("cls");
				printf("\n\t\tTransfer money to anyone on ShahPay for free \n");
				printf("\n\t\t-------------------------------------------- \n");
				
				do{
					printf("\t\tEnter Receiver's Username: ");
					scanf("%s", reciever);
					
					strcpy(rfilename,reciever);
					rfile = fopen(strcat(rfilename,".txt"),"r+");
					
					if(rfile==NULL){
						Sleep(500);
						printf("\n\t\tuser not found\n");
					}
					else{
						break;
					}
				}while(1);
				
				while(1){
					printf("\t\tEnter Amount:");
					scanf("%f", &amount);
					
					if(amount>us.balance){
						printf("\n\t\tInsufficient Balance\n");
					}
					else{
						break;
					}
				}
				printf("\n\t\t\e[1mTRANSACTION DETAILS\e[m\n");
				printf("\n\t\tTRANSACTION ID:       %s", reciever);
				
				time_t t;
				time(&t);
				printf("\n\t\tTRANSACTION Time:     %s", ctime(&t));
				
				printf("\n\t\tAMOUNT DETAILS\n");
				printf("\n\t\tAmount Withdrawn:     Rs. %.2f", amount);
				
				service = 0.05*amount;
				
				printf("\n\t\tService Fee:          Rs. %.2f", service);
				total = service+amount;
				printf("\n\t\tTotal Amount:         Rs. %.2f \n", total);
				
				us.balance = us.balance-total;
				
				printf("\n\t\tCurrent Balance:      Rs. %.2f \n", us.balance);
				
				textcolor(10);
				char message[100] = "\t\t----------------Money Transfered----------------\n\t\t\t\tThanks for choosing Shahpay\n";
			
				for(int i=0; message[i]!='\0'; i++){
					Sleep(20);
					printf("\a");
					printf("%c", message[i]);
				}
				
				//printing on file
				fprintf(fptr,"\nRs.%.2f Transfer To %s\nBalance Remaining: %.2f", amount, reciever, us.balance);
				
				while(getc(rfile)!=EOF){
					fscanf(rfile,"%f\n", &rbalance);
				}
				rbalance = rbalance + total;
				fprintf(rfile,"\nRs.%.2f Transfer from %s\n%.2f", amount, usname, rbalance);
				
				fclose(rfile);
				fclose(fptr);
				
				textcolor(15);
				printf("\n\n\t\tPress any Key to Continue OR 0 to get logout\n");
				scanf("%d", &key);
				
				
				if(key=='0'){
					system("cls");
					main();
				}
				else{
					dashboard(usname);
				}
				break;
				
				case 4:
					system("cls");
					printf("\n\t\tYOUR TRANSFER HISTORY \n");
					printf("\n\t\t----------------------\n");
					
//					fptr = fopen(filename,"r");
//					printf("%s", filename);
//					
//					char c;
//					
//					if(fptr == NULL){
//						printf("File doesn't Exist\n");
//					}
//					else{
//						while((c = fgetc(fptr) != EOF)){
//						putchar(c);
//						}
//					}
//			
//					fclose(fptr);
					textcolor(15);
					printf("\n\n\t\tPress any Key to Continue OR 0 to get logout\n");
					scanf("%d", &key);
				
					
				//Changing Password	
				case 5:
					system("cls");
					
//					char confirmpwd[20], newpwd[20];; 
//					int cnfrmflag = 0;
//					printf("\n\t\tPASSWORD CHANGE \n");
//					printf("\n\t\t----------------\n");
//					
//					fptr = fopen(filename,"r");
//					if(fptr==NULL){
//						printf("File doesn't exist\n");
//					}
//					fscanf(fptr,"%s \n%s \n%s", us.first_name, us.last_name, us.password);
//					fclose(fptr);
//					
//					do{
//						printf("Confirm Your Password\n");
//						scanf("%s", confirmpwd);
//						
//						if(strcmp(us.password,confirmpwd)==0){
//							cnfrmflag = 1;
//						}
//					}while(cnfrmflag!=1);
//					
//					printf("New Password\n");
//					scanf("%s", newpwd);
					break;
					
				case 6:
					system("cls");
					main();
					
				default:
					printf("\n\t\t Invalid Value!\n");
					break;
		}
	}
	
}