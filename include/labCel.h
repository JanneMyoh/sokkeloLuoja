#ifndef LABCEL_H
#define LABCEL_H
#include <vector>


class labCel
{
    public:
        labCel();
        labCel(bool, bool, bool, bool);
        labCel(int, int, int, int);
        virtual ~labCel();
        std::vector<bool> getExits();
        char getGlyph();
        void setSarja(int);
        int getSarja();
        void setGlyph();
        void switchExit(int n);
    protected:
    private:
        bool n; //pohjoinen ovi
        bool s; //etel‰inen ovi
        bool e; //it‰inen ovi
        bool w; //l‰ntinen ovi
        bool generateRandomBool();
        char glyph; //merkki jolla huonetta kuvataan
        bool generateFromInt(int);
        int sarja; //k‰yt‰v‰ j‰rjestelm‰ johon huone kuuluu. K‰ytet‰‰n vain labyrintti‰ luodessa.

};

#endif // LABCEL_H
