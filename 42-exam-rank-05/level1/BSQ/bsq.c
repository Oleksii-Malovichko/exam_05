
#include "bsq.h"

int getEl(FILE *fp, t_elements *el)
{
	int res = fscanf(fp, "%d %c %c %c", &el->n_lines, &el->empty, &el->obstacle, &el->full);
	if (res != 4)
		return -1;
	if (el->n_lines <= 0)
		return -1;
	if (el->empty == el->full || el->full == el->obstacle || el->obstacle == el->empty)
		return -1;
	if (el->empty < 32 || el->empty > 126)
		return -1;
	if (el->obstacle < 32 || el->obstacle > 126)
		return -1;
	if (el->full < 32 || el->full > 126)
		return -1;
	return 0;
}

char *ft_strndup(const char *line, int len)
{
	if (!line)
		return NULL;
	char *res = malloc(len + 1);
	if (!res)
		return NULL;
	int i = 0;
	while (line[i] && i < len)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

void free_arr(char **arr)
{
	if (!arr)
		return ;
	int i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

int elem_control(char **arr, char ch1, char ch2)
{
	int i = 0;
	while (arr[i])
	{
		int j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] != ch1 && arr[i][j] != ch2)
				return -1;
			j++;
		}
		i++;
	}
	return 0;
}

int getMap(FILE *fp, t_elements *el, t_map *map)
{
	map->height = el->n_lines;
	map->grid = calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return -1;
	map->grid[map->height] = NULL;
	char *line = NULL;
	size_t len = 0;
	if (getline(&line, &len, fp) == -1)
	{
		free(line);
		free_arr(map->grid);
		return -1;
	}

	int i = 0;
	while (i < map->height)
	{
		ssize_t read = getline(&line, &len, fp);
		if (read == -1)
		{
			free(line);
			free_arr(map->grid);
			return -1;
		}
		if (line[read - 1] == '\n')
			read--;
		else
		{
			free(line);
			free_arr(map->grid);
			return -1;
		}
		map->grid[i] = ft_strndup(line, (int)read);
		if (!map->grid[i])
		{
			free(line);
			free_arr(map->grid);
			return -1;
		}
		if (i == 0)
			map->width = (int)read;
		else
		{
			if (map->width != (int)read)
			{
				free(line);
				free_arr(map->grid);
				return -1;
			}
		}
		i++;
	}
	ssize_t extra = getline(&line, &len, fp);
	if (extra != -1)
	{
		free(line);
		free_arr(map->grid);
		return -1;
	}
	if (elem_control(map->grid, el->empty, el->obstacle) == -1)
	{
		free(line);
		free_arr(map->grid);
		return -1;
	}
	free(line);
	return 0;
}

int find_min(int n1, int n2, int n3)
{
	int min = n1;
	if (min > n2)
		min = n2;
	if (min > n3)
		min = n3;
	return min;
}

void find_sq(t_elements *el, t_map *map, t_square *sq)
{
	int matrix[map->height][map->width];
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (map->grid[i][j] == el->obstacle)
				matrix[i][j] = 0;
			else if (i == 0 || j == 0)
				matrix[i][j] = 1;
			else
			{
				int min = find_min(matrix[i-1][j], matrix[i-1][j-1], matrix[i][j-1]);
				matrix[i][j] = min + 1;
			}
			if (matrix[i][j] > sq->size)
			{
				sq->size = matrix[i][j];
				sq->i = i - matrix[i][j] + 1;
				sq->j = j - matrix[i][j] + 1;
			}
		}
	}
}

void print_sq(t_elements *el, t_map *map,t_square *sq)
{
	for (int i = sq->i; i < sq->i + sq->size; i++)
	{
		for (int j = sq->j; j < sq->j + sq->size; j++)
		{
			if (i < map->height && j < map->width)
				map->grid[i][j] = el->full;
		}
	}

	for (int i = 0; i < map->height; i++)
	{
		fprintf(stdout, "%s\n", map->grid[i]);
	}
}

