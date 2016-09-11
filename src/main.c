#include	<avr/io.h>
#include	<util/delay.h>
#define	BLINK_DELAY_MS	1000
int	main (void)
{
    /*	set	pin	3	of	PORTB	for	output*/
    DDRA	|=	_BV(DDA3);
    
    while(1)	{
        /*	set	pin	3	high	to	turn	led	on	*/
        PORTA	|=	_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
        
        /*	set	pin	3	low	to	turn	led	off	*/
        PORTA	&=	~_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
    }
}