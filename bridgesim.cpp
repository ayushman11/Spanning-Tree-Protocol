#include<bits/stdc++.h>
using namespace std;

#include"bridgesim.h"

bool myBool_lan(LAN* lan1, LAN* lan2) {
    if((lan1->name -'A') - (lan2->name - 'A') < 0) return true;
    else return false;
}

bool myBool_bridge(bridge* bridge1, bridge* bridge2) {
    return bridge1->id < bridge2->id;
}

void simulateSTP(vector <bridge*> all_bridges,vector <LAN*> all_LANs, int trace) {
    int updates= 1;
    int time=0;

    sort(all_bridges.begin(), all_bridges.end(), myBool_bridge);

    while(updates) {
        updates=0;
        for(int i=0; i<all_bridges.size(); i++) {
        all_bridges[i]->send_to_LANs(time, trace);
        }
        time++;
        for(int i=0; i<all_bridges.size(); i++) {
            all_bridges[i]->fetch_from_LANs();
        }
        for(int i=0; i<all_LANs.size(); i++) {
            if(all_LANs[i] == NULL) continue;
            all_LANs[i]->buffer.clear();
        }
        for(int i=0; i<all_bridges.size(); i++) {
            all_bridges[i]->update_status(updates, time, trace);
            all_bridges[i]->rec_buffer.clear();
        }
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
        sort(curr_bridge->connected_LANS.begin(), curr_bridge->connected_LANS.end(), myBool_lan);
        cout<<'B'<<curr_bridge->id<<':';

        for(int j=0; j<curr_bridge->connected_LANS.size(); j++) {
            auto curr_LAN = curr_bridge->connected_LANS[j];
            cout<<" "<<curr_LAN->name<<'-'<<curr_bridge->LAN_port_status[curr_LAN->name - 'A'];
        }
        cout<<endl;
    }

    return;
}

