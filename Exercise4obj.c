#include <stdio.h>

typedef struct Pixel{
    int x;
    int y;
    int grp;
    int value;
} Pixel;

void groupNeighbors(int n, int m, Pixel pixelGrid[n][m], int i, int j, int group){
    if(pixelGrid[i][j].grp == group){
        return;
    }

    pixelGrid[i][j].grp = group;

    Pixel neighbors[8] = {pixelGrid[i - 1][j - 1], pixelGrid[i][j - 1],
		pixelGrid[i + 1][j - 1], pixelGrid[i - 1][j],
		pixelGrid[i + 1][j], pixelGrid[i - 1][j + 1],
		pixelGrid[i][j + 1], pixelGrid[i + 1][j + 1]};
    
    for (int k = 0; k < 8; k++) {
		if(neighbors[k].value == 1){
			neighbors[k].grp = pixelGrid[i][j].grp;
			groupNeighbors(n, m, pixelGrid, neighbors[k].x, neighbors[k].y, group);
		}
	}
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int nGrid = n + 2;
    int mGrid = m + 2;
    Pixel grid[nGrid][mGrid];

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &grid[i][j].value);
            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].grp = -1;
        }
    }
       
    int grp = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(grid[i][j].value == 1 && grid[i][j].grp < 0){
                groupNeighbors(nGrid, mGrid, grid, i, j, grp++);
            }
        }
    }
    printf("\n");
    printf("%d\n", grp);
    return 0;
}