int execute_bsq(FILE *fp)
{
	t_elements el;
	t_map map;
	t_square sq = {0,0,0};

	if (getEl(fp, &el) == -1)
		return -1;
	if (getMap(fp, &el, &map) == -1)
		return -1;
	find_sq(&el, &map, &sq);
	print_sq(&el, &map, &sq);
	free_arr(map.grid);
	return 0;
}

int convert_file(const char *name)
{
	FILE *fp = fopen(name, "r");
	if (!fp)
		return -1;
	int res = execute_bsq(fp);
	fclose(fp);
	return res;
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		if (execute_bsq(stdin) == -1)
			fprintf(stderr, "map error\n");
	}
	else if (argc == 2)
	{
		if (convert_file(argv[1]) == -1)
			fprintf(stderr, "map error\n");
	}
	else
	{
		int i = 1;
		while (i < argc)
		{
			if (convert_file(argv[i]) == -1)
				fprintf(stderr, "map error\n");
			if (i < argc - 1)
				fputs("\n", stdout);
			i++;
		}
	}
	return 0;
}

// int loadElements(FILE* file, t_elements* elements)
// {
// 	int ret = fscanf(file, "%d %c %c %c", &(elements->n_lines), &(elements->empty), &(elements->obstacle), &(elements->full));
// 	// printf("n=%d e=%c o=%c f=%c\n", elements->n_lines, elements->empty, elements->obstacle, elements->full);
// 	if((ret != 4))
// 		return(-1);

// 	if(elements->n_lines <= 0)
// 		return(-1);
// 	if(elements->empty == elements->obstacle || elements->empty == elements->full || elements->obstacle == elements->full)
// 		return(-1);
// 	if(elements->empty < 32 || elements->empty > 126)
// 		return(-1);
// 	if(elements->obstacle < 32 || elements->obstacle > 126)
// 		return(-1);
// 	if(elements->full < 32 || elements->full > 126)
// 		return(-1);

// 	return(0);
// }

// char* ft_substr(char* arr, int start, int len)
// {
// 	char* str = (char*)malloc(len + 1);
// 	if (!str)
// 		return (NULL);
// 	int i = 0;
// 	int j = 0;
// 	while (arr[i])
// 	{
// 		if ((i >= start) && (j < len))
// 		{
// 			str[j] = arr[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	str[j] = '\0';
// 	return(str);
// }

// void free_map(char** arr)
// {
// 	int	i = 0;
// 	if(arr)
// 	{
// 		while (arr[i] != NULL)
// 		{
// 			if(arr[i])
// 				free(arr[i]);
// 			i++;
// 		}
// 		free(arr);
// 	}
// }

// void print(char** arr)
// {
// 	int i = 0;
// 	while(arr[i])
// 	{
// 		printf("%s\n", arr[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

// int element_control(char** map, char c1, char c2)
// {
// 	int i = 0;
// 	while(map[i])
// 	{
// 		int j = 0;
// 		while(map[i][j] != '\0')
// 		{
// 			if((map[i][j] != c1) && (map[i][j] != c2))
// 				return(-1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return(0);
// }

// int loadMap(FILE* file, t_map* map, t_elements* elements)
// {
// 	map->height = elements->n_lines;
// 	map->grid = (char**)malloc((map->height + 1) * (sizeof(char *)));
// 	map->grid[map->height] = NULL;

// 	char* line = NULL;
// 	size_t len = 0;

// 	if(getline(&line, &len, file) == -1)
// 	{
// 		free_map(map->grid);
// 		return(-1);
// 	}

// 	//int i = 0;
// 	//while(i < elements->n_lines)
// 	for(int i = 0; i < map->height; i++)
// 	{
// 		int read = getline(&line, &len, file);
// 		if(read == -1)
// 		{
// 			free(line);
// 			free_map(map->grid);
// 			return(-1);
// 		}
// 		if(line[read - 1] == '\n')
// 			read--;
// 		// else if (i == map->height - 1)
// 		// {
// 		// 	// 
// 		// }
// 		else
// 		{			
// 			free(line);
// 			free_map(map->grid);
// 			return(-1);
// 		}
// 		map->grid[i] = ft_substr(line, 0, read);
// 		if(!(map->grid[i]))
// 		{
// 			free(line);
// 			free_map(map->grid);
// 			return(-1);
// 		}

