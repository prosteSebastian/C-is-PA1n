#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

int timer;

typedef struct {
  char m_Spz[11];
  int m_Full;
  int m_Time;
} TCar;

//for debugging
void chyba ( int i ) {
  printf("chyba %i\n", i);
}

//for debugging - print each lot in a floor
void printLot ( TCar * ar, int sz ) {
  for ( int i = 0 ; i < sz ; ++i ) {
    if ( ar[i].m_Full == 0 )
      printf ("      EMPTY");
    else
      printf ("%11s", ar[i].m_Spz);
  }
}

//for debugging - print each time in each lot
void printTime ( TCar * ar, int sz ) {
  for ( int i = 0 ; i < sz ; ++i )
    printf ("%11i", ar[i].m_Time);
}

//for debugging - print the whole parking lot 
void printParkLot ( TCar ** ar, int fl, int sz ) {
  printf("        ");
  for ( int j = 0 ; j < sz ; ++j )
    printf ("%11i", j + 1 );
  printf ("\n");

  for ( int i = 0 ; i < fl ; ++i ) {
    printf ("Floor %c:", (i+'A'));
    printLot ( ar[i], sz );
    printf ("\n");
    printf ("Time   :");
    printTime ( ar[i], sz );
    printf ("\n");
  }
}

void inicializeFloor ( TCar * ar, int sz ) {
  for ( int i = 0 ; i < sz ; ++i ) {
    ar[i].m_Full = 0;
    ar[i].m_Time = 0;
  }
}

//return 0, if invalid inputs
//return number of floors, if valid inputs  
int getParkLot ( int * size ) {
  char cFloor;
  int floor;
  printf("Velikost:\n");
  if ( scanf ( " %c %i", &cFloor, size ) != 2 )
    return 0;
  
  if ( *size <= 0 ) return 0;
  if ( cFloor < 'A' || cFloor > 'Z' ) return 0;

  floor = cFloor + 1 - 'A';
  return floor;
}

TCar ** buildParkLots ( TCar ** ar, int fl, int sz ) {
  ar = (TCar**) malloc ( sizeof (*ar) * fl );
  for ( int i = 0 ; i < fl ; ++i ) {
    ar[i] = (TCar*) malloc ( sizeof (**ar) * sz );
    inicializeFloor ( ar[i], sz );
  }
  return ar;
}

//return 0, if invalid inputs
//return 1, if add car
//return 2, if remove car
//return EOF, if EOF
int getCar ( TCar * tmp ) {
  char cmd;
  int input = scanf ( " %c", &cmd );
  
  if ( input == EOF ) return EOF;
  if ( input != 1 ) return 0;    
  if ( cmd != '+' && cmd != '-' ) return 0;

  input = scanf ( " %10s", tmp->m_Spz );
  if ( input == 1 ) {
    if ( cmd == '+' ) return 1;
    if ( cmd == '-' ) return 2;
  }
  else return 0;

  return 0;
}

//return 1, if the car is found
//return 0, if not found
int foundInFloor ( TCar * ar, int sz, int * place ) {
  for ( int j = 0 ; j < sz ; ++j ) {
    if ( ar[j].m_Full == 0 ) {
      *place = j;
      ar[j].m_Full = 1;
      return 1;
    }
  }
  return 0;
}

//return 1, if place is not empty
//return 0, if place is empty
int EmptyPlace ( TCar ** ar, int fl, int sz, 
                 int * floor, int * place ) {
  for ( int i = 0 ; i < fl ; ++i ) {
    if ( foundInFloor ( ar[i], sz, place ) ) {
      *floor = i;
      return 1;
    }
  }
  return 0;
}

void parkCar ( TCar ** ar, TCar car, int fl, int pl ) {
  strcpy ( (ar[fl][pl]).m_Spz, car.m_Spz );
  ar[fl][pl].m_Time = timer;
  printf ("Pozice: %c%i\n", fl + 'A', pl + 1);
}

void oldestPosition ( TCar ** ar, int fl, int sz, 
                     int * floor, int * place ) {
  int oldestTime = timer;
  for ( int i = 0 ; i < fl ; ++i )
    for ( int j = 0 ; j < sz ; ++j )
      if ( ar[i][j].m_Time < oldestTime ) {
        oldestTime = ar[i][j].m_Time;
        *floor = i; *place = j;
      }
}

void rmOld ( TCar ** ar, int fl, int sz, 
                    int * floor, int * place ) {
  oldestPosition ( ar, fl, sz, floor, place );

  printf ("Odtah vozu %s z pozice %c%i\n", ar[*floor][*place].m_Spz
                                         , (*floor) + 'A'
                                         , (*place) + 1 );

}

void pushToLot ( TCar ** ar, TCar car, int fl, int sz ) {
  printf ("%s\n", car.m_Spz);
  int floor = 0, place = 0;
  if ( EmptyPlace ( ar, fl, sz, &floor, &place ) ) {
    parkCar ( ar, car, floor, place );
  }
  else {
    rmOld ( ar, fl, sz, &floor, &place );
    parkCar ( ar, car, floor, place );
  }
}

//return 1, if car is found
//return 0, if not
int foundCarInFloor ( TCar ** ar, TCar car, int sz, 
                      int fl, int * pl ) {
  for ( int i = 0 ; i < sz ; ++i ) 
    if ( strcmp ( ar[fl][i].m_Spz, car.m_Spz ) == 0 ) {
      *pl = i;
      return 1;
    }
  return 0;
}

//return 1, if car is found
//return 0, if not
int foundCar ( TCar ** ar, TCar car, int fl, 
               int sz, int * floor, int * place ) {
  for ( int i = 0 ; i < fl ; ++i ) {
    if ( foundCarInFloor ( ar, car, sz, i, place ) ) {
      *floor = i;
      return 1;
    }
  }
  return 0;
}

void rmFromLot ( TCar ** ar, TCar car, int fl, int sz ) {
  int floor = 0, place = 0;

  if ( !foundCar ( ar, car, fl, sz, &floor, &place ) ) {
    printf ("%s\n", car.m_Spz);
    printf ("Nenalezeno\n");
  } 
  else {
    ar[floor][place].m_Full = 0;
    printf ("%s\n", car.m_Spz);
    printf ("Pozice: %c%i\n", floor + 'A', place + 1);
  }
}

void delArr ( TCar ** ar, int fl, int sz ) {
  for ( int i = 0 ; i < fl ; ++i )
    free ( *(ar+i) );
  free ( ar );
}

int main ( void ) {
  int floor, size = 0, control;

  floor = getParkLot ( &size );
  if ( !floor ) {
    printf("Nespravny vstup.\n");
    return 1;
  }

  TCar ** parkLots = NULL;
  parkLots = buildParkLots ( parkLots, floor, size );

  printf ("Pozadavky:\n");

  while ( 1 ) {
    TCar tmp = {};
    control = getCar ( &tmp );
    if ( control == EOF )
      break;
    else if ( control == 1 ) {
      timer++;
      pushToLot ( parkLots, tmp, floor, size );
    }
    else if ( control == 2 ) {
      rmFromLot ( parkLots, tmp, floor, size );
    }
    else {
      delArr ( parkLots, floor, size );
      printf("Nespravny vstup.\n");
      return 1;
    }
  }
  printParkLot ( parkLots, floor, size );
  delArr ( parkLots, floor, size );
  return 0;
}