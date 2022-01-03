#include "Server.hpp"

String SCP_GetAddress(SCP_Server array[],String name)
{
  int index = 0;
  while(NULL != array[index].name)
  {
    if(String(array[index].name).equals(name))
    {
      return String(array[index].address);
    }
    index++;
  }
  return String("");
}
