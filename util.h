#ifndef UTIL_H
#define UTIL_H

#include <map> 
#include <set> 

enum dir{N, S, W, E, SW, SE, NW, NE};

struct stateT
{
    Node* node;
    dir direction;
	bool gameOver;
};

struct stateS
{
    Node* node;
	bool nodeFound;
};

typedef std::map<Node*,int> Scores_Container;
typedef std::set<int> Scores_Set;
typedef std::vector<Node> Node_Container;
typedef std::vector<Node*> Empty_Nodes_Container;
typedef std::map<Node*,int>::iterator Scores_Iterator;
typedef std::vector<Node>::iterator Node_Iterator;
typedef std::vector<Node*>::iterator Empty_Nodes_Iterator;

const unsigned char COMPUTER_MARK = 'O';
const unsigned char PLAYER_MARK = 'X';

#endif