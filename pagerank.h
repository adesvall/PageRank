#ifndef PAGERANK_H
# define PAGERANK_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <math.h>

# define EPSILON(n) 1.0f / (10 * n)


typedef struct s_vertex vertex;

typedef struct	s_list
{
	vertex			*vertex;
	struct s_list	*next;
}				t_list;

typedef struct	s_vertex
{
	float	proba;
	size_t	len_links;
	t_list	*links;
	t_list	*prede;
}				vertex;

typedef struct	s_vertex_lst
{
	vertex	*Adj;
	vertex	super_vertex;
	size_t	len;
}				vertex_lst;


int		add_elem(t_list **alst, vertex *v);
void	delete_lst(t_list *lst);

int		init_vertex_lst(vertex_lst *v_lst);
int		create_link(vertex_lst *v_lst, int i_src, int i_dst);
void	delete_vertex_lst(vertex_lst *v_lst);

void	update_probas(vertex_lst *v_lst);
void	print_diff(vertex_lst *v_lst, float *values);

int		parse_test_file(char *file, vertex_lst *v_lst, float **values);
int		parse_normal_file(char *file, vertex_lst *v_lst, char ***names);
void	free_tab(char **tab);

#endif
