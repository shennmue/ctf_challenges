#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h> 
#include <time.h>
#include "draw.h" 

WINDOW *win;
#define BUFFSIZE 1024

int maze[5];  
int handle_direction(int *previous, int width, bool is_retry);
void end_proc();
void ncurse_init(int height, int width, int starty, int startx);
void ncurse_refresh();
void ncurse_delete();
void ncurse_set(int previous, int width);
void clear_all(int height, int width);
int random_choice(int i);
void press_enter(int previous, int width);

int main() {
    srand(time(NULL));
    int height = 45;
    int width = 130;
    int starty = 0;
    int startx = 0;

    ncurse_init(height,width,starty,startx);
  
    char space = ' ';
    int previous = 0;  
    mvwprintw(win,previous,width/2 - (strlen("aaMagic Mazeaa")/2),"%c%c%s%c%c",space,space,"Magic Maze",space,space);
    wrefresh(win); 
    
    char *wiz = strdup(wizard);
    char *line = strtok(wiz, "\n");

    while(line != NULL) {
        mvwprintw(win,previous + 1,width/2 - 13,"%s", line);
        previous +=1;
        line = strtok(NULL, "\n");
    }
    previous += 2;
    free(wiz);
    wrefresh(win);

    mvwprintw(win,previous,width/2 - (strlen(dial1)/2),"%s",dial1);
    wrefresh(win);
    
    char *door_copy = strdup(door);
    line = strtok(door_copy, "\n");

    while (line != NULL) {
        mvwprintw(win, previous + 3, width/2 - 34, "%s", line);
        previous += 1;
        line = strtok(NULL, "\n");
    }

    previous += 2;
    free(door_copy);
    wrefresh(win);
    mvwprintw(win,previous+3,width/2 - (strlen(dialx)/2),"%s",dialx);
    wrefresh(win);
    flushinp();
    char c = getch();

    if(c != '\n' && c != '\r') {
        clear_all(height, width);
    }

    ncurse_refresh();
    win = newwin(height, width, starty, startx); 
    box(win, 0, 0);
    wrefresh(win);
    previous = 0;
    mvwprintw(win,previous,width/2 - (strlen("aaMazeaa")/2),"%c%c%s%c%c",space,space,"Maze",space,space);
    wrefresh(win); 
    previous +=4;
    mvwprintw(win,previous,width/2 - (strlen(dial2)/2),"%s",dial2);
    wrefresh(win); 
    previous +=2;
    mvwprintw(win,previous,width/2 - (strlen(dial2)/2),"%s",dial3);
    wrefresh(win); 
    previous+=1;
    mvwprintw(win,previous,width/2 - (strlen(dial2)/2) + 12,"%s",dial4);
    wrefresh(win); 
    previous += 4;

    bool success = handle_direction(&previous, width, false);

    wrefresh(win);
    mvwprintw(win,previous+3,width/2 - (strlen(dialx)/2),"%s",dialx);
    wrefresh(win);
    flushinp();
    c = getch();

    if(c != '\n' && c != '\r') {
        clear_all(height, width);
    }
  
    if(success) {
        goto end;
    }

    ncurse_refresh();
    win = newwin(height, width, starty, startx); 
    box(win, 0, 0);
    wrefresh(win);
    previous = 0;
    mvwprintw(win,previous,width/2 - (strlen("aaMagic Mazeaa")/2),"%c%c%s%c%c",space,space,"Magic Maze",space,space);
    wrefresh(win); 
    previous +=4;
    mvwprintw(win,previous,width/2 - (strlen(dial5)/2),"%s",dial5);
    wrefresh(win); 
    previous += 2;
    mvwprintw(win,previous,width/2 - (strlen(dial6)/2),"%s",dial6);
    wrefresh(win); 
    previous += 1;
    mvwprintw(win,previous,width/2 - (strlen(dial6)/2) + 11,"%s",dial7);
    wrefresh(win); 
    previous += 4;
    
    success = handle_direction(&previous, width, true);
    if(!success) { 
        press_enter(previous,width);
        ncurse_refresh();
        win = newwin(height, width, starty, startx); 
        box(win, 0, 0);
        wrefresh(win);
        previous = 0;
        mvwprintw(win,previous,width/2 - (strlen("aaMagic Mazeaa")/2),"%c%c%s%c%c",space,space,"Magic Maze",space,space);
        wrefresh(win); 
        previous +=4;
        char *game_over_end = strdup(game_over);
        line = strtok(game_over_end, "\n");
        while(line != NULL) {
            mvwprintw(win,previous + 1,width/2 - 33,"%s", line);
            previous +=1;
            line = strtok(NULL, "\n");
        }
        previous += 2;
        free(game_over_end);
        wrefresh(win);
    }
    
    end :
    if (success) {
        press_enter(previous,width);
        ncurse_refresh();
        win = newwin(height, width, starty, startx); 
        box(win, 0, 0);
        wrefresh(win);
        previous = 0;
        mvwprintw(win,previous,width/2 - (strlen("aaMagic Mazeaa")/2),"%c%c%s%c%c",space,space,"Magic Maze",space,space);
        wrefresh(win); 
        previous +=4;
        mvwprintw(win, previous + 3, width/2 - strlen(final_dial)/2, "%s", final_dial);
        wrefresh(win);
        previous += 3;
        FILE *FLAG = fopen("flag.txt", "r");
        char flag[BUFFSIZE];
        if (FLAG) {
            fscanf(FLAG,"%s", flag);
            fclose(FLAG);
            mvwprintw(win, previous + 2,width/2 - strlen(flag)/2,"%s", flag);
        } else {
             mvwprintw(win, previous + 2,width/2 - 10,"Flag introuvable");
        }
        wrefresh(win);

        previous +=3;
        char *chess_end = strdup(chess);
        char *line = strtok(chess_end, "\n");
        while(line != NULL) {
            mvwprintw(win,previous + 1,width/2 - 40,"%s", line);
            previous +=1;
            line = strtok(NULL, "\n");
        }
        previous += 2;
        free(chess_end);
        wrefresh(win);
    }
    end_proc();
    return 0;
}

