#include <iostream>
#include <string>
using namespace std;

struct AdjNode {
    int index;
    int distance;
    AdjNode* next;
};

struct Planet {
    string name;
    AdjNode* head;
};

struct TreeNode {
    string planetName;
    string type;
    TreeNode* left;
    TreeNode* right;
};

class OrbitGraph {
    Planet planets[20];
    int planetCount;
    TreeNode* root; 

    int getIndex(string name) {
        for(int i = 0; i < planetCount; i++)
            if(planets[i].name == name) 
            return i;
        return -1;
    }

public:
    OrbitGraph() {
        planetCount = 0;
        root = NULL;
    }

    void addPlanet(string name) {
        planets[planetCount].name = name;
        planets[planetCount].head = NULL;
        planetCount++;
        cout << "Planet added: " << name << endl;
    }

    void addOrbit(string from, string to, int dist) {
        int u = getIndex(from);
        int v = getIndex(to);
        if(u == -1 || v == -1) {
            cout << "Invalid planet.\n";
            return;
        }

        AdjNode* a = new AdjNode{v, dist, planets[u].head};
        planets[u].head = a;

        AdjNode* b = new AdjNode{u, dist, planets[v].head};
        planets[v].head = b;

        cout << "Orbit added between " << from << " and " << to << " with distance " << dist << endl;
    }

    void displayGraph() {
        for(int i = 0; i < planetCount; i++) {
            cout << planets[i].name << " -> ";
            AdjNode* t = planets[i].head;
            while(t) {
                cout << planets[t->index].name << "(" << t->distance << ") ";
                t = t->next;
            }
            cout << endl;
        }
    }

    void aiMissionPlanner(string src, string dest) {
        int s = getIndex(src);
        int d = getIndex(dest);

        int dist[20], visited[20] = {0};
        for(int i=0;i<20;i++) 
        dist[i]=999999;
        dist[s]=0;

        for(int c=0;c<planetCount;c++) {
            int u=-1,min=999999;
            for(int i=0;i<planetCount;i++)
                if(!visited[i] && dist[i]<min)
                {
                    min=dist[i];
                    u=i;
                }

            if(u==-1) 
            break;
            visited[u]=1;

            AdjNode* t = planets[u].head;
            while(t){
                if(dist[u]+t->distance < dist[t->index])
                    dist[t->index]=dist[u]+t->distance;
                t=t->next;
            }
        }

        cout << "\nAI Mission Report:\n";
        cout << "From: " << src << "\nTo: " << dest << endl;
        cout << "Energy Cost: " << dist[d] << endl;

        if(dist[d] < 100)
            cout << "Mission Type: Exploration\n";
        else if(dist[d] < 400)
            cout << "Mission Type: Colonization\n";
        else
            cout << "Mission Type: Deep Space Mining\n";
    }

    TreeNode* insertTree(TreeNode* node, string name, string type) {
        if(node == NULL) {
            TreeNode* t = new TreeNode{name, type, NULL, NULL};
            return t;
        }
        if(type < node->type)
            node->left = insertTree(node->left, name, type);
        else
            node->right = insertTree(node->right, name, type);
        return node;
    }

    void classifyPlanet(string name, string type) {
        root = insertTree(root, name, type);
        cout << "Planet classified: " << name << " as " << type << endl;
    }

    void showClassification(TreeNode* node) {
        if(!node) 
        return;
        showClassification(node->left);
        cout << node->planetName << " -> " << node->type << endl;
        showClassification(node->right);
    }

    void displayTree() {
        cout << "\nPlanet Classification:\n";
        showClassification(root);
    }
};

int main() {
    OrbitGraph system;

    system.addPlanet("Earth");
    system.addPlanet("Mars");
    system.addPlanet("Venus");

    system.addOrbit("Earth", "Mars", 56);
    system.addOrbit("Earth", "Venus", 42);
    system.addOrbit("Mars", "Venus", 38);

    system.displayGraph();

    system.aiMissionPlanner("Earth", "Venus");

    system.classifyPlanet("Earth", "Habitable");
    system.classifyPlanet("Mars", "Non");
    system.classifyPlanet("Venus", "Non");

    system.displayTree();

    return 0;
}