#include <iostream>
#include <vector>
#include <string>

#define DIM 9
#define CORP 3
#define ARIPA 2

enum Direction {
    Nord = 0,
    Sud,
    Est,
    Vest
};

class Avion {
private:
    int dir;
    int lovituri;
    int rand;
    int coloana;
    std::string nume;

public:
    Avion(int d, int lov, int r, int c, std::string name)
        : dir(d), lovituri(lov), rand(r), coloana(c), nume(name) {}

    void lovit() {
        lovituri++;
    }

    bool isDown() const {
        return lovituri >= DIM;
    }

    int getDir() const {
        return dir;
    }

    int getRand() const {
        return rand;
    }

    int getCol() const {
        return coloana;
    }

    int getLov() const {
        return lovituri;
    }

    std::string getName() const {
        return nume;
    }

    bool isInLimits(int d, int rand, int coloana) const {
        switch (d) {
            case Nord:
                return rand + CORP <= DIM && rand >= 0 && coloana + ARIPA <= DIM && coloana - ARIPA >= 0;
            case Sud:
                return rand <= DIM && rand - CORP >= 0 && coloana + ARIPA <= DIM && coloana - ARIPA >= 0;
            case Est:
                return rand + ARIPA <= DIM && rand - ARIPA >= 0 && coloana <= DIM && coloana - CORP >= 0;
            case Vest:
                return coloana + CORP <= DIM && coloana >= 0 && rand + ARIPA <= DIM && rand - ARIPA >= 0;
            default:
                std::cout << "Optiunea introdusa nu e Cunoscuta";
                return false;
        }
    }

    bool isCH(char c) const {
        return c != '*';
    }

    bool verifyAvion(char grid[][10], int d, int r, int c) const {
        switch (d) {
            case Nord:
                if (grid[r][c] == '*') return false;
                for (int i = 0; i <= ARIPA; ++i) {
                    if (!isCH(grid[r + 1][c - i]) && !isCH(grid[r + 1][c + i])) return false;
                }
                if (!isCH(grid[r + 2][c]) && !isCH(grid[r + 3][c]) && !isCH(grid[r + 3][c + 1]) && !isCH(grid[r + 3][c - 1])) return false;
                break;
            case Sud:
                for (int i = 0; i <= CORP; ++i) {
                    if (!isCH(grid[r - i][c])) return false;
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    if (!isCH(grid[r - 1][c + i]) && !isCH(grid[r - 1][c - i])) return false;
                }
                if (!isCH(grid[r - 3][c + 1]) && !isCH(grid[r - 3][c - 1])) return false;
                break;
            case Est:
                for (int i = 0; i <= CORP; ++i) {
                    if (!isCH(grid[r][c - i])) return false;
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    if (!isCH(grid[r - i][c - 1]) && !isCH(grid[r + i][c - 1])) return false;
                }
                if (!isCH(grid[r - 1][c - 3]) && !isCH(grid[r + 1][c - 3])) return false;
                break;
            case Vest:
                for (int i = 0; i <= CORP; ++i) {
                    if (!isCH(grid[r][c + i])) return false;
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    if (!isCH(grid[r - i][c + 1]) && !isCH(grid[r + i][c + 1])) return false;
                }
                if (!isCH(grid[r - 1][c + 3]) && !isCH(grid[r + 1][c + 3])) return false;
                break;
            default:
                std::cout << "directie necunoscuta";
                return false;
        }
        return true;
    }

