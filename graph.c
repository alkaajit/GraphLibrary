/****************************************************************
 *								*
 * Name: Alka Ajit						*
 * G# : G01220250						*
 *								*	
 ****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"

/* This function initializes a new Graph structure and returns the
 * pointer to it.
 * Argument : None
 * Return : pointer to the new initialized graph, on success
 * 	    NULL, on failure
 */

Graph *graph_initialize(){
	
	Graph *graph = malloc(sizeof(Graph));
	
	if(graph == NULL){
		return NULL;
	}
	
	int i = 0;
	int j = 0;
	
	//Initializes max_vertex to -1
	graph->max_vertex = -1;
	
	//Initializes graph to a state with no edges and no vertices 
	for(i=0;i<MAX_VERTICES;i++){
		for(j=0;j<MAX_VERTICES;j++){
			graph->adj_matrix[i][j] = -1;
		}
	}
	
	//Initializes array to store visited vertex to 0 (not visited state)
	for(i=0;i<MAX_VERTICES;i++){
		graph->visited[i] = 0;
	}

	return graph;
}	

/* Function set the highest vertex in the graph 
 * Argument : Pointer to graph of which highest max vertex is to be set
 * Return : void 
 */
static void graph_set_max_vertex(Graph *graph){
	
	if(graph == NULL){
		return;
	}
	//Set max_vertex to initial state
	graph->max_vertex = -1;
	
	int i = 0; 
	
	for(i = 0;i<MAX_VERTICES;i++){
		//check if vertex is present and it is greater than the 
		//existing max_vertex
		if(graph->adj_matrix[i][i] > -1 && i > graph->max_vertex){
			graph->max_vertex = i;
		}
	}
}

/* Function adds vertex to the graph
 * v1 not a legal vertex if value is  <0 or >= MAX_VERTICES
 * Argument : Pointer to graph, vertex 
 * Return : 0, if added successfully or if it already exists
 * 	    -1, on error
 */
int graph_add_vertex(Graph *graph, int v1){
	//Error if graph null or v1 not a legal value
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES){
		return -1;
	}
	//Success,if v1 already exists
	if(graph->adj_matrix[v1][v1] > -1){
		return 0;
	}
	//set v1 to 0 
	graph->adj_matrix[v1][v1] = 0;
	//check if v1 > graph->max_vertex
	//if yes, set graph->max_vertex as v1
	if(v1 > graph->max_vertex){
		graph->max_vertex = v1;
	}

	return 0;

}

/* Function checks if vertex is in graph
 * Argument : Pointer to graph, vertex 
 * Return : 1, if vertex exists
 * 	    0, on error or if vertex not in graph
 */
int graph_contains_vertex(Graph *graph, int v1){
	//Error if graph is NULL or v1 is not a legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES){
                return 0;
        }
	//Success if v1 is present(value = 0) or 
	//self-loop at v1 (value > 0)
	if(graph->adj_matrix[v1][v1] > -1){
		return 1;
	}

	return 0;
}

/* Function removes vertex and all connected edges to this vertex from graph
 * Argument : Pointer to graph, vertex
 * Return : 0, on success or vertex not in graph
 *          -1, on error
 */ 
int graph_remove_vertex(Graph *graph, int v1){
	//Error if Graph is NULL or v1 not a legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES){
                return -1;
        }

	int i = 0;
	int j = 0;
	//if v1 not in graph, return success
	if(graph->adj_matrix[v1][v1] == -1){
		return 0;
	}
	//Set v1 to -1, no vertex
	graph->adj_matrix[v1][v1] = -1;
	//set all connected edges of v1 to -1
	for(i = 0; i <= graph->max_vertex; i++)
	{
		for(j=0;j <= graph->max_vertex; j++){
			if(graph->adj_matrix[v1][j] > -1){
					graph->adj_matrix[v1][j] = -1;
			} 
		}
		if(graph->adj_matrix[i][v1] > -1){
			graph->adj_matrix[i][v1] = -1;
		}
	}
	//if v1 was graph->max_vertex, call graph_set_max_vertex to 
	//get new graph->max_vertex
	if(v1 == graph->max_vertex){
		graph_set_max_vertex(graph);
	}
	
	return 0;
}

