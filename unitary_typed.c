#include <stdlib.h>

#include <string.h>

#include "unitary_typed.h"

enum node_fields
{
	previous = 1,

	next,

	content
};

void*
list_node_get_field
( void* node, int field )
{
	size_t offset;

	if ( field == 1 )
	{
		offset = 0;
	}

	else if ( field == 2 )
	{
		offset = sizeof( void* );
	}

	else if ( field == 3 )
	{
		offset = 2 * sizeof( void* );
	} 

	return node + offset;
}

void*
list_node_create
( struct list *list )
{
	void* node = calloc( 1, list_get_node_size( list ) );

	void** field;

	enum node_fields field_name;

	field_name = previous;

	field = (void**)list_node_get_field( list->first_node, field_name );

	*field = NULL;

	field_name = next;

	field = (void**)list_node_get_field( list->first_node, field_name );

	*field = NULL;

	return node;
}

int
list_node_connect
( void* node_1, void* node_2 )
{
	void** field;

	enum node_fields field_name;

	field_name = next;

	field = list_node_get_field( node_1, field_name );

	*field = node_2;

	field_name = previous;

	field = list_node_get_field( node_2, field_name );

	*field = node_1;

	return 0;
}

size_t
list_get_node_size
( struct list *list )
{
	return ( 2 * sizeof( void* ) ) + sizeof( unsigned int ) + list->element_size;
}

struct list*
list_create
( size_t size )
{
	struct list *list = malloc( sizeof( struct list ) );

	list->element_size = size;

	list->first_node = list_node_create( list );

	//printf("Node adress:%p\nNode field adress: %p\n", list->first_node, node_field);

	return list;
}

int
list_destroy
( struct list *list )
{
	enum node_fields field_id = next;

	void *previous_node = NULL;

	void *current_node = list->first_node;

	while ( current_node != NULL )
	{
		previous_node = current_node;

		current_node = *( void** )list_node_get_field( current_node, field_id );

		free( previous_node );
	}

	free( list );

	return 0;
}

void*
list_element_create
( struct list *list, int position )
{
	void *nodes[3] = { NULL, list->first_node, NULL };

	int current_position = 1;

	enum node_fields field_name = next;

	while ( current_position < position )
	{
		if ( nodes[1] == NULL )
		{
			nodes[1] = list_node_create( list );

			if ( nodes[1] == NULL )
			{
				return NULL;
			}

			if ( nodes[0] != NULL )
			{
				list_node_connect( nodes[0], nodes[1] );
			}
		}

		nodes[0] = nodes[1];

		nodes[1] = *( void** )list_node_get_field( nodes[0], field_name );

		current_position++;
	}

	nodes[2] = nodes[1];

	nodes[1] = list_node_create( list );

	if ( nodes[1] == NULL )
	{
		return NULL;
	}

	if ( nodes[2] != NULL )
	{
		list_node_connect( nodes[1], nodes[2] );
	}

	if ( nodes[0] != NULL )
	{
		list_node_connect( nodes[0], nodes[1] );
	}

	else
	{
		list->first_node = nodes[1];
	}

	field_name = content;

	return (void*)list_node_get_field( nodes[1], field_name );
}

void*
list_element_get
( struct list *list, int position )
{
	void *node = list->first_node;

	int current_position = 1;

	enum node_fields field_name = next;

	while ( current_position < position && node != NULL )
	{
		node = *( void** )list_node_get_field( node, field_name );

		current_position++;
	}	

	if ( node == NULL )
	{
		return NULL;
	}

	field_name = content;

	return (void*)list_node_get_field( node, field_name );
}