    void getAvion(char grid[][10], int d, int r, int c) const {
        switch (d) {
            case Nord:
                grid[r][c] = '*';
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r + 1][c - i] = '*';
                    grid[r + 1][c + i] = '*';
                }
                grid[r + 2][c] = '*';
                grid[r + 3][c] = '*';
                grid[r + 3][c + 1] = '*';
                grid[r + 3][c - 1] = '*';
                break;
            case Sud:
                for (int i = 0; i <= CORP; ++i) {
                    grid[r - i][c] = '*';
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r - 1][c + i] = '*';
                    grid[r - 1][c - i] = '*';
                }
                grid[r - 3][c + 1] = '*';
                grid[r - 3][c - 1] = '*';
                break;
            case Est:
                for (int i = 0; i <= CORP; ++i) {
                    grid[r][c - i] = '*';
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r - i][c - 1] = '*';
                    grid[r + i][c - 1] = '*';
                }
                grid[r - 1][c - 3] = '*';
                grid[r + 1][c - 3] = '*';
                break;
            case Vest:
                for (int i = 0; i <= CORP; ++i) {
                    grid[r][c + i] = '*';
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r - i][c + 1] = '*';
                    grid[r + i][c + 1] = '*';
                }
                grid[r - 1][c + 3] = '*';
                grid[r + 1][c + 3] = '*';
                break;
            default:
                std::cout << "directie necunoscuta" << std::endl;
                break;
        }
    }

    bool isHit(char grid[][10], int r, int c) const {
        return grid[r][c] == '*';
    }

    void checkPlaneHit(char grid[][10], int r, int c) {
        if (r == rand && c == coloana) {
            lovituri = DIM;
            return;
        }

        switch (dir) {
            case Nord:
                for (int i = 1; i <= CORP; ++i) {
                    if (r == rand + i && c == coloana && grid[r][c] != '^') lovit();
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    if ((r == rand + 1 && c == coloana - i) || (r == rand + 1 && c == coloana + i)) {
                        if (grid[r][c] != '^') lovit();
                    }
                }
                if ((r == rand + 3 && c == coloana + 1) || (r == rand + 3 && c == coloana - 1)) {
                    if (grid[r][c] != '^') lovit();
                }
                break;
            case Sud:
                for (int i = 0; i <= CORP; ++i) {
                    if (r == rand - i && c == coloana && grid[r][c] != '^') lovit();
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    if ((r == rand - 1 && c == coloana + i) || (r == rand - 1 && c == coloana - i)) {
                        if (grid[r][c] != '^') lovit();
                    }
                }
                if ((r == rand - 3 && c == coloana + 1) || (r == rand - 3 && c == coloana - 1)) {
                    if (grid[r][c] != '^') lovit();
                }
                break;
            case Est:
                for (int i = 0; i <= CORP; ++i) {
                    if (r == rand && c == coloana - i && grid[r][c] != '^') lovit();
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    if ((r == rand - i && c == coloana - 1) || (r == rand + i && c == coloana - 1)) {
                        if (grid[r][c] != '^') lovit();
                    }
                }
                if ((r == rand - 1 && c == coloana - 3) || (r == rand + 1 && c == coloana - 3)) {
                    if (grid[r][c] != '^') lovit();
                }
                break;
            case Vest:
                for (int i = 0; i <= CORP; ++i) {
                    if (r == rand && c == coloana + i && grid[r][c] != '^') lovit();
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    if ((r == rand - i && c == coloana + 1) || (r == rand + i && c == coloana + 1)) {
                        if (grid[r][c] != '^') lovit();
                    }
                }
                if ((r == rand - 1 && c == coloana + 3) || (r == rand + 1 && c == coloana + 3)) {
                    if (grid[r][c] != '^') lovit();
                }
                break;
            default:
                std::cout << "directie necunoscuta" << std::endl;
                break;
        }
    }

    void markCorrectGuess(char grid[][10], int d, int r, int c) const {
        switch (d) {
            case Nord:
                grid[r][c] = '^';
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r + 1][c - i] = '^';
                    grid[r + 1][c + i] = '^';
                }
                grid[r + 2][c] = '^';
                grid[r + 3][c] = '^';
                grid[r + 3][c + 1] = '^';
                grid[r + 3][c - 1] = '^';
                break;
            case Sud:
                for (int i = 0; i <= CORP; ++i) {
                    grid[r - i][c] = '^';
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r - 1][c + i] = '^';
                    grid[r - 1][c - i] = '^';
                }
                grid[r - 3][c + 1] = '^';
                grid[r - 3][c - 1] = '^';
                break;
            case Est:
                for (int i = 0; i <= CORP; ++i) {
                    grid[r][c - i] = '^';
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r - i][c - 1] = '^';
                    grid[r + i][c - 1] = '^';
                }
                grid[r - 1][c - 3] = '^';
                grid[r + 1][c - 3] = '^';
                break;
            case Vest:
                for (int i = 0; i <= CORP; ++i) {
                    grid[r][c + i] = '^';
                }
                for (int i = 0; i <= ARIPA; ++i) {
                    grid[r - i][c + 1] = '^';
                    grid[r + i][c + 1] = '^';
                }
                grid[r - 1][c + 3] = '^';
                grid[r + 1][c + 3] = '^';
                break;
            default:
                std::cout << "directie necunoscuta" << std::endl;
                break;
        }
    }
};

