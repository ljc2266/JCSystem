void io_hlt();
void write_mem8(int addr, int data);
void JCMain()
{
	int i;
	char *p;
	p = 0xa0000;
	for (i = 0;i<=0xffff;i++)
	{
		p[i] = i &0x0f;
	}
	for(;;)
	{
		io_hlt();
	}
}
