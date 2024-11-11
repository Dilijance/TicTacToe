#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


bool Xturn = true;
int size;

//Function to print out GameGround
void ShowGround(std::vector<std::vector<std::string>> ground) {
    for(const auto& row : ground) {
        for(const auto& value : row) {
            std::cout << std::setw(3) << value << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


//Creating 2D Vector
std::vector<std::vector<std::string>> CreateGround(){
    std::cout << "Enter size of Ground: ";
    std::cin >> size;

    std::vector<std::vector<std::string>> ground(size + 1,std::vector<std::string>(size + 1, "0"));

    //Add letters on side
    char letter = 'A';
    for (int i = 1; i < size + 1; ++i) {
        ground[i][0] = std::string(1, letter);
        letter++;
    }
    
    //Add numbers on top
    for(int j = 0; j < size + 1; j++) {
        ground[0][j] = std::to_string(j);
    }

    ShowGround(ground);
    return ground;
}


std::vector<std::vector<std::string>> Move(std::vector<std::vector<std::string>> ground) {
    std::string move;

    //Get user input
    if(Xturn == true) {
        std::cout << "X is moving to: " << std::endl;
    } 
    else {
        std::cout << "Y is moving to: " << std::endl;
    }
    std::cin >> move;

    //Convert input to integers
    int column = toupper(move[0]) - 64;
    int row = move[1] - '0';

    //Check if move is possible
    if(ground[column][row] != "0" && column <= size && row <= size) {
        std::cout << "Move: " << move << " is not viable." << std::endl;
        ShowGround(ground);
        return Move(ground);
    }
    else {
        //Determine whose turn it is by global variable
        if(Xturn == true) {
            ground[column][row] = 'x';
        }
        else {
            ground[column][row] = 'y';
        }
    }

    ShowGround(ground);
    return ground;
}


//Check for winner
bool WinCondition(std::vector<std::vector<std::string>> ground) {
    int cnt = 0;
    std::string win;

    if (Xturn) {
        win = "x";
    } else {
        win = "y";
    }

    //Check Win by Columns
    for(int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if(ground[i][j] == win) {
                cnt++;
                if(cnt == size) {
                    return true;
                }
            } else {
                cnt = 0;
                break;
            }
        }
    }

    //Check Win by Rows
    for(int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if(ground[j][i] == win) {
                cnt++;
                if(cnt == size) {
                    return true;
                }
            } else {
                cnt = 0;
                break;
            }
        }
    }


    //Check Win by Diagonals /*  \  */
    for(int i = 1; i <= size; i++) {
        if(ground[i][i] == win) {
            cnt++;
            if(cnt == size) {
                return true;
            }
        } else {
            cnt = 0;
            break;
        }
    }

    //Check Win by Diagonals /*  /  */
    int t = size;
    for(int i = 1; i <= size; i++) {
        if(ground[i][t] == win) {
            t--;
            cnt++;
            if(cnt == size) {
                return true;
            }
        } else {
            cnt = 0;
            break;
        }
    }

    return false;
}


int main() {
    int i = 0;

    std::vector<std::vector<std::string>> ground = CreateGround();

    for(i; i < size * size; i++) {
        ground = Move(ground);

        if (WinCondition(ground)) {
            break;
        };
        Xturn = !Xturn;
    }

    if(i != size * size) {
        if(Xturn) {
            std::cout << "X Won!";
        } else {
            std::cout << "Y Won!";
        }
    } else {
        std::cout << "It's a draw!";
    }

    return 0;
}