class Game {
private:
    char p1grid[10][10];
    char guess1grid[10][10];
    char p2grid[10][10];
    char guess2grid[10][10];
    std::vector<Avion> listaAvion;
    std::vector<Avion> listaAvion2;

    void initGrid(char grid[][10]) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                grid[i][j] = '0';
            }
        }
    }

    void paintGrid(char grid[][10]) const {
        std::cout << "   1|2|3|4|5|6|7|8|9|10" << std::endl << std::endl;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == 9 && j == 0)
                    std::cout << i + 1 << " ";
                if (j == 0 && i != 9)
                    std::cout << i + 1 << "  ";
                std::cout << grid[i][j];
                if (j != 9) {
                    std::cout << "|";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void setPlane(char grid[][10], std::vector<Avion> &listaAvion) {
        int d, r, c;
        for (int i = 0; i < 3; ++i) {
            system("clear");
            paintGrid(grid);
            std::string nume;
            std::cout << "Randul si coloana capului sunt: " << std::endl;
            std::cin >> r >> c;
            r = r - 1;
            c = c - 1;
            std::cout << "Directia pentru capul avionului: 1-Nord, 2-Sud, 3-Est, 4-Vest" << std::endl;
            std::cin >> d;
            d = d - 1;
            std::cout << "Numele avionului" << std::endl;
            std::cin >> nume;
            Avion Obj(d, 0, r, c, nume);
            if (Obj.isInLimits(Obj.getDir(), Obj.getRand(), Obj.getCol())) {
                if (Obj.verifyAvion(grid, Obj.getDir(), Obj.getRand(), Obj.getCol())) {
                    Obj.getAvion(grid, Obj.getDir(), Obj.getRand(), Obj.getCol());
                    listaAvion.push_back(Obj);
                    system("clear");
                } else {
                    std::cout << std::endl << "Avionul se intercaleaza cu alt avion. Introduceti alte coordonate sau directie" << std::endl;
                    i--;
                }
            } else {
                std::cout << "Avionul nu incape" << std::endl;
                i--;
            }
        }
        paintGrid(grid);
    }

    void setPlanes2p(char grid1[][10], char grid2[][10], std::vector<Avion> &listaAvion, std::vector<Avion> &listaAvion2) {
        system("clear");
        std::cout << "Jucatorul 1, introdu coordonatele avioanelor" << std::endl;
        system("sleep 2");
        system("clear");
        setPlane(grid1, listaAvion);
        std::cout << "Toate avioanele pentru jucatorul 1 au fost inregistrate." << std::endl;
        system("sleep 5");
        system("clear");
        std::cout << "Urmeaza jucatorul 2 dupa stergerea afisajului..." << std::endl;
        system("sleep 4");
        system("clear");
        std::cout << "Jucatorul 2, introdu coordonatele avioanelor" << std::endl << std::endl;
        system("sleep 2");
        system("clear");
        setPlane(grid2, listaAvion2);
        system("clear");
        paintGrid(grid2);
        std::cout << "Toate datele au fost introduse" << std::endl;
        system("sleep 2");
        system("clear");
    }

    void updateGrid(char grid[][10], int r, int c, int cond) {
        if (cond == 0)
            grid[r][c] = '1';
        else
            grid[r][c] = '^';
    }

    void hitGuess(char grid[][10], char ggrid[][10], int r, int c, std::vector<Avion> &listaAvion) {
        bool ok = false, doborat = false;
        for (int i = 0; i < listaAvion.size(); ++i) {
            if (listaAvion[i].isHit(grid, r, c)) {
                listaAvion[i].checkPlaneHit(ggrid, r, c);
                if (listaAvion[i].isDown()) {
                    doborat = true;
                    std::cout << "Ati doborat avionul " << listaAvion[i].getName() << std::endl << std::endl;
                    listaAvion[i].markCorrectGuess(ggrid, listaAvion[i].getDir(), listaAvion[i].getRand(), listaAvion[i].getCol());
                    listaAvion.erase(listaAvion.begin() + i);
                    i--;
                }
                updateGrid(ggrid, r, c, 1);
                ok = true;
            }
        }
        if (!ok) {
            updateGrid(ggrid, r, c, 0);
            system("clear");
            std::cout << "Ratare" << std::endl;
        } else if (!doborat && ok) {
            system("clear");
            std::cout << "Lovit!" << std::endl;
        }
    }

    void gameStart() {
        system("sleep 2");
        system("clear");
        for (int i = 3; i > 0; --i) {
            std::cout << "Jocul va incepe in " << i << std::endl;
            system("sleep 1.5");
            system("clear");
        }
    }

    bool isAlreadyHit(char grid[][10], int r, int c) const {
        return grid[r][c] != '0';
    }

    void gameLoop(char grid1[][10], char grid2[][10], std::vector<Avion> &listaAvion, std::vector<Avion> &listaAvion2, char g1grid[][10], char g2grid[][10]) {
        while (listaAvion.size() && listaAvion2.size()) {
            paintGrid(g1grid);
            std::cout << "J.1,introduceti casuta pe care doriti sa o loviti" << std::endl;
            int r, c;
            std::cin >> r >> c;
            system("clear");
            if (r <= 10 && c <= 10) {
                r = r - 1;
                c = c - 1;
                if (!isAlreadyHit(g1grid, r, c)) {
                    hitGuess(grid2, g1grid, r, c, listaAvion2);
                    paintGrid(g1grid);
                    system("sleep 4");
                    system("clear");
                } else {
                    std::cout << "Coordonatele selectate au fost deja lovite" << std::endl;
                    system("sleep 1");
                    std::cout << "Ati irosit o mutare" << std::endl;
                    system("sleep 1.5");
                    system("clear");
                }
            } else {
                std::cout << "coordonatele introduse nu exista" << std::endl;
                system("sleep 2");
                system("clear");
            }
            paintGrid(g2grid);
            std::cout << "J.2,introduceti casuta pe care doriti sa o loviti" << std::endl;
            std::cin >> r >> c;
            system("clear");
            if (r <= 10 && c <= 10) {
                r = r - 1;
                c = c - 1;
                if (!isAlreadyHit(g2grid, r, c)) {
                    hitGuess(grid1, g2grid, r, c, listaAvion);
                    paintGrid(g2grid);
                    system("sleep 4");
                    system("clear");
                } else {
                    std::cout << "Coordonatele selectate au fost deja lovite" << std::endl;
                    system("sleep 1");
                    std::cout << "Ati irosit o mutare" << std::endl;
                    system("sleep 1.5");
                    system("clear");
                }
            } else {
                std::cout << "coordonatele introduse nu exista" << std::endl;
                system("sleep 2");
                system("clear");
            }
        }
        if (listaAvion.size() < listaAvion2.size())
            std::cout << "Jucatorul 2 a castigat";
        else if (listaAvion.size() > listaAvion2.size())
            std::cout << "Jucatorul 1 a castigat";
        else
            std::cout << "Remiza";
    }

public:
    Game() {
        initGrid(p1grid);
        initGrid(p2grid);
        initGrid(guess1grid);
        initGrid(guess2grid);
    }

    void start() {
        char play;
        std::cout << "Apasa c pentru a incepe jocul" << std::endl;
        std::cin >> play;
        while (play != 'c') {
            std::cin >> play;
        }
        system("clear");
        int players;
        std::cout << "Introduceti numarul jucatorilor(1/2)" << std::endl;
        std::cin >> players;
        switch (players) {
            case 1:
                //setPlanes1p(p1grid, listaAvion);
                gameStart();
                gameLoop(p1grid, p2grid, listaAvion, listaAvion2, guess1grid, guess2grid);
                break;
            case 2:
                setPlanes2p(p1grid, p2grid, listaAvion, listaAvion2);
                gameStart();
                gameLoop(p1grid, p2grid, listaAvion, listaAvion2, guess1grid, guess2grid);
                break;
            default:
                std::cout << "Numar de jucatori necunoscut";
                break;
        }
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}