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
    vector <LAN*> all_LANs(26, NULL);
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
            // cout<<all_LANs[data[i][0] - 'A']->name<<" ";
        }
        string str= data[0];
        int pos= str.find(':');
        int bridge_id = str.substr(1,pos-1)[0] - '0';
        // cout<<bridge_id<<endl;

        bridge* b = new bridge(bridge_id, conn_LANs);
        // cout<<b->id<<endl;

        for(int j=0; j<data.size()-1; j++) {
            b->connected_LANS[j]->connected_bridges.push_back(b);
        }
        all_bridges.push_back(b);
    }

    // for(int i=0; i<all_bridges.size(); i++) {
    //     all_bridges[i]->send_to_LANs();
    // }
    // for(int i=0; i<all_bridges.size(); i++) {
    //     all_bridges[i]->fetch_from_LANs();
    // }
    // for(int i=0; i<all_LANs.size(); i++) {
    //     if(all_LANs[i] == NULL) continue;
    //     all_LANs[i]->buffer.clear();
    //     // cout<<all_LANs[i]->name<<": "<<endl;
    //     // for(int k=0; k<all_LANs[i]->buffer.size(); k++) {
    //     //     all_LANs[i]->buffer[k].disp_msg();
    //     // }
    // }
    // for(int i=0; i<all_bridges.size(); i++) {
    //     all_bridges[i]->update_status();
    //     all_bridges[i]->rec_buffer.clear();
    //     // cout<<'B'<<all_bridges[i]->id<<": "<<endl;
    //     // for(int k=0; k<all_bridges[i]->rec_buffer.size(); k++) {
    //     //     all_bridges[i]->rec_buffer[k].first.disp_msg();
    //     // }
    // }
    // for(int k=0; k<all_bridges.size(); k++) {
    // cout<<'B'<<all_bridges[k]->id<<": ("<<all_bridges[k]->root_bridge->id<<','<<all_bridges[k]->root_dist<<')'<<endl;
    // }


    int updates= 1;
    int time=0;

    while(updates) {
        updates=0;
        // cout<<updates<<endl;
        for(int i=0; i<all_bridges.size(); i++) {
        all_bridges[i]->send_to_LANs(time);
        }
        time++;
        for(int i=0; i<all_bridges.size(); i++) {
            all_bridges[i]->fetch_from_LANs();
        }
        for(int i=0; i<all_LANs.size(); i++) {
            if(all_LANs[i] == NULL) continue;
            all_LANs[i]->buffer.clear();
            // cout<<all_LANs[i]->name<<": "<<endl;
            // for(int k=0; k<all_LANs[i]->buffer.size(); k++) {
            //     all_LANs[i]->buffer[k].disp_msg();
            // }
        }
        for(int i=0; i<all_bridges.size(); i++) {
            all_bridges[i]->update_status(updates, time);
            all_bridges[i]->rec_buffer.clear();
            // cout<<'B'<<all_bridges[i]->id<<": "<<endl;
            // for(int k=0; k<all_bridges[i]->rec_buffer.size(); k++) {
            //     all_bridges[i]->rec_buffer[k].first.disp_msg();
            // }
        }
        // for(int k=0; k<all_bridges.size(); k++) {
        // cout<<'B'<<all_bridges[k]->id<<": ("<<all_bridges[k]->root_bridge->id<<','<<all_bridges[k]->root_dist<<')'<<endl;
        // }
        // cout<<updates<<endl;
    }

    for(int i=0; i<all_bridges.size(); i++) {
        auto curr_bridge = all_bridges[i];
        int count=0;
        for(int j=0; j<curr_bridge->connected_LANS.size(); j++) {
            auto curr_LAN = curr_bridge->connected_LANS[j];
            if(curr_bridge->LAN_port_status[curr_LAN->name - 'A'] == "DP") count++;
        }
        if(!count) curr_bridge->LAN_port_status[curr_bridge->designated_LAN->name - 'A']="NP";
    }

    for(int i=0; i<all_bridges.size(); i++) {
        auto curr_bridge = all_bridges[i];
        cout<<'B'<<curr_bridge->id<<':';

        for(int j=0; j<curr_bridge->connected_LANS.size(); j++) {
            auto curr_LAN = curr_bridge->connected_LANS[j];
            cout<<" "<<curr_LAN->name<<'-'<<curr_bridge->LAN_port_status[curr_LAN->name - 'A'];
        }
        cout<<endl;
    }
}