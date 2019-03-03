double GrossPay(double rate,double hours)
{
	double grossWage;
	if(hours>40)
	{
		grossWage = (40*rate)+((hours-40)*(rate*1.5));
	}
	else
	{
		grossWage = hours*rate;
	}

	return grossWage;
}
