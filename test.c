#include <stdlib.h>
#include <stdio.h>

#include "unitary_typed.c"

int
main
()
{
	struct list *numbers = list_create( sizeof( int ) );

	printf( "Created list [numbers], whose elements size is: %d\n\n", numbers->element_size );

	int *element = list_element_create( numbers, 1 );

	*element = 426;

	printf( "Defined element 1: %d\n", *element );

	element = list_element_create( numbers, 2 );

	*element = 29;

	printf( "Defined element 2: %d\n", *element );

	printf( "\nElements in list [numbers]:\nElement 1: %d\nElement 2: %d\n", *(int*)list_element_get( numbers, 1 ), *(int*)list_element_get( numbers, 2 ));

	printf("\n\n");

	struct list *characters = list_create( sizeof( char ) );

	printf( "Created list [ascii], whose elements size is: %d\n\n", characters->element_size );

	element = list_element_create( characters, 1 );

	*element = 'm';

	printf( "Defined element 1: %c\n", *element );

	element = list_element_create( characters, 2 );

	*element = 'a';

	printf( "Defined element 2: %c\n", *element );

	printf( "\nElements in list [characters]:\nElement 1: %c\nElement 2: %c\n", *(char*)list_element_get( characters, 1 ), *(char*)list_element_get( characters, 2 ));

	return 0;
}

