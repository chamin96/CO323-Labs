/* localtime example */
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;

  while (1){
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "Current local time and date: %s", asctime (timeinfo) );
    sleep(3);
  }
  

  return 0;
}