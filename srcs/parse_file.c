
#include "pagerank.h"

int	parse_line(char *line, vertex_lst *v_lst)
{
	v_lst->tab = malloc(v_lst->len * sizeof(vertex));
	char *tok;

	tok = strtok(line, " ");
	while (tok)
	{
		printf("'%s'\n", tok);
		if (tok[0] == '0')
			truc
		else if (tok[1] == '1')

		tok = strtok(NULL, " ");
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

	while ((read = getline(&line, &len, flux)) != -1)
	{
		printf("Réception d'une ligne de longueur %zu :\n", read);
		printf("%s", line);
		if (parse_line(line, v_lst))
			return (0);
	}
	if (line)
		free(line);
	return (0);
}