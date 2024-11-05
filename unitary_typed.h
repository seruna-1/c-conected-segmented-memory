struct list
{
	unsigned int element_size;

	void *first_node;
};

size_t
list_get_node_size
( struct list *list );

struct list*
list_create
( size_t size );

int
list_destroy
( struct list *list );

void*
list_element_create
( struct list*, int position );

void*
list_element_get
( struct list*, int position );

int
list_element_remove
( struct list*, int position );

