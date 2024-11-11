#include <stdlib.h>

#include <string.h>

#include "unitary_typed.h"

void**
list_node_get_field_previous
( void* node )
{
	return ( void** )( node + 0 );
}

void**
list_node_get_field_next
( void* node )
{
	return ( void** )( node + sizeof( void* ) );
}

void*
list_node_get_content
( void* node )
{
	return ( node + ( 2 * sizeof( void* ) ) );
}

void
list_node_connect
( void* node_1, void* node_2 )
{
	void **field;

	if ( node_1 != NULL )
	{
		field = list_node_get_field_next( node_1 );

		*field = node_2;
	}

	if ( node_2 != NULL )
	{
		field = list_node_get_field_previous( node_2 );

		*field = node_1;
	}

	return;
}

size_t
list_get_node_size
( struct list *list )
{
	return ( ( 2 * sizeof( void* ) ) + list->element_size );
}

struct list*
list_create
( size_t size )
{
	struct list *list = malloc( sizeof( struct list ) );

	list->element_size = size;

	list->first_node = NULL;

	return list;
}

void
list_destroy
( struct list *list )
{
	void *nodes[] = { NULL, list->first_node };

	while ( nodes[1] != NULL )
	{
		nodes[0] = nodes[1];

		nodes[1] = *list_node_get_field_next( nodes[0] );

		free( nodes[0] );
	}

	free( list );

	return;
}

struct list*
list_merge
( struct list *list1, struct list *list2, int position )
{
	if ( list1 == NULL )
	{
		printf("Error on function [list_merge]. List to which will be merged is NULL.\n");

		return NULL;
	}

	if ( list2 == NULL )
	{
		printf("Error on function [list_merge]. List that will be merged is NULL.\n");

		return NULL;
	}

	if ( list1->element_size != list2->element_size )
	{
		printf("Error on function [list_merge]. Lists do not have the same element size.\n");

		return NULL;
	}

	void *node = list1->first_node;

	int current_position = 1;

	while ( current_position < position && node != NULL )
	{
		node = *list_node_get_field_next( node );

		current_position++;
	}

	if ( node == NULL )
	{
		return NULL;
	}

	void *neighbours[2] = { node, *list_node_get_field_next( node ) };

	list_node_connect( neighbours[0], list2->first_node );

	list_node_connect( list2->last_node, neighbours[1] );

	return list1;
}

unsigned int
list_get_length
( struct list *list )
{
	unsigned int length = 0;

	void *node = list->first_node;

	while ( node != NULL )
	{
		node = *list_node_get_field_next( node );

		length++;
	}

	return length;
}

void*
list_element_create
( struct list *list, int position )
{
	void *nodes[3] = { NULL, list->first_node, NULL };

	int current_position = 1;

	while ( current_position < position )
	{
		if ( nodes[1] == NULL )
		{
			nodes[1] = calloc( 1, list_get_node_size( list ) );

			if ( nodes[1] == NULL )
			{
				printf("Error on function [list_element_create]. Could not create node.");

				return NULL;
			}

			list_node_connect( nodes[0], nodes[1] );

			list_node_connect( nodes[1], NULL );
		}

		nodes[0] = nodes[1];

		nodes[1] = *list_node_get_field_next( nodes[0] );

		current_position++;
	}

	nodes[2] = nodes[1];

	nodes[1] = calloc( 1, list_get_node_size( list ) );

	if ( nodes[1] == NULL )
	{
		printf("Error on function [list_element_create]. Could not create node.");

		return NULL;
	}

	list_node_connect( nodes[0], nodes[1] );

	list_node_connect( nodes[1], nodes[2] );

	if ( *list_node_get_field_previous( nodes[1] ) == NULL )
	{
		list->first_node = nodes[1];
	}

	if ( *list_node_get_field_next( nodes[1] ) == NULL )
	{
		list->last_node = nodes[1];
	}

	return list_node_get_content( nodes[1] );
}

void*
list_element_get
( struct list *list, int position )
{
	void *node = list->first_node;

	int current_position = 1;

	while ( current_position < position && node != NULL )
	{
		node = *list_node_get_field_next( node );

		current_position++;
	}	

	if ( node == NULL )
	{
		return NULL;
	}

	return list_node_get_content( node );
}

int
list_element_remove
( struct list *list, int position )
{
	void *node = list->first_node;

	int current_position = 1;

	while ( current_position < position && node != NULL )
	{
		node = list_node_get_field_next( node );

		current_position++;
	}

	if ( node == NULL )
	{
		return 1;
	}

	else
	{
		void *neighbours[2] = { *list_node_get_field_previous( node ), *list_node_get_field_next( node ) };

		free( node );

		list_node_connect( neighbours[0], neighbours[1] );

		return 0;
	}
}

