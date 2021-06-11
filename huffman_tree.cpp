#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int freq;
    char ch;
    Node *right;
    Node *left;
    Node(int freq, char ch) : freq(freq), ch(ch), right(nullptr), left(nullptr) {}
    Node() : freq(0), ch('\0'), right(nullptr), left(nullptr) {}
};

map<char, int> char_freq;
vector<pair<int, char>> freq_table;
vector<Node *> freq_Node;

bool comparator(Node *n1, Node *n2)
{
    return n1->freq > n2->freq;
}

void make_freqTable()
{
    char url[] = "input.txt";
    FILE *arq;

    arq = fopen(url, "r");
    if (arq == NULL)
        printf("Erro ao abrir\n");
    else
    {
        char ch;
        while (fscanf(arq, "%c", &ch) != EOF)
        {
            char_freq[ch]++;
        }

        for (auto itr = char_freq.begin(); itr != char_freq.end(); itr++)
        {
            freq_table.push_back(make_pair(itr->second, itr->first));
        }
        sort(freq_table.begin(), freq_table.end());
        reverse(freq_table.begin(), freq_table.end());
    }
}

void make_Nodes()
{
    for (auto ft : freq_table)
    {
        Node *node = new Node(ft.first, ft.second);
        freq_Node.push_back(node);
    }
    sort(freq_Node.begin(), freq_Node.end(), comparator);
}

void make_tree()
{
    if (freq_Node.size() == 1)
        return;
    Node *left_most = freq_Node.back();
    freq_Node.pop_back();
    Node *second_left_most = freq_Node.back();
    freq_Node.pop_back();
    Node *new_root = new Node;
    new_root->left = left_most;
    new_root->right = second_left_most;
    new_root->freq = left_most->freq + second_left_most->freq;
    freq_Node.push_back(new_root);
    sort(freq_Node.begin(), freq_Node.end(), comparator);
    make_tree();
}

int main()
{
    make_freqTable();
    make_Nodes();
    make_tree();
    Node *aux = freq_Node.back();
}