/* Function to add an edge between two vertices with weight in the graph
 * Argument : pointer to graph, vertices and weight
 * Return : 0, on success
 * 	    -1, on error
 */
int graph_add_edge(Graph *graph, int v1, int v2, int wt){
	//Error if graph is NULL or if v1 or v2 is not a legal vertex 
	//or if wt <= 0 
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES \
			 || v2 < 0 || v2 >= MAX_VERTICES || wt <= 0){
                return -1;
        }
	//Error if v1 or v2 not present
	if(graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return -1;
	}
	//Add edge v1,v2. If already present,updates to new weight.
	graph->adj_matrix[v1][v2] = wt;

	return 0;
}
	
/* Function checks if edge present in graph
 * Argument : pointer to graph and end vertices of edge
 * Return : 1, on success
 * 	    0, on error
 */
int graph_contains_edge(Graph *graph, int v1, int v2){
	//Error if graph is NULL or if v1 or v2 is not a legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES \
			 || v2 < 0 || v2 >= MAX_VERTICES){
                return 0;
        }
	//Error if v1 or v2 doesn't exist
        if(graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
                return 0;
        }
	//Edge present if value > 0
	if(graph->adj_matrix[v1][v2] > 0){
		return 1;
	}
	
	return 0;
}

/* Function to remove edge between to 2 vertices in the graph
 * Argument : Pointer to graph , end vertices of edge
 * Return : 0, on success
 * 	    -1, on error
 */
int graph_remove_edge(Graph *graph, int v1, int v2){
	//Error if graph is null or if v1 or v2 is not legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES \
			 || v2 < 0 || v2 >= MAX_VERTICES){
                return -1;
        }
	//Error if v1 or v2 does not exist
        if( graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
                return -1;
        }
	//If v1 == v2, set value to 0 (vertex is present)
	//else, set value to -1 (no edge between v1 and v2)
	if(v1 == v2 && graph->adj_matrix[v1][v2] > -1){
		graph->adj_matrix[v1][v2] = 0;
	}
	else if(graph->adj_matrix[v1][v2] > 0){
		graph->adj_matrix[v1][v2] = -1;
	}
	
	return 0;
}

/* Function to get number of vertices in graph
 * Argument : Pointer to graph
 * Returns : total vertices in graph, on success
 * 	     -1, on error
 */
int graph_num_vertices(Graph *graph){
	//Error if graph is NULL
	if(graph == NULL){
                return -1;
        }
	//counter variable
	int count = 0;
	int i = 0;	

	for(i=0;i<= graph->max_vertex;i++){
		//if value > -1, vertex is present
		if(graph->adj_matrix[i][i] > -1){
			count ++;
		}
	}

	return count;
}

/* Function to get number of edges in graph
 * Argument : Pointer to graph
 * Return : total edges in graph, on success
 * 	    -1, on error
 */
int graph_num_edges(Graph *graph){
	//Error if graph is NULL
	if(graph == NULL){
        	return -1;
        }

	int i = 0;
	int j = 0;
	//counter variable
	int count = 0;
	for(i=0;i<= graph->max_vertex;i++)
	{
		for(j=0;j<=graph->max_vertex; j++){
			//if value > 0, edge is present
			if(graph->adj_matrix[i][j] > 0){
				count ++;
			}
		}
	}

	return count;
}

/* Function gets sum of all edge weights in the graph
 * Argument : Pointer to graph
 * Return : Total weight of all edges,on success
 * 	    -1, on error
 */
