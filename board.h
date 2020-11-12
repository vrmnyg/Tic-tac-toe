#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "node.h"
#include "util.h"

class Board
{
public:
    Board(const unsigned int);
    Board(const unsigned int, Node_Container);
	~Board();
    void Print_Board();
    void Print_Free_Nodes();
    void Set_Mark(unsigned int, unsigned int, unsigned char);
    void Remove_Mark(unsigned int, unsigned int);
    Empty_Nodes_Container Get_Free_Nodes();
    Node_Container Get_All_Nodes();
private:
    //Board(const Board&);
    Board& operator=(const Board&);
    void Init();
    void Copy(Node_Container);
    Node* Get_Node(unsigned int w, unsigned int h);
    Node_Iterator iterator;
    Empty_Nodes_Iterator empty_iterator;
    Node_Container sectors;
    Empty_Nodes_Container empty_sectors;
    unsigned int size;
};
#endif