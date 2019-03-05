#include "pagectrl.h"

char *PageBrk()
{
	char *pgbrk = malloc(100 * sizeof(char));
	memset(pgbrk, '=', 99);
	return pgbrk;
}
char *CntrTxt(char *text)
{
	char *cText = malloc(100 * sizeof(char));
	memset(cText, ' ',(99/2)-(strlen(text)/2));
	strcat(cText,text);
	return cText;
}
char *MonFrmt(double monInput)
{
	setlocale(LC_ALL, "");
	char *string = malloc(100 * sizeof(char));
	strfmon(string, 100, "%n", monInput);
	return string;
}
void print(char *buffer)
{
	printf("%s",buffer);
	FILE *outFile = fopen("tempPayRollFile5569.txt", "a+");
	fseek(outFile,0,SEEK_END);
	fputs(buffer, outFile);
	fflush(outFile);
}
void Heading()
{
	char h_buffer[300];

	char acme[] = "ACME Sports Inc.";
	char motto[] = "We are the best, you use the best!";
	sprintf(h_buffer, "\n%s\n\n%s\n%s", PageBrk(), CntrTxt(acme), CntrTxt(motto));

//	printf("%s",h_buffer);
	print(h_buffer);
}
void NewPage()
{
	char n_buffer[510];

	char acme[] = "ACME";
	char emp[] = "EMP#";
	char name[] = "NAME";
	char dept[] = "DEPT.";
	char ytd[] = "NEW YTD";
	char gross[] = "GROSS";
	char fica[] = "FICA";
	char net[] = "NET";
	sprintf(n_buffer, "\n%s\f\r\n%s\n%s\n\n%-8s%-24s%-13s%-19s%-16s%-16s%s\n\n",
		PageBrk(), PageBrk(), CntrTxt(acme), emp, name, dept, ytd, gross, fica, net);

//	printf("%s",n_buffer);
	print(n_buffer);
}
void PrintEmp(struct emp empInfo, double grossWage, double ficaTax)
{
	char e_buffer[200];

	sprintf(e_buffer, "%4.0d\t%-9.9s %-13.9s %-7.5s %12s%17s%15s%15s\n", empInfo.empNum,
		empInfo.first, empInfo.last, empInfo.dept, MonFrmt((empInfo.ytd)+grossWage),
		MonFrmt(grossWage), MonFrmt(ficaTax), MonFrmt((grossWage-ficaTax)));

	print(e_buffer);
}
void PageTotal(double pageWage, double pageTax, int pageNum)
{
	char p_buffer[390];

	char *bttmDash = malloc(32 * sizeof(char));
	char *spaceSet = malloc(91 * sizeof(char));
	memset(bttmDash, '_', 31);
	memset(spaceSet, ' ', 90);
	sprintf(p_buffer, "\n%s PAGE TOTALS:%25s%15s%15s\n\n%sPAGE:%4d", bttmDash, 
		MonFrmt(pageWage), MonFrmt(pageTax),
		MonFrmt(pageWage-pageTax), spaceSet, pageNum);

	print(p_buffer);
}
void DeptTotal(char *dept, double deptWage, double deptTax)
{
	char d_buffer[200];

	char deptStr[] = " DEPT. TOTALS:";
	char *bttmDot = malloc(32 * sizeof(char));
	memset(bttmDot, '.', 31);
	sprintf(d_buffer, "\n%s %-6.5s%-9.14s %16s%15s%15s\n\n", bttmDot, dept, deptStr,
		MonFrmt(deptWage), MonFrmt(deptTax), MonFrmt(deptWage-deptTax));

	print(d_buffer);
}
void Footer(double totalWage, double totalTax, int totalRecords)
{
	char f_buffer[900];

	char fTitle[] = "Report Summary";
	char tRecords[] = "Records Processed: ";
	char tGross[] = "Total Gross: ";
	char tNet[] = "Total Net: ";
	char tFica[] = "Total FICA";

	sprintf(f_buffer, "\n%s\f\r\n%s\n%s\n\n%-25s%10d \n%-25s%10s \n%-25s%10s \n%-25s%10s\n\n%s\n",
		PageBrk(), PageBrk(), CntrTxt(fTitle), tRecords, totalRecords, tGross, MonFrmt(totalWage),
		tNet, MonFrmt(totalWage-totalTax), tFica, MonFrmt(totalTax), PageBrk());

	print(f_buffer);
}
void Protection_buff()
{
	char *p_buffer = malloc(12 * sizeof(char));
	memset(p_buffer, ' ', 11);
	print(p_buffer);
	free(p_buffer);
}
