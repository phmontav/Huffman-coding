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
string text;
map<char, int> char_freq;
vector<pair<int, char>> freq_table;
vector<Node *> freq_Node;
vector<pair<char, string>> code_table;
map<char,string > char_code;

bool comparator(Node *n1, Node *n2)
{
    return n1->freq > n2->freq;
}

bool comparator_codeTable(pair<char, string> p1, pair<char, string> p2)
{
    if (p1.second.size() < p2.second.size())
        return true;
    else
        return false;
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
            text.push_back(ch);
        }

        for (auto itr = char_freq.begin(); itr != char_freq.end(); itr++)
        {
            freq_table.push_back(make_pair(itr->second, itr->first));
        }
        sort(freq_table.begin(), freq_table.end());
        reverse(freq_table.begin(), freq_table.end());
    }
}

void make_CodeFile()
{
    char url[] = "texto.hfm";
    FILE *arq;
    arq = fopen(url,"w");
    if(arq == NULL)
        printf("Erro ao abrir arquivo\n");
    else
    {
        for(auto ch : text)
        {
            for(auto ch_aux : char_code[ch])
            {
                if(ch_aux == '1' || ch_aux == '0') fputc(ch_aux,arq);
            }
        }
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
string code;
void make_CodeTable(Node *&root)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        code_table.push_back(make_pair(root->ch, code));
        //code.pop_back();
        return;
    }
    code.push_back('1');
    make_CodeTable(root->right);
    if (code.size() != 0)
        code.pop_back();
    code.push_back('0');
    make_CodeTable(root->left);
    if (code.size() != 0)
        code.pop_back();
}

void map_char_code()
{
    for(auto aux : code_table)
    {
        char_code[aux.first] = aux.second;
    }
}

void print_TreePreOrder(Node *root, FILE *&arq)
{
    if (root->left == nullptr && root->right == nullptr)
        fprintf(arq,"%d,%d ",root->freq,root->ch);
    else
        fprintf(arq,"%d,-1 ",root->freq);

    if (root->left != nullptr)
        print_TreePreOrder(root->left, arq);

    if (root->right != nullptr)
        print_TreePreOrder(root->right, arq);
}

void print_TreeInOrder(Node *root, FILE *&arq)
{
    if (root->left != nullptr)
        print_TreeInOrder(root->left, arq);

    if (root->left == nullptr && root->right == nullptr)
         fprintf(arq,"%d,%d ",root->freq,root->ch);
    else
        fprintf(arq,"%d,-1 ",root->freq);

    if (root->right != nullptr)
        print_TreeInOrder(root->right, arq);
}

void make_TreeFile(Node *&root)
{
    char url[] = "arvhuf.txt";
    FILE *arq;
    arq = fopen(url,"w");
    if(arq == NULL)
        printf("Erro ao abrir arquivo\n");
    else
    {
        print_TreeInOrder(root,arq);
        fprintf(arq,"\n");
        print_TreePreOrder(root,arq);

    }
}

int main()
{
    make_freqTable();
    make_Nodes();
    make_tree();
    Node *aux = freq_Node.back();
    make_CodeTable(aux);
    map_char_code();
    sort(code_table.begin(), code_table.end(), comparator_codeTable);
    make_CodeFile();
    make_TreeFile(aux);
    //print_TreePreOrder(aux);
    cout << endl << endl;
    //print_TreeInOrder(aux);
}