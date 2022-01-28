
#include "pagerank.h"

int	parse_line(char *line, vertex_lst *v_lst, int i_line)
{
	char *tok;
	int i_column = 0;

	tok = strtok(line, " \n");
	while (tok)
	{
		if (tok[0] == '0')
			;
		else if (tok[0] == '1')
			create_link(v_lst, i_line, i_column);
		else
			return (-1);
		tok = strtok(NULL, " \n");
		i_column++;
	}
	return (0);
}

void	get_test_values(char *line, float *values)
{
	char *tok;
	int i = 0;

	tok = strtok(line, ", ");
	while (tok)
	{
		values[i] = atof(tok);
		tok = strtok(NULL, ", ");
		i++;
	}
}

int	parse_test_file(char *file, vertex_lst *v_lst, float **values)
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
	// printf("Réception d'une ligne de longueur %zu :\n", read);
	// printf("%s", line);
	v_lst->len = read / 2;
	*values = malloc(sizeof(float) * (v_lst->len + 1));
	if (!values || init_vertex_lst(v_lst))
	{
		free(line);
		fclose(flux);
		return (-1);
	}
	size_t i_line = 0;
	if (parse_line(line, v_lst, i_line))
	{
		free(line);
		fclose(flux);
		return (-1);
	}
	i_line++;
	while (i_line < v_lst->len && (read = getline(&line, &len, flux)) != -1)
	{
		if (parse_line(line, v_lst, i_line))
		{
			free(line);
			fclose(flux);
			return (-1);
		}
		i_line++;
	}
	while ((read = getline(&line, &len, flux)) != -1)
	{}
	get_test_values(line, *values);
	if (line)
		free(line);
	fclose(flux);
	return (0);
}