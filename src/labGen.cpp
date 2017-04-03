#include "labGen.h"
#include "labCel.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

//liitt‰‰ yksitt‰iset huoneet kokonaisuudeksi. Suurin tyˆ labyrintti‰ luodessa, muuten l‰hinn‰ s‰ilytys paikka huoneille
vector<vector<labCel> > lab;

labGen::labGen()
{
    labGen(10);
}

//konstruktori jossa m‰‰ritel‰‰n labyrintin koko. Labyrintti aina neliˆ
labGen::labGen(int n)
{

    generateLab(n);
    findSystems();
    unify();
    setGlyphs();
}

labGen::~labGen()
{
    //dtor
}

//maalaa k‰yt‰v‰ kokonaisuuden annetulla arvolla, ie: asettaa jokaisen huoneen, johonka p‰‰see huoneesta (i,j) , sarja arvoksi n. fstTier k‰ytet‰‰n kertomaan onko kutsu iteratiivinen vai tuleeko se metodin ulkopuolelta. K‰ytet‰‰n vain merkkaamaan t‰ysin umpinaiset huoneet arvolla 0.
void labGen::propa(int i, int j, int n , bool fstTier)
{
    if(lab.at(i).at(j)->getSarja() == n) return; //katotaan onko k‰yty jo solussa
    vector<bool> exits = lab.at(i).at(j)->getExits();
    if(fstTier){ //katsotaan ett‰ onko solun kaikku ulosp‰‰syt falseja
    bool blok = false;
    for(int l = 0; l < exits.size(); l++)
    {
        blok = blok || exits.at(l);
    }
    if(!blok) {lab.at(i).at(j)->setSarja(0); return;}
    }
    lab.at(i).at(j)->setSarja(n);
    if(exits.at(0)) propa(i-1, j, n, false);
    if(exits.at(1)) propa(i, j+1, n, false);
    if(exits.at(2)) propa(i+1, j, n, false);
    if(exits.at(3)) propa(i, j-1, n, false);
}

//generoi raaka labyrintin, jossa jokainen solu katsoo l‰nsi ja pohjois puolella olevaa solua ja asettaa l‰nsi ja pohjois oven niiden mukaan niin ett‰ k‰yt‰v‰ s‰ilyy ja it‰ ja etel‰ oven sattuman varaiseksi. Tuloksena on labyrintti jossa useita k‰yt‰v‰ j‰rjestelmi‰
void labGen::generateLab(int no)
{
    srand(time(NULL));
    for(int i = 0; i < no ; i++)
    {
        vector<labCel*> s;
        lab.push_back(s);
        for(int j = 0; j < no; j++)
        {
            int n;
            int e;
            int s;
            int w;
            if(i == 0 || !lab.at(i-1).at(j)->getExits().at(2)) n=0;
            else n=1;
            if(j == no-1) e=0;
            else e=2;
            if(i == no-1) s=0;
            else s=2;
            if(j == 0 || !lab.at(i).at(j-1)->getExits().at(1)) w=0;
            else w=1;
            lab.at(i).push_back(new labCel(n,e,s,w));
        }
    }

}
//etsii eri k‰yt‰v‰ j‰rjestelm‰t, eli sellaiset alueet josta ei p‰‰se labyrintin muihinb osiin
void labGen::findSystems()
{
    int n = 1;
    for(int i = 0; i < lab.size(); i++)
    {
        for(int j = 0; j < lab.at(i).size(); j++)
        {
            if(lab.at(i).at(j)->getSarja() < 0) {propa(i,j,n,true);n++;}
        }
    }
}
//yhdist‰‰ labyrintin k‰yt‰v‰ kokonaisuudet yhdeksi k‰yt‰v‰ kokonaisuudeksi, ts mist‰ tahaansa solusta on mahdollista lˆyt‰‰ tie mihink‰ tahaansa muuhun soluun. Paitsi tolppiin, eli soluihin mitk‰ arvottiin t‰ysin umpinaisiksi.
void labGen::unify()
{
    for(int i = 0; i < lab.size(); i++)
    {
        for(int j = 0; j < lab.at(i).size(); j++)
        {
            //Katsotaan mit‰ on edess‰
            if(j < lab.at(i).size()-1 && lab.at(i).at(j)->getSarja()!= 0 && lab.at(i).at(j+1)->getSarja()!= 0)
            {
                //tutkitaan onko i,j ja i,j+1 samassa sarjassa
                if(lab.at(i).at(j)->getSarja() != lab.at(i).at(j+1)->getSarja())
                { //vaihdetaan i,j ja i,j+1 samaan sarjaan
                    lab.at(i).at(j)->switchExit(1);
                    lab.at(i).at(j+1)->switchExit(3);
                    if(lab.at(i).at(j)->getSarja() > lab.at(i).at(j+1)->getSarja())
                    {
                        propa(i, j, lab.at(i).at(j+1)->getSarja(), false);
                    }else{
                        propa(i, j+1, lab.at(i).at(j)->getSarja(), false);
                    }
                }
            }
            //Katsotaan mit‰ on alla
            if(i < lab.size()-1 && lab.at(i).at(j)->getSarja()!= 0 && lab.at(i+1).at(j)->getSarja()!= 0)
            {
                //tutkitaan onko i,j ja i+1,j samassa sarjassa
                if(lab.at(i).at(j)->getSarja() != lab.at(i+1).at(j)->getSarja())
                { //vaihdetaan i+1,j ja i+1,j samaan sarjaan
                    lab.at(i).at(j)->switchExit(2);
                    lab.at(i+1).at(j)->switchExit(0);
                    if(lab.at(i).at(j)->getSarja() > lab.at(i+1).at(j)->getSarja())
                    {
                        propa(i, j, lab.at(i+1).at(j)->getSarja(), false);
                    }else{
                        propa(i+1, j, lab.at(i).at(j)->getSarja(), false);
                    }
                }
            }
        }
    }
}
//k‰skee jokaisen solun haistella itsellens‰ glyphi.
void labGen::setGlyphs()
{
    for(int i = 0; i < lab.size(); i++)
    {
        for(int j = 0; j < lab.at(i).size(); j++)
        {
            lab.at(i).at(j)->setGlyph();
        }
    }
}

//kertoo pyydetyn solun ulosmenojen tilan
vector<bool> labGen::getExits(int i, int j)
{
    vector<bool> temp = lab.at(i).at(j)->getExits();
    return temp;
}

char labGen::getGlyph(int i, int j)
{
    return lab.at(i).at(j)->getGlyph();
}
