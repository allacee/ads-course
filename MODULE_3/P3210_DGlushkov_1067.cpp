#include <iostream>
#include <map>
#include <cstdint>
#include <vector>

using namespace std;

struct Node
{
    string str;
    uint8_t level;
    map<string, Node> child;

protected:
    vector<string> parse_path_str(string& path_str)
    {
        vector<string> path;
        for (uint8_t last = 0, first; last < path_str.size(); last++)
        {
            first = last;
            while(path_str[last] != '\\' && path_str[last] != '\0')
                last++;
            path.push_back(path_str.substr(first, last - first));
        }
        return path;
    }



public:

    Node(string str, uint32_t level, map<string, Node> child) : str(std::move(str)), level(level), child(std::move(child))
    {}

    void insert_path (string& path_str)
    {
        vector<string> paths = parse_path_str(path_str);
        Node * cur_node = this;

        for (uint8_t i = 0; i < paths.size(); i++)
        {
            if (cur_node->child.count(paths[i])) // if already exists
                cur_node = &(cur_node->child.at(paths[i]));

            else
            {
                //cur_node->child[paths[i]] = Node(paths[i], i, map<string, Node>());
                cur_node->child.insert(make_pair( paths[i], Node(paths[i], i,  map<string, Node>())));
                cur_node = &(cur_node->child.at(paths[i]));
            }
        }
    }

    static ostream& do_print(ostream& os, const Node& node)
    {
        for (uint i = 0; i < node.child.size(); i++)
        {
            os << node.str;
            for(const auto &cur_child : node.child)
                do_print(os, node.child.at(cur_child.first));
        }


        return os;
//        if (node.child.empty())
//        {
//            for (uint8_t i = 0; i < node.level; i++)
//                os << ' ';
//            os << node.str << '\n';
//        }
//        else
//        {
//            for (uint8_t i = 0; i < node.level; i++)
//                os << ' ';
//            os << node.str << '\n';
//            for(const auto &cur_child : node.child)
//                do_print(os, node.child.at(cur_child.first));
//
//
//        }
//        return os;
    }

    friend ostream& operator<<(ostream& os, const Node& node);


};

ostream &operator<<(ostream &os, const Node& node)
{
//    return Node::do_print(os, node.child.begin().operator*().second);
    return Node::do_print(os, node);
}


int main()
{
    Node root = Node("root", 0, map<string, Node>());
    string temp_path;
    uint16_t N;
    cin >> N;
    for (uint16_t i = 0; i < N; i++)
    {
        cin >> temp_path;
        root.insert_path(temp_path);
    }
    cout << root;

    return 0;
}
