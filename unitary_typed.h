struct list
{
	unsigned int element_size;

	void *first_node;

	void *last_node;
};

size_t
list_get_node_size
( struct list *list );

struct list*
list_create
( size_t size );

void
list_destroy
( struct list *list );

struct list*
list_merge
( struct list *list1, struct list *list2, int position );

unsigned int
list_get_length
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

