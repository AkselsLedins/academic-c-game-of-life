/*!
   \file logic.c
   \brief Handle the logic of Conway's algorithm
   \author Aksels Ledins
   \date 16/04/2016
*/

#include "map.h"
#include "logic.h"

/*!
   \brief This functions checks the cell at y/x pos
   \param m t_map structure
   \param y int y position
   \param x int x position
   \return return 1 if a cell is here, 0 if not
*/
int cellAt(t_map *m, int y, int x) {
  if (x > 0         &&
      y > 0         &&
      y < m->sizeY  &&
      x < m->sizeX  &&
      m->data[y][x] == CELL )
    return 1;
  return 0;
}

/*!
   \brief Decides if a cell should be dead, created or left alive.
   \param m map structure
   \param x int x coordinate
   \param y int y coordinate
*/
void fateOfTheCell(t_map *m, int x, int y)
{
  /* number of cells around */
  short n;
  /* type of the cell */
  char t;

  n = 0;
  t = m->data[y][x];

  // not a wall
  if (t == WALL) return;

  // check sides
  n += cellAt( m, y  , x-1 );
  n += cellAt( m, y  , x+1 );
  n += cellAt( m, y+1, x   );
  n += cellAt( m, y-1, x   );
  // check diagonals
  n += cellAt( m, y+1, x-1 );
  n += cellAt( m, y+1, x+1 );
  n += cellAt( m, y-1, x-1 );
  n += cellAt( m, y-1, x+1 );

  if (t == CELL) {
    if (n < 2)        m->nextState[y][x] = NONE;
    else if ( n > 3)  m->nextState[y][x] = NONE;
    else              m->nextState[y][x] = CELL;
  }
  else if (t == NONE && n == 3)
    m->nextState[y][x] = CELL;
  }

/*!
   \brief Recursively reads the map structure
   \param m map structure
   \param ox x offset
   \param oy y offset
*/
void recursiveRead(t_map * m, int ox, int oy)
{
  /* recursion */
  if (ox < m->sizeX)
    recursiveRead( m, ox+1, oy );
  else if (oy < m->sizeY)
    recursiveRead( m, 0, oy+1 );

  /* decide the cell's fate */
  fateOfTheCell(m, ox, oy);
}

/*!
   \brief Container for logic functions
   \param m map structure
*/
void logic(t_map * m)
{
  char**  tmp;

  // switch ptrs
  tmp = m->data;

  recursiveRead( m, 0 , 0);

  m->data = m->nextState;
  m->nextState = tmp;
  for (int l = 0; m->nextState[l]; l++)
  {
    for (int x = 0; m->nextState[l][x]; x++)
    {
      if ( m->nextState[l][x] != WALL && m->nextState[l][x] != 0  )
        m->nextState[l][x] = NONE;
    }
  }
}
