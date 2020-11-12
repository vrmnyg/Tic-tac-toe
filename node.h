#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
const unsigned char EMPTY_MARK = ' ';

class Node
{
public:
	Node(unsigned int v,  unsigned int h);
	~Node();
	void Print_Node() const;
    void Print_Node_Position() const;
    void Print_Mark() const;
	unsigned int Get_Vertical_Pos() const;
	unsigned int Get_Horizontal_Pos() const;
	Node* Get_Node_W() const;
	Node* Get_Node_E() const;
	Node* Get_Node_N() const;
	Node* Get_Node_S() const;
    Node* Get_Node_NW() const;
	Node* Get_Node_NE() const;
	Node* Get_Node_SW() const;
	Node* Get_Node_SE() const;
	void Set_Node_W(Node* node);
	void Set_Node_E(Node* node);
	void Set_Node_N(Node* node);
	void Set_Node_S(Node* node);
    void Set_Node_NW(Node* node);
	void Set_Node_NE(Node* node);
	void Set_Node_SW(Node* node);
	void Set_Node_SE(Node* node);
    void Set_Mark(unsigned char);
    void Reset_Mark();
    unsigned char Get_Mark();
    std::vector<Node*> Return_Nodes();
private:
	unsigned int vertical_position;
	unsigned int horizontal_position;
	Node* node_W;
	Node* node_E;
	Node* node_N;
	Node* node_S;
    Node* node_NW;
	Node* node_NE;
	Node* node_SW;
	Node* node_SE;
    std::vector<Node*> nodes;
    unsigned char mark;
};

inline unsigned int Node::Get_Vertical_Pos() const
{
	return vertical_position;
}

inline unsigned int Node::Get_Horizontal_Pos() const
{
	return horizontal_position;
}

inline Node* Node::Get_Node_W() const
{
	return node_W;
}

inline Node* Node::Get_Node_E() const
{
	return node_E;
}

inline Node* Node::Get_Node_N() const
{
	return node_N;
}

inline Node* Node::Get_Node_S() const
{
	return node_S;
}

inline Node* Node::Get_Node_NW() const
{
	return node_NW;
}

inline Node* Node::Get_Node_NE() const
{
	return node_NE;
}

inline Node* Node::Get_Node_SW() const
{
	return node_SW;
}

inline Node* Node::Get_Node_SE() const
{
	return node_SE;
}

inline void Node::Set_Node_W(Node* node)
{
	node_W = node;
}

inline void Node::Set_Node_E(Node* node)
{
	node_E = node;
}

inline void Node::Set_Node_N(Node* node)
{
	node_N = node;
}

inline void Node::Set_Node_S(Node* node)
{
	node_S = node;
}

inline void Node::Set_Node_NW(Node* node)
{
	node_NW = node;
}

inline void Node::Set_Node_NE(Node* node)
{
	node_NE = node;
}

inline void Node::Set_Node_SW(Node* node)
{
	node_SW = node;
}

inline void Node::Set_Node_SE(Node* node)
{
	node_SE = node;
}

inline void Node::Print_Mark() const
{
    std::cout << " " << mark << " ";
}

inline void Node::Set_Mark(unsigned char m)
{
    mark = m;
}

inline unsigned char Node::Get_Mark()
{
    return mark;
}

inline void Node::Reset_Mark()
{
    mark = EMPTY_MARK;    
}
#endif