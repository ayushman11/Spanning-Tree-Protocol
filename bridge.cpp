#include<bits/stdc++.h>
using namespace std;

#include "bridge.h"

bridge::bridge(int ID, vector <LAN*> CONNECTED_LANS) {
    id = ID;
    connected_LANS = CONNECTED_LANS;
    vector <string> v(26,"");
    for(int i=0; i<connected_LANS.size(); i++) {
        v[connected_LANS[i]->name - 'A']="DP";
    }
    LAN_port_status = v;

    root_bridge= this;
    root_dist = 0;

    designated_LAN= NULL;
}

void bridge::update_status(int &updates, int time, int trace){

    for(int i=0; i<rec_buffer.size(); i++) {
        auto rec_trace = rec_buffer[i].first;
        auto sender_LAN = rec_buffer[i].second;
        if(rec_trace.sending_bridge == this) {
            continue;
        }
        if(trace) {
            cout<<time<<" r B"<<this->id<<" ";
            rec_trace.disp_msg();
        }
        
        if(rec_trace.root_bridge->id < root_bridge->id ) {

            root_bridge = rec_trace.root_bridge;
            root_dist = rec_trace.dist + 1;
            if(designated_LAN==NULL) designated_LAN = sender_LAN; 
            LAN_port_status[designated_LAN->name - 'A']="DP";
            LAN_port_status[sender_LAN->name - 'A']="RP";
            designated_LAN = sender_LAN;
            designated_bridge = rec_trace.sending_bridge;
            updates++;

        } else if (rec_trace.root_bridge->id == root_bridge->id) {

            if(rec_trace.dist + 1 < root_dist) {

                root_bridge = rec_trace.root_bridge;
                root_dist = rec_trace.dist + 1;
                LAN_port_status[designated_LAN->name - 'A']="NP";
                LAN_port_status[sender_LAN->name - 'A']="RP";
                designated_LAN = sender_LAN;
                designated_bridge = rec_trace.sending_bridge;
                updates++;
            } else if (rec_trace.dist + 1 == root_dist) {

                if(rec_trace.sending_bridge->id == designated_bridge->id && sender_LAN == designated_LAN) continue;
                else if(rec_trace.sending_bridge->id == designated_bridge->id) {
                    if(sender_LAN->name - designated_LAN->name < 0) {
                        LAN_port_status[designated_LAN->name - 'A']="NP";
                        LAN_port_status[sender_LAN->name - 'A']="RP";
                        designated_LAN = sender_LAN;
                        updates++;
                    } else {
                        LAN_port_status[sender_LAN->name - 'A']="NP";
                        updates++;
                    }
                    continue;
                }

                if(rec_trace.sending_bridge->id < designated_bridge->id) {
                    root_bridge = rec_trace.root_bridge;
                    root_dist = rec_trace.dist + 1;
                    LAN_port_status[designated_LAN->name - 'A']="NP";
                    LAN_port_status[sender_LAN->name - 'A']="RP";
                    designated_LAN = sender_LAN;
                    designated_bridge = rec_trace.sending_bridge;
                    updates++;
                } else {
                    LAN_port_status[sender_LAN->name - 'A']="NP";
                    updates++;
                }
            } 
            else {
                if(rec_trace.sending_bridge->LAN_port_status[sender_LAN->name - 'A'] == "DP") {
                    if(rec_trace.sending_bridge->id < this->id) {
                        LAN_port_status[sender_LAN->name - 'A']="NP";
                        updates++;
                    } else {
                        rec_trace.sending_bridge->LAN_port_status[sender_LAN->name - 'A'] = "NP";
                        updates++;
                    }
                }
            }

        } 
    }

    return;
}


LAN::LAN(char NAME, vector <bridge*> CONNECTED_BRIDGES) {
    name = NAME;
    connected_bridges = CONNECTED_BRIDGES;
    designated_bridge_id = 0;
}


trace_message::trace_message(bridge* ROOT, int DIST, bridge* SENDING_BRIDGE){
    root_bridge = ROOT;
    dist = DIST;
    sending_bridge = SENDING_BRIDGE;
}

void trace_message::disp_msg() {
    cout<<"(B"<<root_bridge->id<<','<<dist<<",B"<<sending_bridge->id<<')'<<endl;
}

void bridge::send_to_LANs(int time, int trace) {
    trace_message m(root_bridge, root_dist, this);

    for(int i=0; i<connected_LANS.size(); i++) {
        if(LAN_port_status[connected_LANS[i]->name - 'A'] != "NP") {
            auto curr_LAN = connected_LANS[i];
            curr_LAN->buffer.push_back(m);
            if(trace) {
                cout<<time<<" s B"<<this->id<<" ";
                m.disp_msg();
            }
        }
    }

    return;
}

void bridge::fetch_from_LANs() {
    for(int i=0; i<connected_LANS.size(); i++) {
        if(LAN_port_status[connected_LANS[i]->name -'A'] !="NP") {
            for(int j=0; j<connected_LANS[i]->buffer.size(); j++) {
                rec_buffer.push_back(make_pair(connected_LANS[i]->buffer[j], connected_LANS[i]));
            }
        }
    }
}