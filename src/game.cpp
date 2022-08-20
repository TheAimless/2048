#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>

std::array<int, 4> merge(std::array<int, 4> v);
std::array<int, 4> move(std::array<int, 4> v);

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr1(0, 15), distr2(0, 7);
    std::array<std::array<int, 4>, 4> board = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};

    int start1 = distr1(gen), start2 = distr1(gen);
    std::cout << "start1 = " << start1 << "\nstart2 = " << start2 << std::endl;
    int randnum1 = distr2(gen), randnum2 = distr2(gen);
    while (start2 == start1) start2 = distr1(gen);
    board[start1 / 4][start1 % 4] = (randnum1 < 2 ? 4 : 2);
    board[start2 / 4][start2 % 4] = (randnum2 < 2 ? 4 : 2);

    while (true){
        for (int i = 0; i < 4; ++i){
            for (int j = 0; j < 4; ++j){
                std::cout << board[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::string op;
        std::cout << "Type: ";
        std::cin >> op;

        auto temp = board;
        if (op == "w"){
            for (int j = 0; j < 4; ++j){
                std::array<int, 4> ttmp;
                for (int i = 0; i < 4; ++i){
                    ttmp[i] = temp[i][j];
                }
                std::reverse(ttmp.begin(), ttmp.end());
                ttmp = merge(ttmp);
                ttmp = move(ttmp);
                std::reverse(ttmp.begin(), ttmp.end());
                for (int i = 0; i < 4; ++i){
                    temp[i][j] = ttmp[i];
                }
            }
        }
        else if (op == "s"){
            for (int j = 0; j < 4; ++j){
                std::array<int, 4> ttmp;
                for (int i = 0; i < 4; ++i){
                    ttmp[i] = temp[i][j];
                }
                ttmp = merge(ttmp);
                ttmp = move(ttmp);
                for (int i = 0; i < 4; ++i){
                    temp[i][j] = ttmp[i];
                }
            }   
        }
        else if (op == "a"){
            for (int i = 0; i < 4; ++i){
                std::reverse(temp[i].begin(), temp[i].end());
                temp[i] = merge(temp[i]);
                temp[i] = move(temp[i]);
                std::reverse(temp[i].begin(), temp[i].end());
            }
        }
        else if (op == "d"){
            for (int i = 0; i < 4; ++i){
                temp[i] = merge(temp[i]);
                temp[i] = move(temp[i]);
            }
        }
        if (temp != board){
            board = temp;
            std::vector<std::pair<int, int>> tmp;
            for (int i = 0; i < 4; ++i){
                for (int j = 0; j < 4; ++j){
                    if (board[i][j] == 0){
                        tmp.push_back(std::make_pair(i, j));
                    }
                }
            }
            std::uniform_int_distribution<> idx(0, (int) tmp.size() - 1);
            auto p = tmp[idx(gen)];
            int x = p.first, y = p.second;
            board[x][y] = (distr2(gen) < 2 ? 4 : 2);
        }
    }
}

std::array<int, 4> merge(std::array<int, 4> v){
    auto vv = v;
    if (vv[3] != 0){
        if (vv[2] == vv[3]){
            vv[3] += vv[2];
            vv[2] = 0;
        }
        else if (vv[2] == 0 && vv[1] == vv[3]){
            vv[3] += vv[1];
            vv[1] = 0;
        }
        else if (vv[2] == 0 && vv[1] == 0 && vv[0] == vv[3]){
            vv[3] += vv[0];
            vv[0] = 0;   
        }
    }
    if (vv[2] != 0){
        if (vv[2] == vv[1]){
            vv[2] += vv[1];
            vv[1] = 0;
        }
        else if (vv[1] == 0 && vv[0] == vv[2]){
            vv[2] += vv[0];
            vv[0] = 0;
        }
    }
    if (vv[1] != 0){
        if (vv[1] == vv[0]){
            vv[1] += vv[0];
            vv[0] = 0;
        }
    }
    return vv;
}

std::array<int, 4> move(std::array<int, 4> v){
    auto vv = v;
    for (int i = 3; i >= 0; --i){
        if (vv[i] == 0) continue;
        else{
            for (int j = 3; j > i; --j){
                if (vv[j] == 0){
                    vv[j] = vv[i];
                    vv[i] = 0;
                }
            }
        }
    }
    return vv;
}