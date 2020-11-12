#include "game.h"

Game::Game(unsigned int size): turnsTaken(0), whoseTurn(Human), mark_count_h(0), mark_count_l(0), board_size(size)
{
    Init_Board();
    minNode = 0;
    maxNode = 0;
    user_move = 0;
    gameIsOver = false;
    winning_mark = EMPTY_MARK;
}

Game::~Game()
{ 
	delete game_board;
}

void Game::Init_Board()
{
    game_board = new Board(board_size);
}

void Game::StartGame()
{
    unsigned char select;
    bool moveNotMade = true;
    std::cout << "Who starts the game." << std::endl;
    std::cout << "C = Computer, P = You." << std::endl;

	while(moveNotMade)
	{
        std::cin >> select;

		if((select == 'c') || (select == 'C'))
        {
            whoseTurn = Computer;
            moveNotMade = false;
            break;
        }
        if((select == 'p') || (select == 'P'))
        {
            whoseTurn = Human;
            moveNotMade = false;
            break;
        }
        else
        {
            continue;
        }
    }
}

playerT Game::Opponent(playerT t)
{
    return(t == Human) ? Computer : Human;
}

//  One turn. Set mark on the board sector (v,h) and switch turns.
void Game::Make_Turn(unsigned int v, unsigned int h)
{
    unsigned char s;
    if(whoseTurn == Computer)
    {
        s = COMPUTER_MARK;
    }
    else
    {
        s = PLAYER_MARK;
    }
    game_board->Set_Mark(v, h, s);
    whoseTurn = Opponent(whoseTurn);
}

// Score end game.
int Game::Score(Node* node, dir direction, int depth)
{
    unsigned char c = node->Get_Mark();
    if(c == PLAYER_MARK)
    {
        return depth - 100;
        //return -10;
    }
    else if(c == COMPUTER_MARK)
    {
        return 100 - depth;
        //return 10;
    }
    else
    {
        return 0;
    }
}

// check if board is full or not.
bool Game::Board_Full(Board* board)
{    
    Empty_Nodes_Container empty_container = board->Get_Free_Nodes();    
    if(empty_container.empty())
    {
        return true;
    }
    return false;
}

// Handle users moves.
Node* Game::GetUserMove(Board* board)
{
    std::cout << "Your move." << std::endl;
    unsigned int row;
    unsigned int column;
    Node* node = 0;
    bool moveNotMade = true;

	while(moveNotMade)
	{
		std::cout << "What Row? ";
        std::cin >> row;
        
        std::cout << "What Column? ";
        std::cin >> column;

		if((row > board_size) || (column > board_size))
        {
            std::cout << "Illegal move. Try again." << std::endl;
            break;
        }
        Empty_Nodes_Container nodes = board->Get_Free_Nodes();
        Empty_Nodes_Iterator empty_iterator;
        for(empty_iterator = nodes.begin(); empty_iterator != nodes.end(); ++empty_iterator)
        {
            unsigned int horizontal = (*empty_iterator)->Get_Horizontal_Pos();
            unsigned int vertical = (*empty_iterator)->Get_Vertical_Pos();
            if(horizontal == column && vertical == row)
            {
                node = *empty_iterator;
            }    
        }
        if(node == 0)
        {
            std::cout << "Illegal move. Try again." << std::endl;
            break;   
        }
        else
        {
            moveNotMade = false;
        }
    }
	return node;
}

// In rare cases where alphabeta function returns only one unique score use this alternative method to calculate Computer move.
void Game::AltMove(Board* board)
{
    stateS tempState = Alt_Move_Search(game_board, 2);
    if(tempState.nodeFound)
    {
        Node* node = tempState.node;
        if(node != 0)
        {
            unsigned int v = node->Get_Vertical_Pos();
            unsigned int h = node->Get_Horizontal_Pos();
            Make_Turn(v, h);
            if(v > (board_size / two))
            {
                ++mark_count_h;
            }
            else
            {
                ++mark_count_l;
            }           
        }
        else
        {
            unsigned int v = maxNode->Get_Vertical_Pos();
            unsigned int h = maxNode->Get_Horizontal_Pos();
            Make_Turn(v, h);
            if(v > (board_size / two))
            {
                ++mark_count_h;
            }
            else
            {
                ++mark_count_l;
            }                  
        }
    }
    else
    {
        unsigned int v = maxNode->Get_Vertical_Pos();
        unsigned int h = maxNode->Get_Horizontal_Pos();
        Make_Turn(v, h);
        if(v > (board_size / two))
        {
            ++mark_count_h;
        }
        else
        {
            ++mark_count_l;
        }      
    }
}

