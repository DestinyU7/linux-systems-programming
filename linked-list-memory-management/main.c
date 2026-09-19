//
// adapted from http://www.cprogramming.com/snippets/source-code/singly-linked-list-insert-remove-add-count
//

#include "mp3.h"
#define  BUFFERSIZE 128

node_t *head;

void insert(char *name, int data);
void print();
void freeList();

int main()
{
  int i, num, len;
  struct node *n;
  char buffer[BUFFERSIZE], c; //buffer for name and song
  char artist[BUFFERSIZE], song[BUFFERSIZE];  // Add this line

  head = NULL;

  while (1) {
    printf("\nList Operations\n");
    printf("===============\n");
    printf("(1) Insert\n");
    printf("(2) Display\n");
    printf("(3) Delete\n");
    printf("(4) Exit\n");
    printf("(5) Reverse\n");
    printf("Enter your choice : ");
    if (scanf("%d%c", &i, &c) <= 0) {          // use c to capture \n
        printf("Enter only an integer...\n");
        exit(0);
    } else {
        switch(i)
        {
case 1: 
        printf("Enter the artist name: ");
        if (fgets(artist, BUFFERSIZE, stdin) != NULL) {
            len = strlen(artist);
            artist[len - 1] = '\0';   // override \n to become \0
        } else {
            printf("Invalid artist name...\n");
            exit(-1);
        }
        
        printf("Enter the song name: ");
        if (fgets(song, BUFFERSIZE, stdin) != NULL) //get the song name
         {
            len = strlen(song);
            song[len - 1] = '\0';   // override \n to become \0
        } else {
            printf("Invalid song name...\n");
            exit(-1);
        }
        
        printf("Enter the duration to insert: ");
        scanf("%d%c", &num, &c);  // use c to capture \n
        
        snprintf(buffer, BUFFERSIZE, "%s - %s", artist, song); //format the name
        printf("[%s] [%d]\n", buffer, num);
        insert(buffer, num); //insert into the list
        break;
        case 2: if (head == NULL) //if the list is empty
                  printf("List is Empty\n");
                else
                  print();
                break;

//delete the artist
case 3: 
    printf("Enter the artist name to delete: "); //get the artist name
    if (fgets(artist, BUFFERSIZE, stdin) != NULL) {
        len = strlen(artist);
        if (len > 0 && artist[len - 1] == '\n') {//if the artist name is not empty
            artist[len - 1] = '\0';
        }
        delete_artist(artist);//calls the delete function in my add.c
        printf("All songs by %s have been deleted.\n", artist);
    } else {
        printf("Invalid artist name...\n");
    }
    break;


        case 4: freeList();//this just the memory resulting in the program exiting
                return 0;
        case 5:  // calls the reverse function in my add.c
            reverse();//to save space i just called the function in the main, reverse is in add.c
            printf("List reversed.\n");
            break;
                
        default: printf("Invalid option\n");
        }
    }
  }
  return 0;
}
