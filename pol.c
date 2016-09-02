#define F_CPU 16000000UL    // Setting Frecquency
#include <avr/io.h> 
#include <util/delay.h>
#define direction DDRB       
#define databus PORTD
#define control PORTB
#define rs 0                // setting register select to pin 0
#define rw 1				// setting read write to pin 1
#define en 2				// setting enable to pin 2 
void datawrite(char data)
{
	databus = (data & 0xF0); // creating a nibble
	control |= 1<<rs;        // setting register select to 1, i.e. Data Write mode
	control &=~(1<<rw);		// setting read write pin to 0, i.e setting up for read mode
	control |= 1<<en;		// Setting enable line to 1
	_delay_ms(20);
	 control &= ~(1<<en);	// setting enable to 0
	databus = ((data <<4) & 0xF0);	
	control |= 1<<rs;	// setting register select to 1 
	control &=~(1 << rw); // setting read write pin to 0, i.e setting up for read mode
	control |= 1<<en; // Setting enable line to 1 
	_delay_ms(20);
	 control &= ~(1<<en);   // again setting enable to 0
	_delay_ms(2);
}
void lcdcmd(char cmd)
{
	databus = (cmd & 0xF0);  // creating a nibble
	control &=~(1<<rs | 1<<rw);	// setting register select and read write pin to 0, set register select in command mode and read write pin to read mode
	control |= 1<<en;		// setting enable to 1
	_delay_ms(20);
	control &= ~(1<<en);	// setting enable to 0
	databus = ((cmd<<4) & 0xF0);	
	control &=~(1<<rs);	// setting register select and read write pin to 0, set register select in command mode and read write pin to read mode
	control &=~(1<<rw);
	control |= 1<<en;	// setting enable to 1
	_delay_ms(20);
	 control &= ~(1<<en);	// setting enable to 0
	_delay_ms(2);	
}
void main()
{
	DDRB = 0x07;
	DDRD = 0xF0;
	_delay_ms(15);
	lcdcmd(0x01);		//Clearing lcd
	lcdcmd(0x20);		//
	lcdcmd(0x28);		//Enable Display/Curso
	lcdcmd(0x0c);		//Clear and Home
	lcdcmd(0x06);		//Set Cursor Move Direction
	lcdcmd(0x80);		//Moves cursor to first address on the left of LINE 1
	while(1)
	{
		datawrite(0x41);
		datawrite(0x44);
		datawrite(0x49);
		datawrite(0x54);
		datawrite(0x49);
		lcdcmd(0xC0);
		datawrite('B');
		datawrite('A');
		datawrite('I');
		datawrite('N');
		datawrite('S');
		datawrite('S');
		_delay_ms(2000);
		lcdcmd(0x01);
		datawrite(0x50);
		datawrite(0x41);	
		datawrite(0x52);	// Writing name
		datawrite(0x49);
		datawrite(0x4b);	
		datawrite(0x53);	
		datawrite(0x48);	
		datawrite(0x49);	
		datawrite(0x54);	
		lcdcmd(0xC0);			// getting cursor in line 2
		datawrite(0x50);
		datawrite(0x52);	
		datawrite(0x55);
		datawrite(0x54);	
		datawrite(0x48);
		datawrite(0x49);
		_delay_ms(2000);
		lcdcmd(0x01);
	}
}
