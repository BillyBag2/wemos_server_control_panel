#include <WString.h>

typedef struct SCP_Server {
  char * name;
  char * address;
} SCP_Server;

extern SCP_Server private_servers[];
String SCP_GetAddress(SCP_Server array[],String name);