void press_enter(int previous, int width) {
    mvwprintw(win,previous+3,width/2 - (strlen(dialx)/2),"%s",dialx);
    wrefresh(win);
    getch();
}
void end_proc() {
    fflush(stdout);
    getch();
    fflush(stdout);
    delwin(win);
    endwin();
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);  
    return;
}

void ncurse_set(int previous, int width) {
    curs_set(1);
    wmove(win, previous, width/2 - (strlen(dial2)/2));
    wrefresh(win);
}

void ncurse_refresh() {
    delwin(win);
    clear();
    refresh();
}

int random_choice(int i) {
    int r = rand() % 4;
    maze[i] = r;
    return r;
}

int handle_direction(int *previous, int width, bool is_retry) {
    char *choices[4] = {"forward", "backward", "left", "right"};
    bool success = true;
    char input[256];
    keypad(win, TRUE);
    
    for(int i = 0; i < 5; ++i) {
        char direction[BUFFSIZE];
        int r;
        if (!is_retry) {
            r = random_choice(i); 
        } else {
            r = maze[i]; 
        }
       
        strcpy(direction, choices[r]);
        

        ncurse_set(*previous, width);

        flushinp(); 
        int user_choice = wgetch(win);       
    
        switch(user_choice) {
            case KEY_DOWN :
                mvwprintw(win, *previous, width/2 - (21/2), "Direction (%d) : BACKWARD", i+1);
                wrefresh(win);
                if(strcmp("backward", direction) != 0) {
                    success = false;
                }
                break;
            case KEY_LEFT :
                mvwprintw(win, *previous, width/2 - (21/2), "Direction (%d) : LEFT", i+1);
                wrefresh(win); 
                if(strcmp("left", direction) != 0) {
                    success = false;
                }
                break;
            case KEY_RIGHT :
                mvwprintw(win, *previous, width/2 - (21/2), "Direction (%d) : RIGHT", i+1);
                wrefresh(win); 
                if(strcmp("right", direction) != 0) {
                    success = false;
                }
                break;
            case KEY_UP :
                mvwprintw(win, *previous, width/2 - (21/2), "Direction (%d) : FORWARD", i+1);
                wrefresh(win); 
                if(strcmp("forward", direction) != 0) {
                    success = false;
                }
                break;
            default :
                success = false;
                ungetch(user_choice);
                getnstr(input, sizeof(input)-1);
                
                mvwprintw(win, *previous, width/2 - strlen(input)/2, input);
                mvwprintw(win, *previous + 1, width/2 - strlen("Gan d'Alf: I don't know that direction... but so be it")/2, "Gan d'Alf: I don't know that direction... but so be it");                      
                *previous += 1;
                wrefresh(win); 
                break;
        }
        wrefresh(win);
        curs_set(0);
        *previous += 4;
    }
    return success;
}

void ncurse_init(int height, int width, int starty, int startx) {
    initscr();
    resizeterm(50, 150); 
    noecho();    
    curs_set(0);           

    refresh();
    win = newwin(height, width, starty, startx);
    
    if (win == NULL) {
        endwin();
        fprintf(stderr, "Erreur: Impossible de creer la fenetre ncurses.\n");
        exit(1); 
    }
    box(win, 0, 0);
}

void ncurse_delete() {
    napms(1500);
    clear();
    delwin(win);
    endwin();
}

void clear_all(int height, int width) {
    wclear(win);
    box(win, 0, 0);
    mvwprintw(win, height/2, width/2 - (strlen(err_msg)/2), "%s", err_msg);
    wrefresh(win);
    ncurse_delete();
    exit(0);
}
