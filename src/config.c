
#include <stdio.h>
#include <string.h>

#include "../include/module.h"

void load_config(const char* path)
{
 FILE* file = fopen(path, "r");

 if(!file)
  return;

 char line[256];

 while(fgets(line, sizeof(line), file))
 {
  line[strcspn(line, "\n")] = '\0';

  for(int i = 0; modules[i].name != NULL; i++)
  {
   if(strcmp(line, modules[i].name) == 0)
   {
       modules[i].function();
       break;
   }
  }
 }

 fclose(file);
}