int graph_total_weight(Graph *graph){
	//Error if graph is NULL
	if(graph == NULL){
                return -1;
        }

	int i = 0;
	int j = 0;
	//counter variable
	int sum = 0;
	for(i=0;i<=graph->max_vertex;i++)
        {
                for(j=0;j<= graph->max_vertex; j++){
                        //if edge weight > 0
			if(graph->adj_matrix[i][j] > 0){
                                sum += graph->adj_matrix[i][j];
                        }
                }
        }
        
	return sum;
}

/* Function gets the in-degree of a vertex in graph
 * Argument : Pointer to graph, vertex
 * Returns : in-degree of vertex
 */
static int graph_get_in_degree(Graph *graph, int v1){
	
        int i = 0;
        //counter variable
	int in_degree = 0;

        for (i= 0; i<= graph->max_vertex; i++){
        	//check if edge weight > 0 to vertex v1
		if(graph->adj_matrix[i][v1] > 0){
                	in_degree++;
                }
        }

        return in_degree;
}

/* Function gets the out-degree of a vertex in graph
 * Argument : Pointer to graph, vertex
 * Returns : out-degree of vertex
 */
static int graph_get_out_degree(Graph *graph, int v1){

        int i = 0;
        //counter variable
	int out_degree = 0;

        for (i= 0; i<= graph->max_vertex; i++){
                //check if edge weight > 0 from vertex v1
		if(graph->adj_matrix[v1][i] > 0){
                	out_degree++;
                }
        }

        return out_degree;
}

/* Function returns the total degree of edges on vertex
 * Argument : Pointer to graph, vertex
 * Return : Degree of v1, on success
 * 	    -1, on error
 */
int graph_get_degree(Graph *graph, int v1){
	//Error if graph is NULL or v1 is not a legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES){
                return -1;
        }
	//Error if v1 not present in graph
	if(graph->adj_matrix[v1][v1] == -1){
		return -1;
	}
	//Total_degree = in-degree + out-degree
	return graph_get_in_degree(graph,v1) + graph_get_out_degree(graph,v1) ;	
}

/* Function to get edge weight between two vertices in a graph
 * Argument : Pointer to graph, end vertices of the edge
 * Return : edge weight, on success 
 * 	    -1, on error
 */
int graph_get_edge_weight(Graph *graph, int v1, int v2){
	// Error if graph is NULL or v1 or v2 is not a legal vertex	
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES \
			 || v2 < 0 || v2 >= MAX_VERTICES){
                return -1;
        }
	//error if no edge present between v1 and v2
	if(graph->adj_matrix[v1][v2] <= 0){
		return -1;
	}
	
	return graph->adj_matrix[v1][v2];
	
}

/* Function to check if two vertices are connected
 * Argument : Pointer to graph, two vertices
 * Return : 1, on success
 * 	    0, on error
 */
int graph_is_neighbor(Graph *graph, int v1, int v2){
	//Error if graph is NULL or v1 or v2 is not a legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES \
			 || v2 < 0 || v2 >= MAX_VERTICES){
                return 0;
        }
	//Error if no vertex v1 or v2
	if(graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return 0;
	}
       	//Check if edge is present - v1->v2 > 0 or v2->v1 > 0 
	if(graph->adj_matrix[v1][v2] > 0 || graph->adj_matrix[v2][v1] > 0){
		return 1;
	}
	return 0;	
}

/* Function returns all predecessor of a vertex in the graph
 * Argument : Pointer to graph, vertex
 * Return : pointer to array of predecessors, on success
 * 	    NULL, on error
 */
int *graph_get_predecessors(Graph *graph, int v1){
	//Error if graph is NULL or v1 is not a legal vertex	
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES){
                return NULL;
        }
	//Error if vertex is not present in graph
        if(graph->adj_matrix[v1][v1] == -1){
                return NULL;
        }
	
	//Allocate array of size in_degree of v1 + 1 to add -1 at the end
	int * predecessor = malloc(graph_get_in_degree(graph,v1)+1);
	int i = 0;
	int j = 0;
	
	for(i=0;i<= graph->max_vertex;i++){
		//Check if edge to v1 present
		if(graph->adj_matrix[i][v1] > 0){
			predecessor[j] = i;	
			j++;
		}
	}	
	//Add -1 to represent end of array
	predecessor[j] = -1;
	return predecessor;
}

