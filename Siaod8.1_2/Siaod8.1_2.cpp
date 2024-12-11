#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top();
}

void generateCodes(Node* root, const string& code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

string encode(const string& text, const unordered_map<char, string>& huffmanCode) {
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode.at(ch);
    }
    return encoded;
}

string decode(const string& encoded, Node* root) {
    string decoded = "";
    Node* current = root;
    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

string readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return text;
}

void writeFile(const string& filename, const string& data) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    file << data;
    file.close();
}

int main() {
    setlocale(LC_ALL, "Ru");
    string filename = "input.txt";
    string text = readFile(filename);

    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    Node* root = buildHuffmanTree(freq);

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    /*for (const auto& pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }*/

    string encoded = encode(text, huffmanCode);
    writeFile("encoded.txt", encoded);

    string decoded = decode(encoded, root);
    writeFile("decoded.txt", decoded);

    cout << "Коэффициент сжатия: " << text.size() / (encoded.size() / 8.0) << endl;

    return 0;
}