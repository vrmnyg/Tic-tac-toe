#include "node.h"

Node::Node(unsigned int v, unsigned int h): vertical_position(v), horizontal_position(h),
node_W(0), node_E(0), node_N(0), node_S(0), node_NW(0), node_NE(0), node_SW(0), node_SE(0), mark(0)
{
    mark = EMPTY_MARK;
}

Node::~Node()
{ 
	/*std::cout << "Node destructor\n";*/
}

std::vector<Node*> Node::Return_Nodes()
{
    nodes.clear();
    if(node_W != 0) nodes.push_back(node_W);
	if(node_E != 0) nodes.push_back(node_E);
	if(node_N != 0) nodes.push_back(node_N);
	if(node_S != 0) nodes.push_back(node_S);
    if(node_SW != 0) nodes.push_back(node_SW);
	if(node_SE != 0) nodes.push_back(node_SE);
	if(node_NE != 0) nodes.push_back(node_NE);
	if(node_NW != 0) nodes.push_back(node_NW);
    return nodes;
}

void Node::Print_Node_Position() const
{
    //std::cout << "----------------------------------------------------" << "\n";
    std::cout << "Vertical: " << vertical_position << " Horizontal: " << horizontal_position << "\n";
    //std::cout << "----------------------------------------------------" << "\n";
}

void Node::Print_Node() const
{
	std::cout << "----------------------------------------------------" << "\n";
	std::cout << "Vertical: " << vertical_position << " Horizontal: " << horizontal_position << "\n";
	if(node_W != 0) std::cout << "West: " << node_W->Get_Vertical_Pos() << "," << node_W->Get_Horizontal_Pos() << "\n";
	if(node_E != 0) std::cout << "East: " << node_E->Get_Vertical_Pos() << "," << node_E->Get_Horizontal_Pos() << "\n";
	if(node_N != 0) std::cout << "North: " << node_N->Get_Vertical_Pos() << "," << node_N->Get_Horizontal_Pos() << "\n";
	if(node_S != 0) std::cout << "South: " << node_S->Get_Vertical_Pos()<< "," << node_S->Get_Horizontal_Pos() << "\n";
    
    if(node_SW != 0) std::cout << "SouthWest: " << node_SW->Get_Vertical_Pos() << "," << node_SW->Get_Horizontal_Pos() << "\n";
	if(node_SE != 0) std::cout << "SouthEast: " << node_SE->Get_Vertical_Pos() << "," << node_SE->Get_Horizontal_Pos() << "\n";
	if(node_NE != 0) std::cout << "NortEast: " << node_NE->Get_Vertical_Pos() << "," << node_NE->Get_Horizontal_Pos() << "\n";
	if(node_NW != 0) std::cout << "NorthWest: " << node_NW->Get_Vertical_Pos()<< "," << node_NW->Get_Horizontal_Pos() << "\n";
	std::cout << "----------------------------------------------------" << "\n";
}