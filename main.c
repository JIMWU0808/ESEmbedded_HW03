

void reset_handler(void)
{
	int i,j,k;
        k=1;
	j=0;
	for(i=1;i<10;i++)
	{
		j+=i;
		k*=i;
	}
	plus(j,k);
	while (1)
		;
}
int plus(int j,int k)
{
	return j+k;
}
