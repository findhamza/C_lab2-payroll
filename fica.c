#include "fica.h"

double FicaCalc(struct fica ficaInfo, double grossWage, double ytd)
{
	double ficaMultiplyer = .01*ficaInfo.ficaRate;

	if(ytd>=ficaInfo.ficaLimit)
		return 0;
	else if((ytd+grossWage)<=ficaInfo.ficaLimit)
		return (grossWage*ficaMultiplyer);
	else
		return ((ficaInfo.ficaLimit-ytd)*ficaMultiplyer);
}
