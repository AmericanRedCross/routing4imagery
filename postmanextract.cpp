#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class ProcessCSV{
    private:
        struct Node{
            long long i, nodeid;
            double nodelon, nodelat;
        };

        struct Edges{
            long long strtid, endid;
            double length;
            long long edgeid;

            Edges(long long strtin, long long endin, double lenin) : strtid(strtin), endid(endin), length(lenin){}
        };
        
        unordered_map<long long, ProcessCSV::Node> ids;
        vector<ProcessCSV::Edges> edges; 
        string infileedges;

    public:
        
        int getnodecount(string infilenodes){
            ifstream nodes(infilenodes.c_str());
            string currline;
            int i = 0;
            getline(nodes, currline);
            while(getline(nodes, currline)){
                stringstream ss(currline);
                long long id;
                double lon, lat;
                char fill;
                ss >> id >> fill >> lon >> fill >> lat;
                Node n;
                n.i = i++;
                n.nodeid = id;
                n.nodelat = lat;
                n.nodelon = lon;
                ids[id] = n;           
            }
            
            cout << ids.size() << '\n';
            return ids.size();
        }

        void getedges(string infileedges, ofstream & fout){
            ifstream inedges(infileedges.c_str());
            string currline;
            getline(inedges, currline);
            long long fillint;
            while(getline(inedges, currline)){
                stringstream ss(currline);
                long long source, target;
                double length;
                char fill;
                ss >> fillint >> fill >> source >> fill >> target >> fill >> length;
                if(ids.find(source) == ids.end() || ids.find(target) == ids.end()){
                    cerr << "Node not found\n";
                    exit(1);
                }
                Edges e(source, target, length);
                // cout << source << " " << target << "\n";
                e.edgeid = fillint;
                edges.push_back(e);
                // cout << e.edgeid << " " << e.length << " " << e.strtid << " " << e.endid << "\n";
            }
            fout << ids.size() << '\n';
            fout << edges.size() << '\n';
            for(int i = 0; i < (int) edges.size(); ++i){
                const Edges & edgesi = edges[i];
                fout << edgesi.strtid << " " << edgesi.endid << " " << edgesi.length;
                if(i < (int)edges.size()-1){fout << '\n';}
            }           
        }

        void getnodelegend(ofstream & fout){
            fout << "key    id\n";
            // int i = 0;
            for(const auto & it : ids){
                fout << it.second.i << " " << it.first << '\n';
            }
        }

        void postman_extract(ofstream & osmextract){
            osmextract << "Start Node,End Node,Segment Length,Segment ID,Start Longitude,Start Latitude,End Longitude,End Latitude\n";
            for(size_t i = 0; i < edges.size(); ++i){
                const Edges & curr = edges[i];
                osmextract << curr.strtid << "," << curr.endid << "," << curr.length << "," << curr.edgeid << "," << ids[curr.strtid].nodelon 
                    << "," << ids[curr.strtid].nodelat << "," << ids[curr.endid].nodelon << "," << ids[curr.endid].nodelat << "\n";
            }
        }

};


int main(int argc, char ** argv){
    ios_base::sync_with_stdio(false);
    if(argc != 3){
        cerr << "Incorrect usage: must have nodes csv followed by edges csv\n";
    }
    cout.precision(4);
    ifstream nodes(argv[1]);
    ifstream edges(argv[2]);

    //EXTRACT INPUT FOR chinese (c++)
    ofstream edgelist("edgelist.out");
    ofstream nodelegend("nodelegend.out");

    ProcessCSV pcsv;
    pcsv.getnodecount(argv[1]);
    pcsv.getedges(argv[2], edgelist);
    pcsv.getnodelegend(nodelegend); 
    //END EXTRACT

    //START EXTRACT FOR postman.py
    ofstream osmextract("postman_input.csv");
    // osmextract << "Start Node,End Node,Segment Length,Segment ID,Start Longitude,Start Latitude,End Longitude,End Latitude\n";
    pcsv.postman_extract(osmextract);
    //END EXTRACT FOR postman.py
}