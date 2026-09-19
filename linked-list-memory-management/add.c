#include "mp3.h"

extern node_t *head;

void insert(char *name, int num)
{
  node_t *temp, *mp3;

  mp3 = (node_t *) malloc(sizeof(node_t));        // malloc space for MP3
  mp3->name = (char *) malloc(strlen(name) + 1);  // malloc space for name
  strcpy(mp3->name, name);                        // "assign" name via copy
  mp3->data = num;                                // assign data value
  mp3->next = NULL;

  if (head == NULL)
  {
    head = mp3;               
  }
  else
  {
    temp = head;
    while (temp->next != NULL)
      temp = temp->next;
    temp->next = mp3;         
  }
}
void reverse()
//setting up the pointers
//prev will keep track of my last node
//current points to next REMEMBER THIS PLEASE
{
    node_t *prev = NULL, *current = head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        
        current->next = prev;
        prev = current;
        current = next;
    }
     // Once the loop ends, prev points to the new head of the reversed list
    // so we update the head pointer to show it
    head = prev;
}
//this is the function that deletes the artist
void delete_artist(const char *artist)
{
    node_t *current = head; // current is the head
    node_t *prev = NULL; //tracks previous node
    node_t *temp;

    while (current != NULL) { 
      //check if current node's name matches my artist
        if (strncmp(current->name, artist, strlen(artist)) == 0)
        //if the artist to delete is at the head 
        {
            if (prev == NULL) {
            
                head = current->next; // update head to next node
                free(current->name);  //free name memory
                free(current);//free the node
                current = head;//go to the next node
            } else {
                temp = current; //store current node for temp
                prev->next = current->next;//update prev to next
                current = current->next;// go to the next node
                free(temp->name);  
                free(temp);
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

