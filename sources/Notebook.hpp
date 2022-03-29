#include<string>
#include "Direction.hpp"
#include <unordered_map>
//#include "Notebook.cpp"

namespace ariel {
    class Notebook
    {
    private:
        std::unordered_map<std::string, char> note;
        int rowUpLim;
        int rowDownLim;
    public:
        Notebook();
        ~Notebook();
        void write(int page, int row, int col, ariel::Direction dir, std::string str);
        std::string read(int page, int row, int col, ariel::Direction dir, int length);
        void erase(int page, int row, int col, ariel::Direction dir, int length);
        void show(int page);
        int illegal(int page, int row, int col, ariel::Direction dir, const std::string &str);
    };
}
