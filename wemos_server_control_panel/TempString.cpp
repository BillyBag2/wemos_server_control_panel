#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TempString.hpp"

TempString::TempString(char * a, char * b) {
  purge();
  string = (char *)malloc(strlen(a) + strlen(b) + 1);
  strcpy(string,a);
  strcat(string,b);
}

TempString::TempString(char * a, char * b,char * c) {
  purge();
  string = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + 1);
  strcpy(string,a);
  strcat(string,b);
  strcat(string,c);
}

void TempString::purge() {
  if(NULL != string) {
    free(string);
    string = NULL;
  }
}

TempString::~TempString() {
  purge();
}
