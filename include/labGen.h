#ifndef LABGEN_H
#define LABGEN_H
#include <vector>

class labCel;
class labGen
{
    public:
        labGen();
        labGen(int);
        virtual ~labGen();
        char getGlyph(int,int);
        std::vector<bool> getExits(int,int);
    protected:
    private:
    std::vector< std::vector<labCel *> > lab; //labyrintin huoneet
    void propa(int, int, int, bool);
    void generateLab(int);
    void findSystems();
    void unify();
    void setGlyphs();

};

#endif // LABGEN_H
