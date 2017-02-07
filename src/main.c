/*!
   \file main.c
   \brief Entry point of program
   \author Aksels Ledins
   \date 16/04/2016
*/

#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <ctype.h>

#include "logic.h"
#include "map.h"

/*!
   \brief Display help
   \param argv argv from main
*/
void help(char **argv)
{
  printf("\
usage: %s [options]\n\
  options:\n\
    -h,  display this help\n\
    -i int,  interations\n\
    -d int,  delay (microseconds)\n\
    -m path_to_map, to specify the map's path\n\
\
  \n", argv[0]);
}

/*!
   \brief This functions parse the cmdline arguments
   \param argc argc from main
   \param argv argv from main
   \param i iterations
   \param d delay in microseconds
   \return filepath
*/
char * parseArgv(int argc, char **argv, int *i, int *d)
{
  char *mvalue;
  int c;

  /* default path */
  mvalue = "./maps/base.map";
  while ((c = getopt (argc, argv, "i:d:hm:")) != -1)
    switch (c)
      {
      case 'm':
        mvalue = optarg;
        break;
      case 'i':
        *i = atoi(optarg);
        break;
      case 'd':
        *d = atoi(optarg);
        break;
      case 'h':
        help(argv);
        exit(0);
        break;
      case '?':
        if (optopt == 'm')
          return NULL;
      default:
        return NULL;
      }

  return mvalue;
}

/*!
   \brief Entry point of the program
   \return 0 on success, 1 on error
*/
int main(int argc, char **argv) {

  int iter, delay;
  char *path;

  iter = 100;
  delay = 100000;
  path = parseArgv(argc, argv, &iter, &delay);
  if (!path) return 1;

  t_map map;

  if (mapParse(path, &map) == 0)
  {
    if (checkMapIntegrity(&map) == 1) {
      mapFree(&map);
      return 1;
    }
    initscr();
    noecho();

    for (int i = 0; i < iter; i++) {


      logic   ( &map );
      mapPrint( &map );
      usleep(delay);

      refresh();
      erase();

    }
    mapFree(&map);
    endwin();
  }

  return 0;
}
