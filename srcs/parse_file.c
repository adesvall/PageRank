
#include "pagerank.h"

void	create_link(vertex_lst *v_lst, int i_src, int i_dst)
{
	vertex	*src = &v_lst->tab[i_src];
	vertex	*dst = &v_lst->tab[i_dst];

	src->len_links++;
	add_elem(&src->links, dst);
	add_elem(&dst->prede, src);
}

int	parse_line(char *line, vertex_lst *v_lst, int i_line)
{
	char *tok;
	int i_column = 0;

	tok = strtok(line, " ");
	while (tok)
	{
		printf("'%s'\n", tok);
		if (tok[0] == '0')
			;
		else if (tok[0] == '1')
			create_link(v_lst, i_line, i_column);
		tok = strtok(NULL, " ");
		i_column++;
	}
	return (0);
}

int	parse_file(char *file, vertex_lst *v_lst)
{
	FILE		*flux;
	char		*line = NULL;
	size_t		len = 0;
	__ssize_t		read;

	flux = fopen(file, "r");
	if (flux == NULL)
		return (1);

	if ((read = getline(&line, &len, flux)) == -1)	{
		free(line);
		return (-1);
	}
	printf("Réception d'une ligne de longueur %zu :\n", read);
	printf("%s", line);
	v_lst->len = read / 2;
	v_lst->tab = malloc(v_lst->len * sizeof(vertex));
	int i_line = 0;
	if (parse_line(line, v_lst, i_line))
		return (-1);
	while ((read = getline(&line, &len, flux)) != -1)
	{
		printf("Réception d'une ligne de longueur %zu :\n", read);
		printf("%s", line);
		i_line++;
		if (parse_line(line, v_lst, i_line))
			return (-1);
	}
	if (line)
		free(line);
	return (0);
}