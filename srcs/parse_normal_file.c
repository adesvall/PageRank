#include "pagerank.h"

int	tab_len(char **tab)
{
	int i = 0;

	while (tab[i])
		i++;
	return i;
}

void	free_tab(char **tab)
{
	int i = 0;

	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	get_index(char **names, char *name)
{
	int	i = 0;
	while (names[i])
	{
		if (!strcmp(name, names[i]))
			return i;
		i++;
	}
	return -1;
}

size_t	counts_lines(FILE *flux)
{
	char		*line = NULL;
	size_t		len = 0;
	size_t		n_line = 0;

	while (getline(&line, &len, flux) != -1)
		n_line++;
	free(line);
	fseek(flux, 0, SEEK_SET);
	return n_line;
}

char	**malloc_names(FILE *flux)
{
	char		*line = NULL;
	char		*name;
	char		**names;
	size_t		len = 0;
	size_t		n_lines = counts_lines(flux);
	size_t		i = 0;

	names = malloc(sizeof(char*) * (n_lines + 1));
	if (names == NULL)
		return NULL;
	while (i < n_lines && getline(&line, &len, flux) != -1)
	{
		name = strtok(line, "|\n");
		if (names == NULL)
			return NULL;
		names[i] = strdup(name);
		i++;
	}
	if (line)
		free(line);
	names[i] = NULL;
	return names;
}

int	parse_wikiline(char *line, int *matrix, int i_line, char **names)
{
	char *tok;
	int i_column;

	tok = strtok(line, "|\n");
	tok = strtok(NULL, "|\n");
	while (tok)
	{
		i_column = get_index(names, tok);
		if (i_column != -1 && i_column != i_line)
			matrix[i_column] = 1;
		tok = strtok(NULL, "|\n");
	}
	return (0);
}

int	parse_links(FILE *flux, vertex_lst *v_lst, char **names)
{
	char		*line = NULL;
	size_t		len = 0;
	int 		*matrix_line = malloc(sizeof(int) * v_lst->len);

	printf("creating links...\n");
	fseek(flux, 0, SEEK_SET);
	int	i = 0;
	while (i < (int) v_lst->len)
	{
		bzero(matrix_line, v_lst->len * sizeof(int));
		getline(&line, &len, flux);
		if (parse_wikiline(line, matrix_line, i, names))
		{
			free(matrix_line);
			free(line);
			return (-1);
		}
		for (size_t column = 0; column < v_lst->len; column++)	{
			if (matrix_line[column])	{
				if (create_link(v_lst, i, column))
				{
					free(matrix_line);
					return -1;
				}
			}
		}
		if (i % 27 == 0)
			printf("%d linked...\r", i);
		i++;
	}
	printf("\n");
	if (line)
		free(line);
	free(matrix_line);
	return 0;
}

int	parse_normal_file(char *file, vertex_lst *v_lst, char ***names)
{
	FILE		*flux;

	flux = fopen(file, "r");
	if (flux == NULL)
		return -1;
	*names = malloc_names(flux);
	v_lst->len = tab_len(*names);
	printf("%ld entries\n", v_lst->len);
	if (!*names || init_vertex_lst(v_lst))
	{
		free_tab(*names);
		fclose(flux);
		return -1;
	}
	if (parse_links(flux, v_lst, *names))
	{
		free_tab(*names);
		fclose(flux);
		return -1;
	}

	fclose(flux);
	return 0;
}