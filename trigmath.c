#include "trigmath.h"
#include "space.h"

// This is from here: http://stackoverflow.com/a/1026370/1871287
// it is initially seeded with the time
float prand (unsigned int *seed)
{
  unsigned int next = *seed;
  int result;
  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  *seed = next;

  return result / 2147483647.0;
}
