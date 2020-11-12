#include "board.h"

Board::Board(unsigned int s): size(s)
{
    Init();
}

Board::Board(unsigned int s, Node_Container nodes): size(s)
{
    Init();
    Copy(nodes);
}


Board::~Board() 
{

}

void Board::Copy(Node_Container nodes)
{
    for(iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
    {
        unsigned int v = iterator->Get_Vertical_Pos();
        unsigned int h = iterator->Get_Horizontal_Pos();
        unsigned char mark = iterator->Get_Mark();
        if(mark == COMPUTER_MARK || mark == PLAYER_MARK)
        {
            Node_Iterator iterator2;
            Node* node;
            for(iterator2 = sectors.begin(); iterator2 != sectors.end(); ++iterator2)
            {
                unsigned int vertical = iterator2->Get_Vertical_Pos();
                unsigned int horizontal = iterator2->Get_Horizontal_Pos();
                if(horizontal == h && vertical == v)
                {
                    node = &(*iterator2);
                    node->Set_Mark(mark);
                }
            }
            Node* back_node = empty_sectors.back();
            if(back_node == node)
            {
                empty_iterator = empty_sectors.end();
                --empty_iterator;
                empty_sectors.erase(empty_iterator);
            }
            else
            {    
                for(empty_iterator = empty_sectors.begin(); empty_iterator != empty_sectors.end(); ++empty_iterator)
                {
                    if((*empty_iterator) == node)
                    {
                        empty_sectors.erase(empty_iterator);
                    }
                }
            }
        }
    }
}

void Board::Init()
{
    for(unsigned int h = 0; h < size; ++h)
    {
        for(unsigned int w = 0; w < size; ++w)
        {
            sectors.push_back(Node(h + 1, w + 1));
        }
    }
    for(unsigned int i = 0; i < sectors.size(); ++i)
    {
        Node* node = &sectors[i];
        empty_sectors.push_back(node);
        for(unsigned int j = 0; j < sectors.size(); ++j)
        {
            Node* node2 = &sectors[j];
            if(node->Get_Vertical_Pos() == node2->Get_Vertical_Pos() && (node->Get_Horizontal_Pos() + 1) == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_E(node2);	
            }
            if(node->Get_Vertical_Pos() == node2->Get_Vertical_Pos() && (node->Get_Horizontal_Pos() - 1) == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_W(node2);
            }
            if((node->Get_Vertical_Pos() + 1) == node2->Get_Vertical_Pos() && node->Get_Horizontal_Pos() == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_S(node2);
            }
            if((node->Get_Vertical_Pos() - 1) == node2->Get_Vertical_Pos() && node->Get_Horizontal_Pos() == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_N(node2);
            }
            if((node->Get_Vertical_Pos() + 1) == node2->Get_Vertical_Pos() && (node->Get_Horizontal_Pos() + 1) == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_SE(node2);	
            }
            if((node->Get_Vertical_Pos() - 1) == node2->Get_Vertical_Pos() && (node->Get_Horizontal_Pos() - 1) == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_NW(node2);
            }
            if((node->Get_Vertical_Pos() + 1) == node2->Get_Vertical_Pos() && (node->Get_Horizontal_Pos() - 1) == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_SW(node2);
            }
            if((node->Get_Vertical_Pos() - 1) == node2->Get_Vertical_Pos() && (node->Get_Horizontal_Pos() + 1) == node2->Get_Horizontal_Pos())
            {
                node->Set_Node_NE(node2);
            }
        }
    }
}

void Board::Print_Board()
{
    for(iterator = sectors.begin(); iterator != sectors.end(); ++iterator)
    {
        unsigned int h = iterator->Get_Horizontal_Pos();
        if(h == 1)
        {
            for(unsigned int h = 0; h < size - 1; ++h)
            {
                std::cout << "---+";
            }
            std::cout << "---" << '\n';
                        
            iterator->Print_Mark();
            std::cout << "|";
            Node* temp = iterator->Get_Node_E();
            while(temp != 0)
            {
                temp->Print_Mark();
                temp = temp->Get_Node_E();
                if(temp != 0)
                {
                    std::cout << "|";
                }
            }
            std::cout << '\n';
        }
    }
}

void Board::Print_Free_Nodes()
{
    std::cout << "---------------------------" << "\n";
    for(empty_iterator = empty_sectors.begin(); empty_iterator != empty_sectors.end(); ++empty_iterator)
    {       
        (*empty_iterator)->Print_Node_Position();
    }
    std::cout << "---------------------------" << "\n";
}    

Node* Board::Get_Node(unsigned int v, unsigned int h)
{
    Node* node;
    for(iterator = sectors.begin(); iterator != sectors.end(); ++iterator)
    {
        unsigned int horizontal = iterator->Get_Horizontal_Pos();
        unsigned int vertical = iterator->Get_Vertical_Pos();
        if(horizontal == h && vertical == v)
        {
            node = &(*iterator);
        }
    }
    return node;
}

Empty_Nodes_Container Board::Get_Free_Nodes()
{
    return empty_sectors;
}

Node_Container Board::Get_All_Nodes()
{
    return sectors;
}

void Board::Remove_Mark(unsigned int v, unsigned int h)
{
    if(v <= size && h <= size)
    {
        Node* node = Get_Node(v, h);
        node->Reset_Mark();
        empty_sectors.push_back(node);
    }
}

void Board::Set_Mark(unsigned int v, unsigned int h, unsigned char mark)
{
    if(v <= size && h <= size)
    {
        Node* node = Get_Node(v, h);
        node->Set_Mark(mark);
        Node* back_node = empty_sectors.back();
        if(back_node == node)
        {
            empty_iterator = empty_sectors.end();
            --empty_iterator;
            empty_sectors.erase(empty_iterator);
        }
        else
        {    
            for(empty_iterator = empty_sectors.begin(); empty_iterator != empty_sectors.end(); ++empty_iterator)
            {
                if((*empty_iterator) == node)
                {
                    empty_sectors.erase(empty_iterator);
                }
            }
        }
    }
    else
    {
        // Try-catch!!
        std::cout << "er323ror!" <<'\n';   
    }
}