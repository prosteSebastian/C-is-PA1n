#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
	struct TItem * m_Next;
	char           m_Digit;
} TITEM;

TITEM * createItem ( char digit, TITEM * next )
{
	TITEM * n = (TITEM *) malloc (sizeof ( *n ));
	n -> m_Digit = digit;
	n -> m_Next = next;
	return n;
}

void deleteList (TITEM * l)
{
	while (l)
	{
		TITEM * tmp = l -> m_Next;
		free (l);
		l = tmp;
	}
}
#endif /* __PROGTEST__ */
int validLinkedList (TITEM * list) {
    if (!list) return 0;
    while (list) {
        if (isdigit(list->m_Digit)) {
            list = list->m_Next;
        } else {
            return 0;
        }
    }
    return 1;
}
int getListLength (TITEM * list) {
    int zeroCounter = 0;
    int length = 0;
    while (list) {
        if (list->m_Digit == '0') {
            zeroCounter++;
        } else {
            zeroCounter = 0;
        }
        length++;
        list = list->m_Next;
    }
    return (length - zeroCounter-1);
}
void printList (TITEM *x) {
	while (x) {
		printf("%c", x->m_Digit);
		x = x->m_Next;
	}
}
TITEM * maxOf (TITEM ** x, int nr) {
    for (int i = 0; i < nr; i++) {
        if (!validLinkedList(x[i])) {
            return NULL;
        }
    }
    TITEM * max = x[0];
	int lengthMax = getListLength(max);
	for (int i = 1; i < nr; i++) {
		TITEM * current = x[i];
		int lengthCurr = getListLength(current);
		if (lengthMax > lengthCurr) {
			continue;
		} else if (lengthMax < lengthCurr) {
			lengthMax = lengthCurr;
			max = current;
		} else {
			int isBigger = 0;
			TITEM * maxCycle = max;
			TITEM * currentCycle = current;
			for (int i = 0; i < lengthCurr; i++) {
				if (currentCycle->m_Digit > maxCycle->m_Digit) {
					isBigger = 1;
				} else if (currentCycle->m_Digit < maxCycle->m_Digit) {				
					isBigger = 0;
				}
				currentCycle = currentCycle->m_Next;
				maxCycle = maxCycle->m_Next;
			}
			if (isBigger) {
				max = current;
				lengthMax = lengthCurr;
			}
		}
	}
	
    return max;
}
#ifndef __PROGTEST__
int main (int argc, char * argv [])
{
	TITEM * a[5];

	a[0] = createItem ( '4',
						createItem ( '3',
									 createItem ( '2',
												  createItem ( '1', NULL ))));
	a[1] = createItem ( '2',
						createItem ( '3',
									 createItem ( '4',
												  createItem ( '5', NULL))));
	
											  
	assert ( maxOf ( a, 2 ) == a[1] );
	deleteList( a[0] );
	deleteList( a[1] );

	a[0] = createItem ( '0',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '1', NULL ))));
	a[1] = createItem ( '2',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '1', NULL ))));
	a[2] = createItem ( '1',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '1', NULL))));
	a[3] = createItem ( '2',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '1',
															   createItem ( '0',
																			createItem ( '0', NULL ))))));
	assert ( maxOf ( a, 4 ) == a[1] );
	deleteList ( a[0] );
	deleteList ( a[1] );
	deleteList ( a[2] );
	deleteList ( a[3] );

	a[0] = createItem ( '1',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '0',
															   createItem ( '0',
																			createItem ( '0', NULL ))))));
	a[1] = createItem ( '0',
						createItem ( '0',
									 createItem ( '1', NULL )));
	a[2] = createItem ( '1',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '0',
															   createItem ( '0',
																			createItem ( '9', NULL ))))));
	a[3] = createItem ( '0',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '0',
															   createItem ( '0',
																			createItem ( '0',
																						 createItem ( '0',
																									  createItem ( '0',
																												   createItem ( '0',
																																createItem ( '0',
																																			 createItem ( '0',
																																						  createItem ( '0',
																																									   createItem ( '0',
																																													createItem ( '0',
																																																 createItem ( '0', NULL )))))))))))))));
	assert ( maxOf (a, 4) == a[2] );
	deleteList ( a[0] );
	deleteList ( a[1] );
	deleteList ( a[2] );
	deleteList ( a[3] );

	a[0] = createItem ( '0',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '0',
															   createItem ( '0',
																			createItem ( '0',
																						 createItem ( '0',
																									  createItem ( '0',
																												   createItem ( '0',
																																createItem ( '0',
																																			 createItem ( '0',
																																						  createItem ( '0',
																																									   createItem ( '0',
																																													createItem ( '0',
																																																 createItem ( '0',
																																																			  createItem ( '0',
																																																						   createItem ( '0',
																																																										createItem ( '0',
																																																													 createItem ( '0',
																																																																  createItem ( '0',
																																																																			   createItem ( '0',
																																																																							createItem ( '1', NULL ))))))))))))))))))))));
	a[1] = createItem ( '1',
						createItem ( '0',
									 createItem ( '0',
												  createItem ( '0',
															   createItem ( '0',
																			createItem ( '0',
																						 createItem ( '0',
																									  createItem ( '0',
																												   createItem ( '0',
																																createItem ( '0',
																																			 createItem ( '0',
																																						  createItem ( '0',
																																									   createItem ( '0',
																																													createItem ( '0',
																																																 createItem ( '0',
																																																			  createItem ( '0',
																																																						   createItem ( '0',
																																																										createItem ( '0',
																																																													 createItem ( '0',
																																																																  createItem ( '0',
																																																																			   createItem ( '0',
																																																																							createItem ( '1', NULL ))))))))))))))))))))));
	assert ( maxOf ( a, 2 ) == a[1] );
	deleteList ( a[0] );
	deleteList ( a[1] );

	a[0] = createItem ( '3',
						createItem ( '2',
									 createItem ( '1', NULL )));
	a[1] = createItem ( '6',
						createItem ( '5',
									 createItem ( '4', NULL )));
	a[2] = createItem ( '9',
						createItem ( 'c',
									 createItem ( 'b',
												  createItem ( '9',
															   createItem ( '9', NULL )))));
	assert ( maxOf ( a, 3 ) == NULL);
	deleteList ( a[0] );
	deleteList ( a[1] );
	deleteList ( a[2] );

	return 0;
}
#endif /* __PROGTEST__ */