#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct node
{
  char *name; //name of the song
  char *title; //title of the song
  char *artist; //artist of the song

  int   data; //data is the RUNtIME of the song
  struct node *next;
  struct node *prev;
} node_t; 

void reverse();

void delete_artist(const char *artist);
