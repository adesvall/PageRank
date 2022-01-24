#include "pagerank.h"

float maj_proba(vertex *v)
{
	float 	new_proba = 0;
	t_list 	*cur = v->prede;

	for (int i = 0; cur != NULL; cur = cur->next)
	{
		new_proba += cur->vertex->proba;
	}
	return ;
}

int main(int argc, char const *argv[])
{
	vertex_lst	adj;
	

	return 0;
}
