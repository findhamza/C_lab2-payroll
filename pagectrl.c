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
	char h_buffer[750];

	char acme[] = "ACME Sports Inc.";
	char motto[] = "We are the best, you use the best!";
	sprintf(h_buffer, "\n%s\n\n%s\n%s", PageBrk(), CntrTxt(acme), CntrTxt(motto));

//	printf("%s",h_buffer);
	print(h_buffer);
}
void NewPage()
{
	char n_buffer[750];

	char acme[] = "ACME";
	sprintf(n_buffer, "\n%s\n%s\n\nEMP#\tNAME     \t\tDEPT.\t     NEW YTD\t\tGROSS\t\tFICA\t\tNET\n\n",
		PageBrk(), CntrTxt(acme));

//	printf("%s",n_buffer);
	print(n_buffer);
}
void PrintEmp(struct emp empInfo, double grossWage, double ficaTax)
{
	char e_buffer[750];

	sprintf(e_buffer, "%4.0d\t%-9.9s %-13.9s %-7.5s %12s%17s%15s%15s\n", empInfo.empNum,
		empInfo.first, empInfo.last, empInfo.dept, MonFrmt((empInfo.ytd)+grossWage),
		MonFrmt(grossWage), MonFrmt(ficaTax), MonFrmt((grossWage-ficaTax)));

	print(e_buffer);
}
void PageTotal(double pageWage, double pageTax, int pageNum)
{
	char p_buffer[750];

	char *bttmDash = malloc(32 * sizeof(char));
	char *spaceSet = malloc(91 * sizeof(char));
	memset(bttmDash, '_', 31);
	memset(spaceSet, ' ', 90);
	sprintf(p_buffer, "\n%s PAGE TOTALS:%25s%15s%15s\n\n%sPAGE:%4d\n%s\f\r\n", bttmDash, 
		MonFrmt(pageWage), MonFrmt(pageTax),
		MonFrmt(pageWage-pageTax), spaceSet, pageNum, PageBrk());

	print(p_buffer);
}
void DeptTotal(char *dept, double deptWage, double deptTax)
{
	char d_buffer[750];

	char deptStr[] = " DEPT. TOTALS:";
	char *bttmDot = malloc(32 * sizeof(char));
	memset(bttmDot, '.', 31);
	sprintf(d_buffer, "\n%s %-6.5s%-9.14s %16s%15s%15s\n\n", bttmDot, dept, deptStr,
		MonFrmt(deptWage), MonFrmt(deptTax), MonFrmt(deptWage-deptTax));

	print(d_buffer);
}
void Footer(double totalWage, double totalTax, int totalRecords, int pageNum)
{
	char f_buffer[750];

	double netPay = totalWage-totalTax;

	char fTitle[] = "Report Summary";
	char tRecords[] = "Records Processed: ";
	char tGross[] = "Total Gross: ";
	char tNet[] = "Total Net: ";
	char tFica[] = "Total FICA";

	char *spaceSet = malloc(91 * sizeof(char));
	memset(spaceSet, ' ', 90);

	sprintf(f_buffer, "\n%s\n%s\n\n%-25s%10d \n%-25s%10s \n%-25s%10s \n%-25s%10s\n\n%sPAGE:%4d\n%s\r\n",
		PageBrk(), CntrTxt(fTitle), tRecords, totalRecords, tGross, MonFrmt(totalWage),
		tNet, MonFrmt(netPay), tFica, MonFrmt(totalTax), spaceSet, pageNum, PageBrk());

	print(f_buffer);
}
void Protection_buff()
{
	char *p_buffer = malloc(12 * sizeof(char));
	memset(p_buffer, ' ', 11);
	print(p_buffer);
	free(p_buffer);
}
