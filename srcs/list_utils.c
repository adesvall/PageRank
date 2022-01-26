
#include "pagerank.h"

void	add_elem(t_list **alst, vertex *v)
{
	while (*alst)
		alst = &(*alst)->next;
	*alst = malloc(sizeof(t_list));
	(*alst)->vertex = v;
	(*alst)->next = NULL;
}

