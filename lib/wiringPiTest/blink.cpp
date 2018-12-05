#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);

  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  for (;;)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
   digitalWrite (0,  LOW) ; delay (500) ;

  }
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  return 0 ;
}
