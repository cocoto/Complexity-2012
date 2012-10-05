#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

struct timeval start_utime, stop_utime;

void crono_start()
{
  struct rusage rusage;

  getrusage(RUSAGE_SELF, &rusage);
  start_utime = rusage.ru_utime;
}

void crono_stop()
{
  struct rusage rusage;

  getrusage(RUSAGE_SELF, &rusage);
  stop_utime = rusage.ru_utime;
}

double crono_ms()
{
  return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}


/* dans le main 

double temps;
crono_start();

crono_stop();
        temps = crono_ms()/1000,0;
        std::cout << "temps : " << temps << std::endl << std::endl ;

*/
