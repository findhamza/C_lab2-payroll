#include "structs.h"
#include <locale.h>
#include <monetary.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Heading();
void NewPage();
void PrintEmp(struct emp empInfo, double grossWage, double ficaTax);
void PageTotal(double pageWage, double pageTax, int pageNum);
void DeptTotal(char *dept, double deptWage, double deptTax);
void Footer(double totalWage, double totalTax, int totalRecords);
void Protection_buff();
