
#include "pagerank.h"

int	add_elem(t_list **alst, vertex *v)
{
	t_list *new = malloc(sizeof(t_list));

	if (new == NULL)
		return -1;
	new->vertex = v;
	new->next = (*alst);
	*alst = new;
	return 0;
}

void	delete_lst(t_list *lst)
{
	if (lst == NULL)
		return;
	delete_lst(lst->next);
	free(lst);
}