/* Function returns all successors of a vertex in the graph
 * Argument : Pointer to graph, vertex
 * Return : pointer to array of successors, on success
 * 	    NULL, on error
 */
int *graph_get_successors(Graph *graph, int v1){
	//Error if graph is NULL or v1 is not a legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES){
                return NULL;
        }
	//Error if vertex not present in graph
        if(graph->adj_matrix[v1][v1] == -1){
                return NULL;
        }
	// Allocate array of size out_degree of v1 + 1 to add -1 at end
        int * successor = malloc(graph_get_out_degree(graph,v1)+1);
        int i = 0;
        int j = 0;

        for(i=0;i<= graph->max_vertex;i++){
		// Check if edge from v1 is present
                if(graph->adj_matrix[v1][i] > 0){
                        successor[j] = i;
                        j++;
                }
        }
	//Add -1 to represent end of array
        successor[j] = -1;
        return successor;
}
/* Function to do depth first seach to find if path exists to other vertices
 * from vertex v1 on the graph
 * Argument: Pointer to graph, vertex
 * Return : void
 */
void graph_DFS(Graph *graph, int v1)
{
	int j;
    	for(j=0;j<graph->max_vertex;j++){
		//check if vertices are not equal and the vertex j has not been 
		//visited and edge between v1 and j exists
       		if(v1 != j && !graph->visited[j] && graph->adj_matrix[v1][j] > 0){
			//set j to 1 if visited
			graph->visited[j]=1;
			graph_DFS(graph,j);
		}
	}	
}

/* Function checks if a path exists between two vertices in a graph
 * Argument : Pointer to graph, vertices 
 * Return : 0, if path doesn't exist
 * 	    1, if path exists
 */
int graph_has_path(Graph *graph, int v1, int v2){

	//Error if graph is NULL or v1 or v2 is not a legal vertex
	if(graph == NULL || v1 < 0 || v1 >= MAX_VERTICES \
			 || v2 < 0 || v2 >= MAX_VERTICES){
                return 0;
        }

	int i = 0;
	//check if there is a self loop on v1 
	if(v1 == v2 && graph->adj_matrix[v1][v1] > 0)
	{	
		return 1;
	}
	else{
		//reset graph->visited array
		for(i = 0;i < graph->max_vertex;i++){
			graph->visited[i] = 0;
		}
		//Do depth first search on v1
		graph_DFS(graph,v1);
		//check if v2 is present in visited array
		if(graph->visited[v2] == 1){
			return 1;
		}
        }
	return 0;
}

/* Function to print graph as adjacency matrix
 * Argument : Pointer to graph
 * Return : void
 */
void graph_print(Graph *graph){
	//Error if graph is NULL	
	if (graph == NULL){
		return;
	}

	int i = 0;
	int j = 0; 
	// To print columns
	printf("   | ");
	for(i = 0; i<= graph->max_vertex;i++){
		printf("%5d",i);
	}
	//Design
	printf("\n");
	for(i = 0; i<= graph->max_vertex;i++){
                printf("------");
        }
	
	printf("\n");
	for(i = 0;i <= graph->max_vertex;i++){
		//print rows
		printf(" %d | ",i);
		for(j = 0;j <= graph->max_vertex;j++){
			//print value
			printf("%5d", graph->adj_matrix[i][j]);
		}
		printf("\n");
	}	
	//Design
	for(i = 0; i<= graph->max_vertex;i++){
                printf("------");
        }
	//Reference
	printf("\n|------------------------------------|\n");
	printf("| Reference:                         |\n");
	printf("|        -1 denotes no vertex or edge|\n");
	printf("|        0 denotes vertex exists     |\n");
	printf("|        > 0 denotes edge exists     |"); 
	printf("\n|------------------------------------|\n");
}

