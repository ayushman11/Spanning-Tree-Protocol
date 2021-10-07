#include<bits/stdc++.h>
using namespace std;
#include "bridge.h"

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
    int num_bridges; cin>>num_bridges;
    cin >> ws;
    vector <bridge*> all_bridges;
    vector <LAN*> all_LANs(26);
    vector <bool> isLAN(26, false);

    for(int i=0; i<num_bridges; i++)
    {
        string s;
        getline(cin,s);
        vector <LAN*> conn_LANs;
        auto data = split_input(s);

        // cout<<data[0]<<endl;
        for(int i=1; i<data.size(); i++) {
            if(!(isLAN[data[i][0] - 'A'])) {
                // cout<<"created new LAN"<<endl;
                isLAN[data[i][0] - 'A']=1;
                vector <bridge*> conn_bridges;
                LAN* lan = new LAN(data[i][0], conn_bridges);
                all_LANs[data[i][0] - 'A'] = lan;
            }
            // else cout<<"Lan already exists"<<endl;
            conn_LANs.push_back(all_LANs[data[i][0] - 'A']);
        }
        string str= data[0];
        int pos= str.find(':');
        int bridge_id = str.substr(1,pos-1)[0] - '0';
        // cout<<bridge_id<<endl;

        bridge* b = new bridge(bridge_id, conn_LANs);

        for(int j=1; j<data.size(); j++) {
            b->connected_LANS[j]->connected_bridges.push_back(b);
        }

        all_bridges.push_back(b);
    }

    // for(int i=0; i<all_bridges.size(); i++) {
    //     cout<<'B'<<all_bridges[i]->id<<": ";
    //     for(int j=0; j<all_bridges[i]->connected_LANS.size(); j++) cout<<all_bridges[i]->connected_LANS[j]->name<<"-"<<all_bridges[i]->LAN_port_status[all_bridges[i]->connected_LANS[j]->name - 'A']<<" ";
    //     cout<<endl;
    // }
}