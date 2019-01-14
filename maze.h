/**
 * @file maze.h
 * Represents each squareMaze object
 * @author Zixin Zhang
 */
#ifndef MAZE_H
#define MAZE_H


#include <vector>
#include <cstdlib>



#include "dsets.h"
#include "utilities/PNG.h"
using namespace cs225;
using std::vector;
/*
Each SquareMaze object represents a randomly-generated square maze and its solution.

(Note that by "square maze" we mean a maze in which each cell is a square; the maze
itself need not be a square.)
*/



class SquareMaze{
public:

	SquareMaze();


	void makeMaze(int width, int height);


	bool canTravel(int x, int y, int dir) const;


	void setWall(int x, int y, int dir, bool exists);


	vector<int> solveMaze();


	PNG* drawMaze() const;


	PNG* drawMazeWithSolution();

private:
	vector<bool> downWalls;
	vector<bool> rightWalls;


	int m_width;
	int m_height;
	int size;

	DisjointSets rec;

	bool isDown(int a, int b, int c);
	bool isRight(int a, int b, int c);

	void randomly_Down(int a, int b, int c);
	void randomly_Right(int a, int b, int c);

	void make_black(int a, int b, PNG* ori) const;
	void make_red(int a, int b, PNG* ori) const;
	void make_white(int a, int b, PNG* ori) const;

	void go_Road(vector<int> & a, int x, int y, int dir, int rd, bool knock);
	void knockDown(vector<int> & a, int x, int y, int rd, bool knock);

	void find_Path(vector<int> & a, int * dest, int x, int y);
	bool solve_No_Cycle(vector<int> & a, int dest, int x, int y);


};

#endif
