#ifndef MAPPARSER_H__

# define MAPPARSER_H__

#define CELL '@'
#define WALL '#'
#define NONE '.'

/* Map structure */
typedef struct s_map
{
  // SIZE
  int sizeX;
  int sizeY;

  /* DATA of the map */
  char ** data;
  char ** nextState;
} t_map;

/* function declarations */
void mapFree          ( t_map * );
void mapPrint         ( t_map * );
int checkMapIntegrity ( t_map * );
int mapParse          (char*, t_map *);

#endif // EOF ! MAPPARSER_H__
