#include "pagerank.h"

float new_proba(vertex *v, vertex *super_vertex, size_t len)
{
	float 	new_proba = 0;
	
	for (t_list *cur = v->prede; cur != NULL; cur = cur->next)
		new_proba += cur->vertex->proba * (1 - EPSILON(len)) / cur->vertex->len_links;
	new_proba += super_vertex->proba / len;
	return new_proba;
}

float	new_super_proba(vertex_lst *v_lst)
{
	float	new_proba = 0;

	for (size_t i = 0; i < v_lst->len; i++)
		new_proba += v_lst->Adj[i].proba * EPSILON(v_lst->len);
	return new_proba;
}

void	update_probas(vertex_lst *v_lst)
{
	float	probas[v_lst->len];

	for (size_t i = 0; i < v_lst->len; i++)
		probas[i] = new_proba(&v_lst->Adj[i], &v_lst->super_vertex, v_lst->len);
	
	v_lst->super_vertex.proba = new_super_proba(v_lst);
	for (size_t i = 0; i < v_lst->len; i++)
		v_lst->Adj[i].proba = probas[i];
}

void	print_diff(vertex_lst *v_lst, float *values)
{
	float max_erreur;
	float erreur;

	max_erreur = fabs(v_lst->super_vertex.proba - values[0]) / values[0];
	// printf("super\t= %e  vl = %e  err = %f %%\n", v_lst->super_vertex.proba, values[0], 100 * max_erreur);
	for (size_t i = 0; i < v_lst->len; i++)
	{
		erreur = fabs(v_lst->Adj[i].proba - values[i + 1]) / values[i + 1];
		if (erreur > max_erreur)
			max_erreur = erreur;
		// printf("%lu\t= %e  vl = %e  err = %f %%\n", i, v_lst->Adj[i].proba, values[i + 1], 100 * erreur);
	}
	printf("Error max = %f %%\n", 100 * max_erreur);
}