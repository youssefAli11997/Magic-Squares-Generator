#include <bits/stdc++.h>

using namespace std;

int n = 3, countOfSquares = 0;

vector<vector<vector<int>>> squares;

int rowSum(vector<vector<int>> grid, int r){
    int sum = 0;
    for(int i=0; i<n; i++)
        sum += grid[r][i];
    return sum;
}

int colSum(vector<vector<int>> grid, int c){
    int sum = 0;
    for(int i=0; i<n; i++)
        sum += grid[i][c];
    return sum;
}

int diagonalSum(vector<vector<int>> grid, int diagonal){
    int sum = 0;
    for(int i=0; i<n; i++){
        if(diagonal == 0)
            sum += grid[i][i];
        if(diagonal == 1)
            sum += grid[i][n-i-1];
    }
    return sum;
}

bool rowSumsValid(vector<vector<int>> grid){
    for(int i=0; i<n; i++)
        if(rowSum(grid, i) != 15)
            return false;
    return true;
}

bool colSumsValid(vector<vector<int>> grid){
    for(int i=0; i<n; i++)
        if(colSum(grid, i) != 15)
            return false;
    return true;
}

bool diagonalSumsValid(vector<vector<int>> grid){
    int sum1 = 0, sum2 = 0;
    for(int i=0; i<n; i++)
        sum1 += grid[i][i];
    for(int i=0; i<n; i++)
        sum2 += grid[i][n-i-1];
    return sum1 == 15 && sum2 == 15;
}

void printGrid(vector<vector<int>> grid){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"---------------\n";
}

string putIn3DArrayFormat(){ // to pre-load them in another program
    string result = "{";
    for(int i=0; i<squares.size(); i++){
        if(i > 0)
            result += ", ";
        result += "{";
        for(int j=0; j<squares[i].size(); j++){
            if(j > 0)
                result += ", ";
            result += "{";
            for(int k=0; k<squares[i][j].size(); k++){
                if(k > 0)
                    result += ", ";
                result += (char)(squares[i][j][k] + '0');
            }
            result += "}";
        }
        result += "}";
    }
    result += "}";

    return result;
}

void generateMagicSquares(int r, int c, vector<vector<int>> grid, vector<bool> used){
    //stopping conditions
    if(r == 3){
        if(diagonalSumsValid(grid) && rowSumsValid(grid) && colSumsValid(grid)){
            // a valid square
            cout<<"Square #"<<++countOfSquares<<"\n";
            printGrid(grid);
            squares.push_back(grid);
        }
        return;
    }
    if(r >= 3 || c >= 3)
        return;
    if(rowSum(grid, r) > 15 || colSum(grid, c) > 15) // row and column prone
        return;
    if((r == c && diagonalSum(grid, 0) > 15) || (r == n-c-1 && diagonalSum(grid, 1) > 15)) // diagonal prone
        return;

    // recurrence
    for(int num=1; num<10; num++){
        if(used[num])
            continue;
        grid[r][c] = num;
        used[num] = true;
        if(c == 2)
            generateMagicSquares(r+1, 0, grid, used);
        else
            generateMagicSquares(r, c+1, grid, used);
        grid[r][c] = 0;
        used[num] = false;
    }
}

int main()
{
    cout << "Welcome to magic squares generator!" << endl;
    cout << "I am going to generate all 3x3 magic squares!" << endl << endl;

    generateMagicSquares(0, 0, vector<vector<int>>(n, vector<int>(n, 0)),
                          vector<bool>(10, false));
    cout << "Number of squares: " << countOfSquares << endl;
    // if you want to use them in your code
    cout << "Squares in 3D array format: (to pre-load them in your code)" << endl;
    cout << putIn3DArrayFormat() << endl;
    return 0;
}
