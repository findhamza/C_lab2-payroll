/* Author: Hamza Syed */
/* COSC 2347          */
/* Lab 1, Option A    */
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "structs.h"
#include "fica.h"
#include "gross.h"
#include "pagectrl.h"

char *FileReader(char *fileName);
struct fica GetFica();
void OpEmp(struct fica);

int main()
{
	struct fica ficaInfo = GetFica();

	OpEmp(ficaInfo);

	return 0;
}

char *FileReader(char *fileName)
{
	char *buffer=NULL;
	int strSize,readSize;
	FILE *file = fopen(fileName,"r");

	if(file)
	{
		fseek(file,0,SEEK_END);
		strSize = ftell(file);
		rewind(file);

		buffer = (char*) malloc(sizeof(char) * (strSize+1));
		readSize = fread(buffer, sizeof(char), strSize, file);
		buffer[strSize] = '\0';

		if(strSize != readSize)
		{
			free(buffer);
			buffer = NULL;
		}

		fclose(file);
	}

	return buffer;
}

struct fica GetFica()
{
	char ficaFile[] = "fica.dat";
	char *ficaText = FileReader(ficaFile);

	if(ficaText==NULL)
	{
		printf("Missing FICA file...\nPlease contact management for fica.txt file...");
		printf("\n\nThis Program Will Now Self Terminate\n\n");
		exit(0);
	}

	struct fica ficaInfo;
	double rate,limit;
	char delimit[] = " \t\r\n\v\f";
	char *ficaToken = strtok(ficaText,delimit);
	while(ficaToken)
	{
		if(strcmp(ficaToken,"RATE")==0)
		{
			rate = atof(strtok(NULL,delimit));
		}
		if(strcmp(ficaToken,"LIMIT")==0)
		{
			limit = atof(strtok(NULL,delimit));
		}
		ficaToken = strtok(NULL,delimit);
	}
	ficaInfo = (struct fica){.ficaRate = rate,.ficaLimit = limit};
	return ficaInfo;
}

void OpEmp(struct fica ficaInfo)
{
	struct emp empInfo;
	double empGross,empFica;

	int empCounter=0;
	int totalEmp=0;
	double pageWage,pageTax;
	double totalWage,totalTax;
	double deptWage,deptTax;
	char *dept="";

	char empFile[30];
	printf("\nPlease enter employee file: ");
	scanf("%s",empFile);
	char *empText = FileReader(empFile);

	if(empText==NULL)
	{
		printf("\nINCORRECT OR MISSING FILE...");
		printf("\nPlease ensure:\n1) File exist\n2) Not Empty\n3) In correct directory");
		printf("\n\nThis Program Will Now Self Terminate\n\n");
		exit(0);
	}

	char empOut[30];
	printf("\nPlease enter payroll file name: ");
	scanf("%s",empOut);
	if(access(empOut, F_OK) != -1)
	{
		printf("\nFILE ALREADY EXIST\n\nThis Program Will Now Self Terminate\n\n");
		exit(0);
	}


	Heading();

	char delimit[] = " \t\r\n\v\f";
	char *empTokNum = strtok(empText,delimit);

	NewPage();
	while(empTokNum)
	{
		totalEmp+=1;
		empInfo = (struct emp)	{.empNum = atoi(empTokNum),
					.first = strtok(NULL,delimit),
					.last = strtok(NULL,delimit),
					.dept = strtok(NULL,delimit),
					.ytd = atof(strtok(NULL,delimit)),
					.rate = atof(strtok(NULL,delimit)),
					.hrs = atof(strtok(NULL,delimit))};

		empTokNum = strtok(NULL,delimit);

		empGross = GrossPay(empInfo.rate,empInfo.hrs);
		empFica = FicaCalc(ficaInfo,empGross,empInfo.ytd);

		if(!(dept && !dept[0]) && strcmp(dept,empInfo.dept)!=0)
		{
			DeptTotal(dept,deptWage,deptTax);
			deptWage=0; deptTax=0;
			if(empCounter==3)
			{
				empCounter=0;
				PageTotal(pageWage,pageTax,(int)(totalEmp/4));
				pageWage=0; pageTax=0;
				NewPage();
			}
		}
		if(empCounter==4)
		{
			empCounter=0;
			PageTotal(pageWage,pageTax,(int)(totalEmp/4));
			pageWage=0; pageTax=0;
			NewPage();
		}

		PrintEmp(empInfo,empGross,empFica);

		deptWage += empGross;
		deptTax += empFica;

		pageWage+=empGross;
		pageTax+=empFica;

		totalWage+=empGross;
		totalTax+=empFica;

		dept = empInfo.dept;
		empCounter++;
	}
	DeptTotal(dept,deptWage,deptTax);
	PageTotal(pageWage,pageTax,(int)(totalEmp/4));
	Footer(totalWage,totalTax,totalEmp);

	Protection_buff();

	int close_all = fcloseall();
	fflush(stdout);

	rename("tempPayRollFile5569.txt", empOut);


	return;
}
