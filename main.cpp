#include<bits/stdc++.h>
using namespace std;
#include "bridgesim.h"

vector <string> split_input(string str) {
    stringstream s(str);
    string word;

    vector <string> ind_words;

    while(s >> word) ind_words.push_back(word);
    return ind_words;
}

int main()
{
    int trace; cin>>trace;
    int num; cin>>num;
    cin >> ws;
    vector <bridge*> all_bridges;
    vector <LAN*> all_LANs(26, NULL);

    for(int i=0; i<num; i++)
    {
        string s;
        getline(cin,s);
        vector <LAN*> conn_LANs;
        auto data = split_input(s);

        for(int i=1; i<data.size(); i++) {
            if(all_LANs[data[i][0] - 'A'] == NULL) {
                vector <bridge*> conn_bridges;
                LAN* lan = new LAN(data[i][0], conn_bridges);
                all_LANs[data[i][0] - 'A'] = lan;
            }
            conn_LANs.push_back(all_LANs[data[i][0] - 'A']);
        }
        string str= data[0];
        int pos= str.find(':');
        int bridge_id = str.substr(1,pos-1)[0] - '0';

        bridge* b = new bridge(bridge_id, conn_LANs);

        for(int j=0; j<data.size()-1; j++) {
            b->connected_LANS[j]->connected_bridges.push_back(b);
        }
        all_bridges.push_back(b);
    }

    simulateSTP(all_bridges, all_LANs, trace);

}