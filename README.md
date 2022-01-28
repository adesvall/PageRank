# Simplified PageRank Algorithm Implementation

## Compilation :
- make : compile program
- make clean : clean the .o
- make fclean : make clean & remove program
- make re : make fclean & make

## Usage :
- ./pagerank -t k
	Runs the tests with k updates and displays the percentage error
- ./pagerank -n path_to_graph.txt x
	Parse the wikipedia graph at path_to_graph.txt and displays the x most important websites in the list, with 100 updates
