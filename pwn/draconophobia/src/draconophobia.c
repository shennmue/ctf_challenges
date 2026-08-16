
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_ATTACK_POINTS 20
#define MAX_NAME_LENGTH 8
  
char flag[64];

struct stat *player1, *player2;
struct stat {
  int attack_points;
  char *id;
};

void lvl_up()
{
  rand();
  FILE *flag_file = fopen("flag.txt", "r");
  char flag_buf[64];
  fgets(flag_buf, sizeof(flag_buf), flag_file);
  strcpy(flag, flag_buf);
  printf("You manage to defeat the dragon and level up !\n%s\n",flag_buf);
}

void fighting_dragon() {
    printf("The fight is tough but you will die immolated by the dragon's flames.\n");
}

int main()
{
  player1 = malloc(sizeof(struct stat));
  player1->attack_points = DEFAULT_ATTACK_POINTS;
  player1->id = malloc(MAX_NAME_LENGTH);

  player2 = malloc(sizeof(struct stat));
  player2->attack_points = DEFAULT_ATTACK_POINTS;
  player2->id = malloc(MAX_NAME_LENGTH);
  printf("Hey adventurers, you are going to fight the dragon! Good luck..\n\n");
  printf("First player name : ");
  fflush(stdout);
  scanf("%s", player1->id);

  printf("Second player name : ");
  fflush(stdout);
  scanf("%s", player2->id);

  if(strcmp(player1->id,player2->id) == 0) {
      printf("\nPlease use differents names.\n");
      printf("[CTRL D] to exit the programe\n");

      exit(EXIT_FAILURE);
  }
  fighting_dragon();
  printf("\n[CTRL D] to exit the programe\n");
  return 0;
}
