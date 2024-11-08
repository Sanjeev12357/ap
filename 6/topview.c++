#include<bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

/*
class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

*/

    void topView(Node *root) {
    if (root == nullptr) return;

    // Map to store the topmost node at each horizontal distance
    map<int, int> topNodes;
    // Queue to store nodes along with their horizontal distance
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        Node* node = q.front().first;
        int hd = q.front().second;
        q.pop();

        // If this HD is not in the map, add it as it's the topmost node at this HD
        if (topNodes.find(hd) == topNodes.end()) {
            topNodes[hd] = node->data;
        }

        // Traverse left and right children with updated HDs
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }

    // Print the top view by iterating over the map
    for (const auto& [hd, data] : topNodes) {
        cout << data << " ";
    }
}


}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
	myTree.topView(root);
    return 0;
}
