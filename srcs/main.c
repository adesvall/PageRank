#include "pagerank.h"

float maj_proba(vertex *v)
{
	float 	new_proba = 0;
	
	for (t_list *cur = v->prede; cur != NULL; cur = cur->next)
	{
		new_proba += cur->vertex->proba;
	}
	return new_proba;
}

int main(int argc, char *argv[])
{
	vertex_lst	adj;
	char *file = NULL;

	if (argc >= 2)
		file = argv[2];
	
	parse_file(file, &adj);

	return 0;
}
