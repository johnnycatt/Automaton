#include "Atm_blink.hpp"
	
Atm_blink & Atm_blink::begin( int attached_pin, uint32_t blinkrate )
{
  const static state_t state_table[] PROGMEM = {
    /*            ON_ENTER    ON_LOOP  ON_EXIT  EVT_TIMER  EVT_ON  EVT_OFF  ELSE */
    /* IDLE    */  ACT_OFF,        -1,      -1,        -1, LED_ON,      -1,   -1,
    /* LED_ON  */   ACT_ON,        -1,      -1,   LED_OFF,     -1,    IDLE,   -1,
    /* LED_OFF */  ACT_OFF,        -1,      -1,    LED_ON,     -1,    IDLE,   -1,
  };
  Machine::begin( state_table, ELSE );
  pin = attached_pin; 
  timer.set( blinkrate ); 
  pinMode( pin, OUTPUT ); 
  return *this;          
}

int Atm_blink::event( int id ) 
{
  switch ( id ) {
  	case EVT_TIMER :
  	  return timer.expired( this );        
   }
   return 0;
}

void Atm_blink::action( int id ) 
{
  switch ( id ) {
  	case ACT_ON :
  	  digitalWrite( pin, HIGH );
  	  return;
  	case ACT_OFF :
  	  digitalWrite( pin, LOW );
  	  return;
   }
}

Atm_blink & Atm_blink::trace( Stream & stream ) 
{
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "EVT_TIMER\0EVT_ON\0EVT_OFF\0ELSE\0IDLE\0LED_ON\0LED_OFF" );
  return *this;
}