/* Function outputs graph in format for GraphViz program as file
 * Argument : Pointer to graph, file
 * Return : void
 */
void graph_output_dot(Graph *graph, char *filename){
	//Error if graph is NULL	
	if(graph == NULL){
		return;
	}
	
	FILE *fp = fopen(filename, "w+");
	//Error if fp is NULL
	if(fp == NULL){
		return;
	}
	
	int i = 0; 
	int j = 0;
	//to add vertex that exists which has no edges to file 
	int flag = 0;
	
	fprintf(fp, "digraph{\n");
	for(i = 0;i<= graph->max_vertex;i++){
		for(j=0;j<= graph->max_vertex;j++){
			//check if edge exists
			if(graph->adj_matrix[i][j] > 0){
				fprintf(fp,"%d -> %d [label = %d];\n",\
					 i,j,graph->adj_matrix[i][j]);
				flag = 1;
			}
		}
		//Add vertex if it is present but has no edges
		if(flag == 0 && graph->adj_matrix[i][i] == 0){
			fprintf(fp,"%d;\n",i);
		}
		//reset flag
		flag = 0;
	}

	fprintf(fp,"}");
	fclose(fp);
}

/* Function loads graph from a file
 * Argument : Pointer to graph, file to load
 * Return : 0, on success
 * 	    -1, on error;
 */
int graph_load_file(Graph *graph, char *filename){
	//if graph is not NULL, free graph
	if(graph != NULL){
		free(graph);
	}
	//Initialize graph
	if(graph_initialize(graph) == NULL){
		return -1;
	}
	
	char buffer[FILE_ENTRY_MAX_LEN];
	char * token = NULL;
	char * tmp = NULL;
	int v1 = -1;
	int v2 = -1;
	int wt = 0;

	FILE* fp = fopen(filename, "r");
	//failed to open file
	if(fp == NULL){
		return -1;
	}
	
	//till end of file
	while(!feof(fp)){
		fgets(buffer,FILE_ENTRY_MAX_LEN,fp);
		//Assign first token to v1
		token = strtok(buffer,",");
		if(token != NULL){
			v1 = atoi(token);
			//Add vertex v1 to graph
			if(graph_add_vertex(graph,v1)== -1){
				return -1;
			}
		}
		//Assign second token if present to v2
		token = strtok(NULL,",");
		if(token != NULL){
			v2 = atoi(token);
			//Assign third if present token to wt
			tmp = strtok(NULL,",");
			if(tmp != NULL){
				wt = atoi(tmp);
				//Add vertex v2 to graph
				if(graph_add_vertex(graph,v2) == -1){
					return -1;
				}
				//Add edge from v1 to v2 with weight wt 
				if(graph_add_edge(graph,v1,v2,wt) == -1){
					return -1;
				}
			}
		}
	}
	
	token = NULL;
	tmp = NULL;
	fclose(fp);
	
	return 0;
}

/* Function to save graph to file
 * Argument : Pointer to graph, file to save
 * Return : 0, on success
 * 	    -1, on failure
 */
int graph_save_file(Graph *graph, char *filename){
	//Error if graph is NULL;
	if(graph == NULL){
		return -1;
	}

	FILE *fp = fopen(filename,"w+");
	//failed to open file
	if(fp == NULL){
		return -1;
	}
	
	int i = 0;
	int j = 0;
	
	for(i = 0;i<= graph->max_vertex; i++){
		for(j=0;j<= graph->max_vertex;j++){
			//add edge to file,if present
			//add vertex if it exists, but has no edges, to file
			if(graph->adj_matrix[i][j]>0){
				fprintf(fp,"%d,%d,%d\n", i,\
					 j, graph->adj_matrix[i][j] );
			}
			else if(i == j && graph->adj_matrix[i][j] == 0){
				fprintf(fp,"%d\n",i);
			}
		}
	}

	fclose(fp);
	return 0;
}