// In rare cases where alphabeta function returns only one unique score use this alternative method to calculate Computer move.
// Try to find 2 length rows and stop player from getting 3.
stateS Game::Alt_Move_Search(Board* board, int search_row)
{
    Node_Container container = board->Get_All_Nodes();
    Node_Iterator iterator;
    if(search_row == 2)
    {
        for(iterator = container.begin(); iterator != container.end(); ++iterator)
        {
            Node* node = &(*iterator);
            unsigned char c = node->Get_Mark();
            if(c == PLAYER_MARK)
            {
                Node* NodeW = node->Get_Node_W();
                Node* NodeE = node->Get_Node_E();
                Node* NodeN = node->Get_Node_N();
                Node* NodeS = node->Get_Node_S();
                Node* NodeNW = node->Get_Node_NW();
                Node* NodeNE = node->Get_Node_NE();
                Node* NodeSW = node->Get_Node_SW();
                Node* NodeSE = node->Get_Node_SE();
                if((NodeW != 0) && (c == NodeW->Get_Mark()))
                {
                    Node* tempNode = NodeW->Get_Node_W();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
                if((NodeE != 0) && (c == NodeE->Get_Mark()))
                {
                    Node* tempNode = NodeE->Get_Node_E();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
                if((NodeN != 0) && (c == NodeN->Get_Mark()))
                {
                    Node* tempNode = NodeN->Get_Node_N();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
                if((NodeS != 0) && (c == NodeS->Get_Mark()))
                {
                    Node* tempNode = NodeS->Get_Node_S();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
                if((NodeNW != 0) && (c == NodeNW->Get_Mark()))
                {
                    Node* tempNode = NodeNW->Get_Node_NW();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
                if((NodeSW != 0) && (c == NodeSW->Get_Mark()))
                {
                    Node* tempNode = NodeSW->Get_Node_SW();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
                if((NodeNE != 0) && (c == NodeNE->Get_Mark()))
                {
                    Node* tempNode = NodeNE->Get_Node_NE();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
                if((NodeSE != 0) && (c == NodeSE->Get_Mark()))
                {
                    Node* tempNode = NodeSE->Get_Node_SE();
                    if((tempNode != 0) && (tempNode->Get_Mark() == EMPTY_MARK))
                    {
                        stateS temp;
                        temp.node = tempNode;
                        temp.nodeFound = true;
                        return temp;
                    }
                }
            }
        }
    }
    stateS temp;
    temp.node = 0;
    temp.nodeFound = false;
    return temp;
}

// Check the board to see if game is at end state or not.
stateT Game::Game_Over(Board* board, int search_row)
{
    Node_Container container = board->Get_All_Nodes();
    Node_Iterator iterator;
    unsigned int PLAYER_MARK_COUNTER = 0;
    unsigned int COMPUTER_MARK_COUNTER = 0;
    for(iterator = container.begin(); iterator != container.end(); ++iterator)
    {
        Node* node = &(*iterator);
        unsigned char c = node->Get_Mark();
        if(c == PLAYER_MARK)
        {
            ++PLAYER_MARK_COUNTER;  
        }
        else if(c == COMPUTER_MARK)
        {
            ++COMPUTER_MARK_COUNTER;
        }
        else
        {
            continue;
        }
    }
    if(PLAYER_MARK_COUNTER < win_row && COMPUTER_MARK_COUNTER < win_row)
    {
        stateT temp;
        temp.node = 0;
        temp.direction = N;
        temp.gameOver = false;
        return temp;
    }
    else
    {
        for(iterator = container.begin(); iterator != container.end(); ++iterator)
        {
            Node* node = &(*iterator);
            unsigned char c = node->Get_Mark();
            if(c == PLAYER_MARK || c == COMPUTER_MARK)
            {
                Node* NodeW = node->Get_Node_W();
                Node* NodeE = node->Get_Node_E();
                Node* NodeN = node->Get_Node_N();
                Node* NodeS = node->Get_Node_S();
                Node* NodeNW = node->Get_Node_NW();
                Node* NodeNE = node->Get_Node_NE();
                Node* NodeSW = node->Get_Node_SW();
                Node* NodeSE = node->Get_Node_SE();
                // Does not work if win_row > 4!!! Need for()
                if((NodeW != 0) && (c == NodeW->Get_Mark()))
                {
                    Node* NodeW2 = NodeW->Get_Node_W();
                    if(win_row == 3)
                    {
                        if((NodeW2 != 0) && (c == NodeW2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = W;
                            temp.gameOver = true;
                            return temp;
                        }
                    }
                    else
                    {
                        if((NodeW2 != 0) && (c == NodeW2->Get_Mark()))
                        {
                            Node* temp = NodeW2->Get_Node_W();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = W;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
                if((NodeE != 0) && (c == NodeE->Get_Mark()))
                {
                    Node* NodeE2 = NodeE->Get_Node_E();
                    if(win_row == 3)
                    {
                        if((NodeE2 != 0) && (c == NodeE2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = E;
                            temp.gameOver = true;
                            return temp;    
                        }
                    }
                    else
                    {
                        if((NodeE2 != 0) && (c == NodeE2->Get_Mark()))
                        {
                            Node* temp = NodeE2->Get_Node_E();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = E;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
                if((NodeN != 0) && (c == NodeN->Get_Mark()))
                {
                    Node* NodeN2 = NodeN->Get_Node_N();
                    if(win_row == 3)
                    {
                        if((NodeN2 != 0) && (c == NodeN2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = N;
                            temp.gameOver = true;
                            return temp;    
                        }
                    }
                    else
                    {
                        if((NodeN2 != 0) && (c == NodeN2->Get_Mark()))
                        {
                            Node* temp = NodeN2->Get_Node_N();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = N;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
                if((NodeS != 0) && (c == NodeS->Get_Mark()))
                {
                    Node* NodeS2 = NodeS->Get_Node_S();
                    if(win_row == 3)
                    {
                        if((NodeS2 != 0) && (c == NodeS2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = S;
                            temp.gameOver = true;
                            return temp;
                        }
                    }
                    else
                    {
                        if((NodeS2 != 0) && (c == NodeS2->Get_Mark()))
                        {
                            Node* temp = NodeS2->Get_Node_S();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = S;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
                if((NodeNW != 0) && (c == NodeNW->Get_Mark()))
                {
                    Node* NodeNW2 = NodeNW->Get_Node_NW();
                    if(win_row == 3)
                    {
                        if((NodeNW2 != 0) && (c == NodeNW2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = NW;
                            temp.gameOver = true;
                            return temp;;    
                        }
                    }
                    else
                    {
                        if((NodeNW2 != 0) && (c == NodeNW2->Get_Mark()))
                        {
                            Node* temp = NodeNW2->Get_Node_NW();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = NW;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
                if((NodeSW != 0) && (c == NodeSW->Get_Mark()))
                {
                    Node* NodeSW2 = NodeSW->Get_Node_SW();
                    if(win_row == 3)
                    {
                        if((NodeSW2 != 0) && (c == NodeSW2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = SW;
                            temp.gameOver = true;
                            return temp;    
                        }
                    }
                    else
                    {
                        if((NodeSW2 != 0) && (c == NodeSW2->Get_Mark()))
                        {
                            Node* temp = NodeSW2->Get_Node_SW();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = SW;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
                if((NodeNE != 0) && (c == NodeNE->Get_Mark()))
                {
                    Node* NodeNE2 = NodeNE->Get_Node_NE();
                    if(win_row == 3)
                    {
                        if((NodeNE2 != 0) && (c == NodeNE2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = NE;
                            temp.gameOver = true;
                            return temp;    
                        }
                    }
                    else
                    {
                        if((NodeNE2 != 0) && (c == NodeNE2->Get_Mark()))
                        {
                            Node* temp = NodeNE2->Get_Node_NE();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = NE;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
                if((NodeSE != 0) && (c == NodeSE->Get_Mark()))
                {
                    Node* NodeSE2 = NodeSE->Get_Node_SE();
                    if(win_row == 3)
                    {
                        if((NodeSE2 != 0) && (c == NodeSE2->Get_Mark()))
                        {
                            stateT temp;
                            temp.node = node;
                            temp.direction = SE;
                            temp.gameOver = true;
                            return temp;    
                        }
                    }
                    else
                    {
                        if((NodeSE2 != 0) && (c == NodeSE2->Get_Mark()))
                        {
                            Node* temp = NodeSE2->Get_Node_SE();
                            if((temp != 0) && (c == temp->Get_Mark()))
                            {
                                stateT temp;
                                temp.node = node;
                                temp.direction = SE;
                                temp.gameOver = true;
                                return temp;
                            }
                        }    
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
    stateT temp;
    temp.node = 0;
    temp.direction = N;
    temp.gameOver = false;
    return temp;
}

// Minimax search function
int Game::Minimax(playerT whoseTurnT, Board* current_board, unsigned int depth)
{
    Empty_Nodes_Container empty_nodes = current_board->Get_Free_Nodes();
    Empty_Nodes_Iterator empty_iterator;
    
    // reverse searching order of nodes if most of marks are located at the lower part of board.
    // Nodes (3,1) (3,2) (3,3) (3,4) (4,1) (4,2) (4,3) (4,4) are consider lower part if board_size == 4
    // makes searching faster
    if(mark_count_h > mark_count_l)
    {
        std::reverse(empty_nodes.begin(), empty_nodes.end());
    }
    
    stateT tempState = Game_Over(current_board, win_row);
    // Check if in a end state and give score if true.
    if(tempState.gameOver)
    {
        int score = Score(tempState.node, tempState.direction, depth);
        return score;    
    }
    // Only one empty slot left.
    else if(empty_nodes.size() == 1)
    {
        unsigned int v = empty_nodes.front()->Get_Vertical_Pos();
        unsigned int h = empty_nodes.front()->Get_Horizontal_Pos();
        if(whoseTurnT == Computer)
        {
            current_board->Set_Mark(v, h, COMPUTER_MARK); 
        }
        else
        {
            current_board->Set_Mark(v, h, PLAYER_MARK);
        }
        stateT tempState = Game_Over(current_board, win_row);
        if(tempState.gameOver)
        {
            int score = Score(tempState.node, tempState.direction, depth);
            return score;    
        }
        else
        {
            return 0;
        }
    }
    // Game not over - Use Minimax
    else
    {        
        if(whoseTurnT == Computer)
        {
            int max = -inf;
            for(empty_iterator = empty_nodes.begin(); empty_iterator != empty_nodes.end(); ++empty_iterator)
            {
                unsigned int v = (*empty_iterator)->Get_Vertical_Pos();
                unsigned int h = (*empty_iterator)->Get_Horizontal_Pos();
                Board temp_board = Board(board_size, current_board->Get_All_Nodes());
                temp_board.Set_Mark(v, h, COMPUTER_MARK);
                int score = Minimax(Opponent(whoseTurnT), &temp_board, (depth + 1));
                if(score > max)
                {
                    max = score;
                    if(depth == 0)
                    {
                        maxNode = (*empty_iterator);
                    }
                }
            }
            return max;
        }
        else
        {
            int min = inf;
            for(empty_iterator = empty_nodes.begin(); empty_iterator != empty_nodes.end(); ++empty_iterator)
            {
                unsigned int v = (*empty_iterator)->Get_Vertical_Pos();
                unsigned int h = (*empty_iterator)->Get_Horizontal_Pos();
                Board temp_board = Board(board_size, current_board->Get_All_Nodes());
                temp_board.Set_Mark(v, h, PLAYER_MARK);
                int score = Minimax(Opponent(whoseTurnT), &temp_board, (depth + 1));
                if(score < min)
                {
                    min = score;
                    if(depth == 0)
                    {
                        minNode = (*empty_iterator);
                    }
                }
            }
            return min;
        }
    }
}

// AlphaBeta search function
int Game::Alphabeta(playerT whoseTurnT, Board* current_board, unsigned int depth, int alpha, int beta)
{
    Empty_Nodes_Container empty_nodes = current_board->Get_Free_Nodes();
    Empty_Nodes_Iterator empty_iterator;
    
    // reverse searching order of nodes if most of marks are located at the lower part of board.
    // Nodes (3,1) (3,2) (3,3) (3,4) (4,1) (4,2) (4,3) (4,4) are consider lower part if board_size == 4
    // makes searching faster
    if(mark_count_h > mark_count_l)
    {
        std::reverse(empty_nodes.begin(), empty_nodes.end());
    }

    stateT tempState = Game_Over(current_board, win_row);
    // Check if in a end state and give score if true.
    if(tempState.gameOver)
    {
        int score = Score(tempState.node, tempState.direction, depth);
        return score;    
    }
    // Only one empty slot left. Only one possible move. Game basically over.
    else if(empty_nodes.size() == 1)
    {
        unsigned int v = empty_nodes.front()->Get_Vertical_Pos();
        unsigned int h = empty_nodes.front()->Get_Horizontal_Pos();
        if(whoseTurnT == Computer)
        {
            current_board->Set_Mark(v, h, COMPUTER_MARK); 
        }
        else
        {
            current_board->Set_Mark(v, h, PLAYER_MARK);
        }
        stateT tempState = Game_Over(current_board, win_row);
        if(tempState.gameOver)
        {
            int score = Score(tempState.node, tempState.direction, depth);
            return score;    
        }
        else
        {
            return 0;
        }
    }
    // Game not over - Use AlphaBeta
    else
    {        
        if(whoseTurnT == Computer)
        {
            for(empty_iterator = empty_nodes.begin(); empty_iterator != empty_nodes.end(); ++empty_iterator)
            {
                unsigned int v = (*empty_iterator)->Get_Vertical_Pos();
                unsigned int h = (*empty_iterator)->Get_Horizontal_Pos();
                // make a copy of the board
                Board temp_board = Board(board_size, current_board->Get_All_Nodes());
                // edit the copy instead of the "real" board
                temp_board.Set_Mark(v, h, COMPUTER_MARK);
                int score = Alphabeta(Opponent(whoseTurnT), &temp_board, (depth + 1), alpha, beta);
                if(depth == 0)
                {
                    // insert depth 0 node scores to map.
                    // if all scores are the same (map size is 1) calculate computer move with some other method.
                    // should not really happen if depth is used at scoring.
                    s_scores.insert(score);
                }
                if(score > alpha)
                {
                    alpha = score;
                    if(depth == 0)
                    {
                        maxNode = (*empty_iterator);
                    }
                }
                if(alpha >= beta)
                {
                    break;
                }
            }
            return alpha;
        }
        else
        {
            for(empty_iterator = empty_nodes.begin(); empty_iterator != empty_nodes.end(); ++empty_iterator)
            {
                unsigned int v = (*empty_iterator)->Get_Vertical_Pos();
                unsigned int h = (*empty_iterator)->Get_Horizontal_Pos();
                Board temp_board = Board(board_size, current_board->Get_All_Nodes());
                temp_board.Set_Mark(v, h, PLAYER_MARK);
                int score = Alphabeta(Opponent(whoseTurnT), &temp_board, (depth + 1), alpha, beta);
                /*if(depth == 0)
                {
                    // if all scores are -X do something different.
                    s_scores.insert(score);
                }*/
                if(score < beta)
                {
                    beta = score;
                    if(depth == 0)
                    {
                        minNode = (*empty_iterator);
                    }
                }
                if(alpha >= beta)
                {
                    break;
                }
            }
            return beta;
        }
    }
}

// Game execution
// Switch between players and keep the game going. Give results when game is finished.
// If board_size == 4 don't use AlphaBeta or Minimax at first turn because searching is too slow.
// Instead at first turn counter players first move and use AlphaBeta after that.
// Or if computer starts open with (2,2), continue with AlphaBeta and win the game.
void Game::Execute()
{   
    StartGame();
    while(!gameIsOver)
	{
        game_board->Print_Board();
        switch(whoseTurn)
		{
			case Human:
            {
                user_move = GetUserMove(game_board);
                if(user_move == 0)
                {
                    continue;
                }
                unsigned int v = user_move->Get_Vertical_Pos();
                unsigned int h = user_move->Get_Horizontal_Pos();
                Make_Turn(v, h);
                ++turnsTaken;
                
                if(v > (board_size / two))
                {
                    ++mark_count_h;
                }
                else
                {
                    ++mark_count_l;
                }
                
                stateT tempState = Game_Over(game_board, win_row);
                if(Board_Full(game_board))
                {
                    gameIsOver = true;
                }
                if(tempState.gameOver)
                {
                    winning_mark = PLAYER_MARK;
                    gameIsOver = true;
                }
				break;
            }
            case Computer:
            {
                std::cout << "Computer's move" << "\n";
                if((turnsTaken == 0) && (board_size == 4))
                {
                    Make_Turn(2, 2);
                    ++turnsTaken;
                    ++mark_count_l;
                }
                else if((turnsTaken == 1) && (board_size == 4))
                {
                    int v = user_move->Get_Vertical_Pos();
                    int h = user_move->Get_Horizontal_Pos();
                    if((v == 1) && (h == 1))
                    {
                        Make_Turn(v + 1, h + 1);
                        ++turnsTaken;
                        ++mark_count_l;
                    }
                    else if((v == 1) && (h == 4))
                    {
                        Make_Turn(v + 1, h - 1);
                        ++turnsTaken;
                        ++mark_count_l;                        
                    }
                    else if((v == 4) && (h == 1))
                    {
                        Make_Turn(v - 1, h + 1);
                        ++turnsTaken;
                        ++mark_count_h;                        
                    }
                    else if((v == 4) && (h == 4))
                    {
                        Make_Turn(v - 1, h - 1);
                        ++turnsTaken;
                        ++mark_count_h;                         
                    }
                    else if(h == 2)
                    {
                        Make_Turn(v, h + 1);
                        ++turnsTaken;
                        if((v == 1) || (v == 2))
                        {
                            ++mark_count_l;     
                        }
                        if((v == 3) || (v == 4))
                        {
                            ++mark_count_h;                             
                        }                              
                    }
                    else if(h == 3)
                    {
                        Make_Turn(v, h - 1);
                        ++turnsTaken;
                        if((v == 1) || (v == 2))
                        {
                            ++mark_count_l;     
                        }
                        if((v == 3) || (v == 4))
                        {
                            ++mark_count_h;                             
                        }                        
                    }
                    else if((h == 1) && ((v == 2) || (v == 3)))
                    {
                        Make_Turn(v, h + 1);
                        ++turnsTaken;
                        if(v == 2)
                        {
                            ++mark_count_l;     
                        }
                        if(v == 3)
                        {
                            ++mark_count_h;                             
                        }                        
                    }
                    else if((h == 4) && ((v == 2) || (v == 3)))
                    {
                        Make_Turn(v, h - 1);
                        ++turnsTaken;
                        if(v == 2)
                        {
                            ++mark_count_l;     
                        }
                        if(v == 3)
                        {
                            ++mark_count_h;                             
                        }
                    }
                    else
                    {
                        std::cout << "erroria!!43242" << "\n";
                    }
                }        
                else
                {        
                    //Minimax(whoseTurn, game_board, 0);
                    Alphabeta(whoseTurn, game_board, 0, -inf, +inf);
                    if(maxNode != 0)
                    {
                        if(s_scores.size() == 1)
                        {
                            AltMove(game_board);
                            ++turnsTaken;
                        } 
                        else
                        {
                            unsigned int v = maxNode->Get_Vertical_Pos();
                            unsigned int h = maxNode->Get_Horizontal_Pos();
                            Make_Turn(v, h);
                            if(v > (board_size / two))
                            {
                                ++mark_count_h;
                            }
                            else
                            {
                                ++mark_count_l;
                            }           
                            ++turnsTaken;
                        }
                        if(Board_Full(game_board))
                        {
                            gameIsOver = true;
                        }
                        stateT tempState = Game_Over(game_board, win_row);
                        if(tempState.gameOver)
                        {
                            winning_mark = COMPUTER_MARK;
                            gameIsOver = true;
                        }
                        s_scores.clear();
                        break;
                    }
                }
                /*if(minNode != 0)
                {
                    int v = minNode->Get_Vertical_Pos();
                    int h = minNode->Get_Horizontal_Pos();
                    Make_Turn(v, h);
                    stateT tempState = Game_Over(game_board, win_row);
                    if(tempState.gameOver || Board_Full(game_board))
                    {
                        game_board->Print_Board();
                        gameIsOver = true;    
                    }
                    break;
                }*/
                break;
            }
        }
    }
    if(gameIsOver)
    {
        game_board->Print_Board();
        if(winning_mark == COMPUTER_MARK)
        {
            std::cout << "You Lose!" << "\n";
        }
        else if(winning_mark == PLAYER_MARK)
        {
            std::cout << "You Win!" << "\n";
        }
        else
        {
            std::cout << "It's a Draw!" << "\n";
        }
    }
}