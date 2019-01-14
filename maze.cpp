/**
 * @file maze.cpp
 * Represents each squareMaze object
 * @author Zixin Zhang
 */
#include "maze.h"



SquareMaze::SquareMaze(){
	//Nothing
}

bool SquareMaze::isDown(int a, int b, int c){
	return downWalls[a * c + b] && rec.find(a * c + b) != rec.find((a + 1) * c + b);
}

bool SquareMaze::isRight(int a, int b, int c){
	return rightWalls[a * c + b] && rec.find(a * c + b) != rec.find(a * c + b + 1);
}

void SquareMaze::randomly_Right(int a, int b, int c){
	rightWalls[a * c + b] = false;
	rec.setunion(a * c + b, a * c + b + 1);
}

void SquareMaze::randomly_Down(int a, int b, int c){
	downWalls[a * c + b] = false;
	rec.setunion(a * c + b, (a + 1) * c + b);
}


void SquareMaze::makeMaze(int width, int height){
	size = (width * height);
	rec.addelements(size);
	m_width = width;
	m_height = height;

	for(int i = 0; i < size; ++i){
		downWalls.push_back(true);
		rightWalls.push_back(true);
	}

	int count = 0;
	int temp = 0;

  static bool seeded = false;
  if(!seeded) {
      srand(time(NULL));
      seeded = true;
  }


	while(count < size/2){
		int row = rand() % (m_height - 1);
		int col = rand() % (m_width - 1);

		temp = rand() % 2;

		if(temp){
			if(isRight(row, col, m_width)){
				randomly_Right(row, col, m_width);
				count++;
			}
		} else if(isDown(row, col, m_width)){
			randomly_Down(row, col, m_width);
			count++;
		}
	}

	int rowNum = 0;

	for(; rowNum < m_height - 1; ++rowNum){
		int colNum = 0;
		for(; colNum < m_width - 1; ++colNum){
			if(temp){
				if(isRight(rowNum, colNum, m_width)){
					randomly_Right(rowNum, colNum, m_width);
				}
				if(isDown(rowNum, colNum, m_width)){
					randomly_Down(rowNum, colNum, m_width);
				}
			} else {
				if(isDown(rowNum, colNum, m_width)){
					randomly_Down(rowNum, colNum, m_width);
				}
				if(isRight(rowNum, colNum, m_width)){
					randomly_Right(rowNum, colNum, m_width);
				}
			}
		}
		if(isDown(rowNum, colNum, m_width)){
			randomly_Down(rowNum, colNum, m_width);
		}
	}

	for(int colNum = 0; colNum < m_width - 1; ++colNum){
		if(isRight(rowNum, colNum, m_width)){
			randomly_Right(rowNum, colNum, m_width);
		}
	}

}

bool SquareMaze::canTravel(int x, int y, int dir) const{
	if(dir == 0 && x != m_width - 1){
		return (!rightWalls[y * m_width + x]);
	}
	if(dir == 1 && y != m_height - 1){
		return (!downWalls[y * m_width + x]);
	}
	if(dir == 2 && x != 0){
		return (!rightWalls[y * m_width + x - 1]);
	}
	if(dir == 3 && y != 0){
		return (!downWalls[(y - 1) * m_width + x]);
	}
	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
	int boundary = x + y * m_width;
	if(dir == 0 && x != m_width - 1){
		rightWalls[boundary] = exists? true : false;
	}
	if(dir == 1 && y != m_height - 1){
		downWalls[boundary] = exists? true : false;
	}
}

void SquareMaze::go_Road(vector<int> & a, int x, int y, int dir, int rd, bool knock){
	a.push_back(dir);
	setWall(x, y, rd, knock);
}

void SquareMaze::knockDown(vector<int> & a, int x, int y, int rd, bool knock){
	a.pop_back();
	setWall(x, y, rd, knock);
}

void SquareMaze::find_Path(vector<int> & a, int * dest, int x, int y){
	if(y == m_height - 1){
		dest[x] = a.size();
	}

	if(canTravel(x, y, 0)){
		go_Road(a, x, y, 0, 0, true);

		find_Path(a, dest, x + 1, y);
		knockDown(a, x, y, 0, false);
	}

	if(canTravel(x, y, 1)){
		go_Road(a, x, y, 1, 1, true);

		find_Path(a, dest, x, y + 1);
		knockDown(a, x, y, 1, false);
	}

	if(canTravel(x, y, 2)){
		go_Road(a, x - 1, y, 2, 0, true);

		find_Path(a, dest, x - 1, y);
		knockDown(a, x - 1, y, 0, false);
	}

	if(canTravel(x, y, 3)){
		go_Road(a, x, y - 1, 3, 1, true);

		find_Path(a, dest, x, y - 1);
		knockDown(a, x, y - 1, 1, false);
	}
}

