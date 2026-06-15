#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int count_neighbourgs(int y, int x, int width, int height, int** matrix){
    int count = 0;
    for(int dy = -1; dy <= 1; ++dy){
        for(int dx = -1;dx <= 1; ++dx){
            if(dx == 0 && dy == 0)
                continue;
            if(y + dy >= 0 && y+dy < height && x + dx >= 0 && x + dx < width)
                count += matrix[y+dy][x+dx];
        }
    }
    return count;
}

void delete_matrix(int** matrix, int size){
    if(!matrix)
        return;
    for(int i = 0; i < size; i++){
        if(matrix[i])
            free(matrix[i]);
    }
    free(matrix);
}

void display_matrix(int** matrix, int height, int width){
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            if(matrix[y][x])
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}


int main(int argc, char** argv) {
    if(argc != 4)
        return 1;
    
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iter = atoi(argv[3]);

    if (width <= 0 || height <= 0 || iter < 0) return 0;
    
    int** matrix = (int**)malloc(height * sizeof(int*));
    if(!matrix)
        return 1;
    for(int i = 0; i < height; ++i){
        matrix[i] = (int*)calloc(width, sizeof(int));
        if(!matrix[i]){
            delete_matrix(matrix, i);
            return 1;
        }
    }

    int x = 0;
    int y = 0;
    int down = 0;
    char c;
    int rn = 1;

    while(rn){
        rn = read(0, &c, 1);
        if(rn < 0){
            delete_matrix(matrix, height);
            return 1;
        }
        if(rn == 0)
            break;
        if(c == 'w')
            y--;
        else if(c == 'a')
            x--;
        else if(c == 's')
            y++;
        else if(c == 'd')
            x++;
        else if(c == 'x')
            down = !down;

        if(down && y >= 0 && y < height && x >= 0 && x < width)
            matrix[y][x] = 1;
    }

    //iterations
    for(int j = 0; j < iter; ++j){
        int** new_matrix = (int**)malloc(height * sizeof(int*));
        if(!new_matrix){
            delete_matrix(matrix, height);
            return 1;
        }
        for(int k = 0; k < height; ++k){
            new_matrix[k] = (int*)calloc(width, sizeof(int));
            if(!new_matrix[k]){
                delete_matrix(new_matrix, k);
                delete_matrix(matrix, height);
                return 1;
            }
        }

        //one iteration
        int my=0;
        int mx=0;
        int num_neighbourg;
        for(my = 0; my < height; ++my){
            for(mx=0; mx < width; ++mx){
                num_neighbourg = count_neighbourgs(my, mx, width, height, matrix);
                if(matrix[my][mx] == 1){
                    if(num_neighbourg == 2 || num_neighbourg == 3)
                        new_matrix[my][mx] = 1;
                }
                else{
                    if(num_neighbourg == 3)
                        new_matrix[my][mx] = 1;
                }
            }
        }
        delete_matrix(matrix, height);
        matrix = new_matrix;
    }
    display_matrix(matrix, height, width);
    delete_matrix(matrix, height);
    return 0;
}