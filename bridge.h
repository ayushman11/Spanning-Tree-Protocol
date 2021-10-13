#include<bits/stdc++.h>
using namespace std;

class bridge;
class LAN;
class trace_message;

class bridge {
    private:

    public:

    int id; // bridge id

    // LAN information
    vector <LAN*> connected_LANS; 
    vector <string> LAN_port_status;

    // what bridge thinks
    bridge* root_bridge;
    int root_dist;
    LAN* designated_LAN;
    bridge* designated_bridge;

    // received message buffer
    vector <pair<trace_message, LAN*>> rec_buffer;

    bridge(int ID, vector <LAN*> CONNECTED_LANS);

    void update_status();
    void fetch_from_LANs();
    void send_to_LANs();
};

class LAN {
    private:

    public:

    char name;
    vector <bridge*> connected_bridges; // vector of connected bridges
    int designated_bridge_id;

    vector <trace_message> buffer;


    LAN(char NAME, vector <bridge*> CONNECTED_BRIDGES);
};

class trace_message{
    private:

    public: 

    bridge* root_bridge;
    int dist;
    bridge* sending_bridge;

    trace_message(bridge* ROOT, int DIST,  bridge* SENDING_BRIDGE);
    void disp_msg();
};