bool SquareMaze::solve_No_Cycle(vector<int> & a, int dest, int x, int y){
	if(x == dest && y == m_height -1){
		return true;
	}

	if(canTravel(x, y, 0)){
		go_Road(a, x, y, 0, 0, true);

		if(solve_No_Cycle(a, dest, x + 1, y)){
			setWall(x, y, 0, false);
			return true;
		}

		knockDown(a, x, y, 0, false);
	}

	if(canTravel(x, y, 1)){
		go_Road(a, x, y, 1, 1, true);

		if(solve_No_Cycle(a, dest, x, y + 1)){
			setWall(x, y, 1, false);
			return true;
		}

		knockDown(a, x, y, 1, false);
	}

	if(canTravel(x, y, 2)){
		go_Road(a, x - 1, y, 2, 0, true);

		if(solve_No_Cycle(a, dest, x - 1, y)){
			setWall(x-1, y, 0, false);
			return true;
		}

		knockDown(a, x - 1, y, 0, false);
	}

	if(canTravel(x, y, 3)){
		go_Road(a, x, y - 1, 3, 1, true);

		if(solve_No_Cycle(a, dest, x, y-1)){
			setWall(x, y-1, 1, false);
			return true;
		}

		knockDown(a, x, y - 1, 1, false);
	}

	return false;
}

vector<int> SquareMaze::solveMaze(){
	vector<int> solution;
	int *destRow = new int[m_width];
	find_Path(solution, destRow, 0, 0);

	int theDest = 0;
	for(int i = 1; i < m_width; ++i){
		if(destRow[theDest] < destRow[i]){
			theDest = i;
		}
	}

	solution.clear();
	solve_No_Cycle(solution, theDest, 0, 0);

	delete [] destRow;
	destRow = NULL;

	return solution;
}


void SquareMaze::make_black(int a, int b, PNG *ori) const{
	(*ori).getPixel(a, b)->h = 0;
	(*ori).getPixel(a, b)->s = 0;
	(*ori).getPixel(a, b)->l = 0;
  (*ori).getPixel(a, b)->a = 1;
}


void SquareMaze::make_red(int a, int b, PNG *ori) const{
  (*ori).getPixel(a, b)->h = 0;
	(*ori).getPixel(a, b)->s = 1;
	(*ori).getPixel(a, b)->l = 0.5;
  (*ori).getPixel(a, b)->a = 1;
}


void SquareMaze::make_white(int a, int b, PNG *ori) const{
  (*ori).getPixel(a, b)->h = 0;
	(*ori).getPixel(a, b)->s = 0;
	(*ori).getPixel(a, b)->l = 1;
  (*ori).getPixel(a, b)->a = 1;
}

PNG* SquareMaze::drawMaze() const{
	PNG *retVal = new PNG(m_width * 10 + 1, m_height * 10 + 1);

	for(int i = 0; i < m_height * 10; ++i){
		make_black(0, i, retVal);
	}

	for(int j = 10; j < m_width*10; ++j){
		make_black(j, 0, retVal);
	}

	for(int i = 0; i < size; ++i){
		if(rightWalls[i]){
			for(int k = 0; k <= 10; k++){
				make_black((i % m_width + 1) * 10, i / m_width * 10 + k, retVal);
			}
		}
		if(downWalls[i]){
			for(int k = 0; k <= 10; k++){
				make_black(i % m_width * 10 + k, (i / m_width + 1) * 10, retVal);
			}
		}
	}

	return retVal;
}

PNG* SquareMaze::drawMazeWithSolution(){
	PNG *retVal = drawMaze();
	vector<int> solution = solveMaze();
	int x = 5;
	int y = 5;

	for(size_t i = 0; i < solution.size(); i++){
		if(solution[i] == 0){
			for(int j = 0; j < 11; j++){
				make_red(x + j, y, retVal);
			}
			x += 10;
		} else if(solution[i] == 1){
			for(int j = 0; j < 11; j++){
				make_red(x, y + j, retVal);
			}
			y += 10;
		} else if(solution[i] == 2){
			for(int j = 0; j < 11; j++){
				make_red(x - j, y, retVal);
			}
			x -= 10;
		} else{
			for(int j = 0; j < 11; j++){
				make_red(x, y - j, retVal);
			}
				y -= 10;
		}
	}


	for(int k = 1; k < 10; k++){
		make_white((x / 10) * 10 + k, m_height * 10, retVal);
	}

	return retVal;
}
