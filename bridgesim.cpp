#include<bits/stdc++.h>
using namespace std;

#include"bridgesim.h"

// void gen_trace(LAN* SENDING_LAN, bridge* SENDING_BRIDGE, int time) {

//     // send trace message to all connected bridges except the sending bridge
//     vector <bridge*> adj_bridges= SENDING_LAN->connected_bridges;
//     for(int i=0; i<adj_bridges.size(); i++) {
//         if (adj_bridges[i] == SENDING_BRIDGE) continue;

        
//     }
// }

// void transmitPackets(LAN* SENDING_LAN,  int time) {
//      auto msg_buffer= SENDING_LAN->buffer;
//      auto conn_bridges= SENDING_LAN->connected_bridges;
//     for(int i=0; i<msg_buffer.size(); i++) {
//         for(int j=0; j<conn_bridges.size(); j++) {
//             if(conn_bridges[j] == msg_buffer[i].sending_bridge) continue;
//             else if(conn_bridges[j]->LAN_port_status[SENDING_LAN->name - 'A'] == "NP") continue;
//             else {
//                 conn_bridges[j]->update_status(msg_buffer[i], SENDING_LAN);
//             }
//         }
//     }
// }

