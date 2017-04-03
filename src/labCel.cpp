#include "labCel.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

//Hoitaa yksitt‰isen huoneen olemuksen, eli ovet ja merkki jolla se esitet‰‰n. Merkki on pitk‰lti j‰‰nne alkuper‰isest‰ tarkoituksesta...
using namespace std;

//oletus konstruktori. T‰ysin sattumanvaraninen huone (ovien osalta)
labCel::labCel()
{

    n = generateRandomBool();
    e = generateRandomBool();
    s = generateRandomBool();
    w = generateRandomBool();
    glyph = 63;
    sarja = -1;
}

//konstruktori jossa osa ovista mahdollisesti tuntemattomia. Voidaan siis luoda huone jossa osa ovista on asetettu ja loput arvotaan. katso generateFromInt()
//argumentit vastaavat ovien tiloja niin ett‰ un vastaa pohkoista ovea, en it‰ist‰ jne
labCel::labCel(int un, int ue, int us, int uw)
{
    n = generateFromInt(un);
    e = generateFromInt(ue);
    s = generateFromInt(us);
    w = generateFromInt(uw);
    glyph = 63;
    sarja =-1;
}

//luo bool arvon annetun intin pohjalta. false jos target == 0, true jos 1 ja randomi jos muuta.
bool labCel::generateFromInt(int target)
{
    if(target == 0) return false;
    else if(target == 1) return true;
    else return generateRandomBool();
}

char labCel::getGlyph()
{
    return glyph;
}

//Asettaa huoneen ikonin. Tarkoitettu l‰hinn‰ mappaamis komentoa varten. Glyphi lasketaan huoneen ovista
void labCel::setGlyph()
{
    int luku = 8*n + 4*e + 2*s + 1*w;
    switch (luku)
    {
    case 0:
    glyph = 178;
    break;
    case 1:
    glyph = 180;
    break;
    case 2:
    glyph = 194;
    break;
    case 3:
    glyph = 187;
    break;
    case 4:
    glyph = 195;
    break;
    case 5:
    glyph = 205;
    break;
    case 6:
    glyph = 201;
    break;
    case 7:
    glyph = 203;
    break;
    case 8:
    glyph = 193;
    break;
    case 9:
    glyph = 188;
    break;
    case 10:
    glyph = 186;
    break;
    case 11:
    glyph = 185;
    break;
    case 12:
    glyph = 200;
    break;
    case 13:
    glyph = 202;
    break;
    case 14:
    glyph = 204;
    break;
    case 15:
    glyph = 206;
    break;

    }
}

//arpoo sattumanvaraisen bool arvon
bool labCel::generateRandomBool()
{

    int randomval = rand() % 2;
    if (randomval == 1) return true;
    else return false;
}

//konstruktori jossa annetaan ovien arvot... hiukan turha ehk‰ kun saman voi tehd‰ labCel(int,int,int,int) konstruktorilla. Pid‰np‰ nyt kuitenkin viel‰ sen t‰ss‰.
labCel::labCel(bool un, bool ue, bool us, bool uw)
{
    n = un;
    e = ue;
    s = us;
    w = uw;
    glyph = 63;
    sarja = -1;

}

int labCel::getSarja()
{
    return sarja;
}

void labCel::setSarja(int x)
{
    sarja = x;
}

//palauttaa vektorin jossa 0 alkio vastaa pohjoisen oven tilaa, 1 it‰isen, 2 etel‰isen ja 3 l‰ntisen oven tilaa
vector<bool> labCel::getExits()
{
    vector<bool> palautus;
    palautus.push_back(n);
    palautus.push_back(e);
    palautus.push_back(s);
    palautus.push_back(w);
    return palautus;
}

//vaihtaa pyydetyn oven tilan falsesta trueksi tai toisinp‰in. 0 vastaa pohjoista, 1 it‰sit‰, 2 etel‰ist‰ ja 3 l‰ntist‰ ovea
void labCel::switchExit(int no)
{
    switch (no)
    {
    case 0:
        n = !n;
        break;
    case 1:
        e = !e;
        break;
    case 2:
        s = !s;
        break;
    case 3:
        w = !w;
        break;
    }
}

labCel::~labCel()
{
    //dtor
}
