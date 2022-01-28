#include "pagerank.h"

void	exit_and_free(int code, char *msg, vertex_lst *v_lst)
{
	if (msg)
		write(2, msg, strlen(msg));
	if (v_lst)
		delete_vertex_lst(v_lst);
	exit(code);
}

int	test_file(char *file, int k)
{
	vertex_lst	v_lst = (vertex_lst) {NULL, {}, 0};

	float	*values;

	if (parse_test_file(file, &v_lst, &values))
		exit_and_free(-1, "Erreur fichier\n", &v_lst);

	for (int i = 0; i < k; i++)
		update_probas(&v_lst);
	print_diff(&v_lst, values);
	free(values);
	delete_vertex_lst(&v_lst);
	return 0;
}

int	test_mode(char *karg)
{
	char *files[6] = {
		"tests/alea/alea4-6.txt",
		"tests/alea/alea4-12.txt",
		"tests/alea/alea10-40.txt",
		"tests/alea/alea50-1000.txt",
		"tests/alea/alea100-5000.txt",
		"tests/alea/alea1000-10000.txt",
		};

	for (int i = 0; karg[i]; i++)
	{
		if (!strchr("0123456789", karg[i]))
			exit_and_free(-1, "Bad k argument\n", NULL);
	}
	int k = atoi(karg);

	for (int test = 0; test < 6; test++)
	{
		printf("Test pour %s\n\t", files[test]);
		test_file(files[test], k);
	}
	return 0;
}

/* Here the sort is slow, complexite en n**2 but it is justified as x is not usually big  */
void	print_x_best(int x, char **names, vertex_lst *v_lst)
{
	float 	best;
	int		ibest;

	for (int rank = 0; rank < x && rank < (int)v_lst->len; rank++)
	{
		ibest = 0;
		best = 0;
		for (size_t i = 0; i < v_lst->len; i++)
		{
			if (v_lst->Adj[i].proba > best)
			{
				ibest = i;
				best = v_lst->Adj[i].proba;
			}
		}
		printf("%d %30s\t%f\n", ibest + 1, names[ibest], best);
		v_lst->Adj[ibest].proba = 0;
	}
}

int	normal_mode(char *file, char *x_arg)
{
	vertex_lst	v_lst = (vertex_lst) {NULL, {}, 0};

	for (int i = 0; x_arg[i]; i++)
	{
		if (!strchr("0123456789", x_arg[i]))
			exit_and_free(-1, "Bad x argument\n", NULL);
	}
	int x = atoi(x_arg);

	char	**names;
	if (parse_normal_file(file, &v_lst, &names))
		exit_and_free(-1, "Erreur parsing\n", &v_lst);

	printf("prossessing proba...\n");
	for (int i = 0; i < 100; i++)
		update_probas(&v_lst);

	print_x_best(x, names, &v_lst);
	free_tab(names);
	delete_vertex_lst(&v_lst);
	return 0;
}

int main(int argc, char *argv[])
{

	if (argc == 3 || argc == 4)
	{
		if (!strcmp("-t", argv[1]) && argc == 3)
			return test_mode(argv[2]);
		else if (!strcmp("-n", argv[1]) && argc == 4)
			return normal_mode(argv[2], argv[3]);
	}
	printf("Usage:\n%s\n", "test mode\t: ./programme -t k\ngraph mode\t: ./programme -n graphe.txt x");
	return -1;
}
