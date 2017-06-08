#include <wiringPi.h>
#include <stdio.h>
int SER = 12 ;
int RCLK = 10 ;
int SRCLK = 14 ;
unsigned char LED [ 8 ]={ 0x01 , 0x02 , 0x04 , 0x08 , 0x10 , 0x20 , 0x40 , 0x80 };
void SIPO ( unsigned char byte );
void pulse ( int pin );


/* some sort of init function */
void init () {
        pinMode ( SER , OUTPUT );
        pinMode ( RCLK , OUTPUT );
        pinMode ( SRCLK , OUTPUT );
        digitalWrite ( SER , 0 );
        digitalWrite ( SRCLK , 0 );
        digitalWrite ( RCLK , 0 );
}

/* some sort of delay function */
void delayMS ( int x ) {
        usleep ( x * 1000 );
}

/* the main loopy loop */
int main ( void )
{
        if ( - 1 == wiringPiSetup()) {
                printf ( "Setup wiringPi failed!");
                return 1 ;
        }
        init ();
        int i ;
        while ( 1 ) {
                for ( i = 0 ; i < 8 ; i ++)
                {
                SIPO ( LED [ i ]);
                pulse ( RCLK );
                delayMS ( 50 );
                printf ( " i = %d" , i );
                }
        printf ( "\n" );
        delayMS ( 200 ); // 200 ms

        for ( i = 7 ; i >= 0 ; i -- )
                {
                SIPO ( LED [ i ]);
                pulse ( RCLK );
                delayMS ( 50 );
                printf ( " i = %d" , i );
                }
                delayMS ( 500 ); // 500 ms
        }
        usleep ( 1000 );
        digitalWrite( RCLK , 1 );
}

/* color mingler - 0xXX is the led color! */
void SIPO ( unsigned char byte )
{
        int i ;
        for ( i = 0 ; i < 8 ; i ++)
        {
                digitalWrite ( SER ,(( byte & ( 0xAA >> i )) > 0 ));
                pulse ( SRCLK );
        }
}

/* some sort of pulse function */
void pulse ( int pin )
{
        digitalWrite ( pin , 1 );
        digitalWrite ( pin , 0 );
}