// 		if(i == 0)
// 			map->width = read;
// 		else
// 		{
// 			if(map->width != read)
// 			{
// 				free(line);
// 				free_map(map->grid);
// 				return(-1);
// 			}
// 		}
// 		//i++;
// 	}

// 	ssize_t extra = getline(&line, &len, file);
// 	if(extra != -1)
// 	{
// 		free(line);
// 		free_map(map->grid);
// 		return(-1);
// 	}

// 	if(element_control(map->grid, elements->empty, elements->obstacle) == -1)
// 	{
// 		free(line);
// 		free_map(map->grid);
// 		return(-1);
// 	}

// 	free(line);

// 	return (0);
// }

// int find_min(int n1, int n2, int n3)
// {
// 	int min = n1;

// 	if(n2 < min)
// 		min = n2;
// 	if(n3 < min)
// 		min = n3;
// 	return(min);
// }

// void find_big_square(t_map* map, t_square* square, t_elements* elements)
// {
// 	// matrix init
// 	int matrix[map->height][map->width];
// 	for(int i = 0; i < map->height; i++)
// 	{
// 		for(int j = 0; j < map->width; j++)
// 			matrix[i][j] = 0;
// 	}

// 	for(int i = 0; i < map->height; i++)
// 	{
// 		for(int j = 0; j < map->width; j++)
// 		{
// 			if(map->grid[i][j] == elements->obstacle)
// 				matrix[i][j] = 0;
// 			else if(i == 0 || j == 0)
// 				matrix[i][j] = 1;
// 			else
// 			{
// 				int min = find_min(matrix[i - 1][j],matrix[i - 1][j - 1], matrix[i][j - 1]);
// 				matrix[i][j] = min + 1;
// 			}

// 			if(matrix[i][j] > square->size)
// 			{
// 				square->size = matrix[i][j];
// 				square->i = i - matrix[i][j] + 1;
// 				square->j = j - matrix[i][j] + 1;
// 			}
// 		}
// 	}
// 	/** matrix print
// 	for(int i = 0; i < map->height; i++)
// 	{
// 		for(int j = 0; j < map->width; j++)
// 		{
// 			printf("%d", matrix[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	*/

// }

// void print_filled_square(t_map* map, t_square* square, t_elements* elements)
// {

// 	for(int i = square->i; i < square->i + square->size; i++)
// 	{
// 		for(int j = square->j; j < square->j + square->size; j++)
// 		{
// 			if((i < map->height) && (j < map->width))
// 				map->grid[i][j] = elements->full;
// 		}
// 	}

// 	for(int i = 0; i < map->height; i++)
// 	{
// 		fprintf(stdout, "%s\n", map->grid[i]);
// 	}
// }

// int execute_bsq(FILE* file)
// {
// 	t_elements elements;
// 	if(loadElements(file, &elements) == -1)
// 	{
// 		return(-1);
// 	}

// 	t_map map;
// 	if(loadMap(file, &map, &elements) == -1)
// 	{
// 		return(-1);
// 	}

// 	//print(map.grid);

// 	t_square square;
// 	square.size = 0; square.i = 0; square.j = 0;
// 	find_big_square(&map, &square, &elements);
// 	// printf("size: %d, i: %d, j: %d", square.size, square.i, square.j);
// 	print_filled_square(&map, &square, &elements);
// 	free_map(map.grid);
// 	return(0);
// }

// int convert_file_pointer(char* name)
// {
// 	FILE* file = fopen(name, "r");
// 	if(!file)
// 		return(-1);
// 	int ret = 0;
// 	ret = execute_bsq(file);
// 	// printf("ret: %d\n", ret);
// 	fclose(file);
// 	return(ret);
// }
