#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
using std::ifstream;
using std::string;
using std::map;
using std::remove_if;
using std::ofstream;
using std::endl;
using std::transform;
using std::stringstream;
using std::pair;
using std::vector;

void skaitymas(map<string, pair<int, vector<int>>>& zodziai, vector<string>& url);
void spausdinimas(map<string, pair<int, vector<int>>>& zodziai, vector<string>& url);

int main()
{
    vector<string> url;
    map<string, pair<int, vector<int>>> zodziai;
    skaitymas(zodziai, url);
    spausdinimas(zodziai, url);
    return 0;
}
void skaitymas(map<string, pair<int, vector<int>>>& zodziai, vector<string>& url)
{
    ifstream fd ("failas.txt");
    string k, eilute;
    stringstream eile;
    int nr = 0;

    while (getline(fd, eilute))
    {
        eile.clear();
        eile.str(eilute);
        nr ++;

        while (eile >> k)
        {
            if (k.find("www.") != string::npos || k.find("http") != string::npos)
                url.push_back(k);
            else
            {
                k.erase(remove_if(k.begin(), k.end(), [](char a)
                {
                    return !isalpha(a);
                } ), k.end());
                if (k != "")
                {
                    transform(k.begin(), k.end(), k.begin(), [](unsigned char a)
                    {
                        return tolower(a);
                    });
                    zodziai[k].first ++;
                    zodziai[k].second.push_back(nr);
                }
            }
        }
    }
    fd.close();
}

void spausdinimas(map<string, pair<int, vector<int>>>& zodziai, vector<string>& url)
{
    ofstream fr ("statistika.txt");
    fr << std::left << std::setw(17) << "Zodis" << std::setw(17)<< "Daznis" << std::setw(17) << "Eilutes" <<endl;
    for (auto k : zodziai)
        if (k.second.first > 1)
        {
            fr << endl << std::setw(17) << k.first << std::setw(17) << k.second.first;
            for (auto n : k.second.second)
                fr << n << " ";
        }
    fr << endl;
    fr << endl;
    fr << "URL adresai:";
    fr << endl;
    for (string u : url)
        fr << u << endl;

    fr.close();
}
