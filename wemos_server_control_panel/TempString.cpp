#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TempString.hpp"

TempString::TempString(char * a, char * b) {
  string = (char *)malloc(strlen(a) + strlen(b) + 1);
  strcpy(string,a);
  strcat(string,b);
}

TempString::TempString(char * a, char * b,char * c) {
  string = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + 1);
  strcpy(string,a);
  strcat(string,b);
  strcat(string,c);
}

TempString::TempString(char * a, char * b,char * c, char * d) {
  string = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + 1);
  strcpy(string,a);
  strcat(string,b);
  strcat(string,c);
  strcat(string,d);
}

TempString::TempString(char * a, char * b,char * c, char * d, char * e) {
  string = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + 1);
  strcpy(string,a);
  strcat(string,b);
  strcat(string,c);
  strcat(string,d);
  strcat(string,e);
}

TempString::TempString(char * a, char * b,char * c, char * d, char * e, char * f) {
  string = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + 1);
  strcpy(string,a);
  strcat(string,b);
  strcat(string,c);
  strcat(string,d);
  strcat(string,e);
  strcat(string,f);
}

TempString::TempString(char * a, char * b,char * c, char * d, char * e, char * f, char * g) {
  string = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g) + 1);
  strcpy(string,a);
  strcat(string,b);
  strcat(string,c);
  strcat(string,d);
  strcat(string,e);
  strcat(string,f);
  strcat(string,g);
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
