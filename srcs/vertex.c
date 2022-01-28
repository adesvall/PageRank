#include "pagerank.h"

int	create_link(vertex_lst *v_lst, int i_src, int i_dst)
{
	vertex	*src = &v_lst->Adj[i_src];
	vertex	*dst = &v_lst->Adj[i_dst];

	src->len_links++;
	if (add_elem(&src->links, dst))
		return -1;
	if (add_elem(&dst->prede, src))
		return -1;
	return 0;
}

void	delete_vertex_lst(vertex_lst *v_lst)
{
	for (size_t i = 0; i < v_lst->len; i++)
	{
		delete_lst(v_lst->Adj[i].links);
		delete_lst(v_lst->Adj[i].prede);
	}
	free(v_lst->Adj);
}

int	init_vertex_lst(vertex_lst *v_lst)
{
	v_lst->Adj = malloc(v_lst->len * sizeof(vertex));
	if (v_lst->Adj == NULL)
		return (-1);
	v_lst->super_vertex = (vertex) {0, 0, NULL, NULL};
	for (size_t i = 0; i < v_lst->len; i++)
	{
		v_lst->Adj[i] = (vertex) {1.0f / v_lst->len, 0, NULL, NULL};
		create_link(v_lst, i, i);
	}
	return (0);
}