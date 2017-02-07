/*!
   \file map.c
   \brief Map handling functions
   \author Aksels Ledins
   \date 16/04/2016
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "map.h"

/*!
   \brief Check if the map is ok.
   \param map map structure
   \return 0 on success 1 on failure
*/
int checkMapIntegrity(t_map * map)
{
  char c;
  size_t lineSize;

  if (!map || !map->data || !map->data[0])
    return 1;

  lineSize = strlen(map->data[0]);
  for (int n = 0; map->data[n] ; n++ )
  {
    if ( lineSize !=  strlen(map->data[n]) ) {
      fprintf(stderr, "[map error] inconsistent line size\n");
      return 1;
    }

    for (int i = 0; map->data[n][i] ; i++)
    {
        c = map->data[n][i];
        if (c != CELL && c != NONE && c != WALL && c != 0) {
          fprintf(stderr, "[map error] invalid caracter (%c) at %d/%d\n", c,n,i);
          return 1;
        }
    }
  }

  return 0;
}

/*!
   \brief This function parses a map and stores it.
   \param path path to the map
   \param map pointer to map structure
   \return Returns 0 on success, 1 on error.
*/
int mapParse(char * path, t_map * map)
{
  int ret;
  char str[999];
  int sizeY = 0;
  FILE * file;

  ret = 0;
  memset(str, 0, 999);
  map->data = NULL;
  map->nextState = NULL;

  file = fopen( path , "r" );
  if (file) {
    while ( fscanf(file, "%s", str) != EOF ) {

      map->data = (char **) realloc(map->data, (sizeY+1) * sizeof(char**) );
      map->nextState = (char **) realloc(map->nextState, (sizeY+1) * sizeof(char**) );

      map->data[sizeY] = strdup(str);
      map->nextState[sizeY] = strdup(str);

      memset(str, 0, 999);
      sizeY++;
    }

    map->data = (char **) realloc(map->data, (sizeY+1) * sizeof(char**) );
    map->data[sizeY] = NULL;

    map->nextState = (char **) realloc(map->nextState, (sizeY+1) * sizeof(char**) );
    map->nextState[sizeY] = NULL;

  }
  else {
    fprintf(stderr, "[error] Can't open map : %s\n", path);
    return 1;
  }

  map->sizeY = sizeY - 1;
  if (map->data && map->data[0])
    map->sizeX = strlen(map->data[0]);
  else {
    ret = 1;
    fprintf(stderr, "[error] empty file\n");
  }
  fclose(file);
  return ret;
}

/*!
   \brief This function outputs the map to the terminal
   \param map map structure
*/
void mapPrint(t_map * map)
{
  for (int n = 0; n <= map->sizeY; n++)
  {
    for (int i = 0; i < map->sizeX; i++)
    {
      switch ( map->data[n][i] ) {
        case WALL:
          addch( ACS_CKBOARD );
          break;
        case CELL:
          addch( ACS_DIAMOND );
          break;
        default:
          printw(" ");
          break;
      }
    }
    printw("\n");
  }

}

/*!
   \brief This function frees the map structure entirely.
   \param map map structure
*/
void mapFree(t_map * map)
{
  /* free very line */
  for (int n = 0; map->data[n]; n++)
    free( map->data[n] );
  for (int n = 0; map->nextState[n]; n++)
    free( map->nextState[n] );

  /* free array */
  free( map->data );
  free( map->nextState );
  /* put ptr to null to be sure that's it won't be used after */
  map->data = NULL;
}
