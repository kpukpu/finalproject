//--------------------------------------------------------------------
//
//  Laboratory 13                                        wtgraph.cpp
//
//  SOLUTION: Adjacency matrix implementation of the Weighted
//            Graph ADT
//
//--------------------------------------------------------------------

#include <stdlib.h>
#include "queueLnk.cpp"
//--------------------------------------------------------------------

template < class QE >
WtGraph<QE>::WtGraph(int r, int c) {
	Queue<int> box_x(0);
	Queue<int> box_y(0);
	Queue<int> player_x(0);
	Queue<int> player_y(0);
	rs = r;
	cs = c;
	visited = new bool*[rs];
	adjMatrix = new int*[rs];
	for (int i = 0; i < rs; i++) {
		visited[i] = new bool[cs];
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			visited[i][j] = true;//방문하지 않았다고 초기화
		}
	}

	for (int i = 0; i < r; i++) {
		adjMatrix[i] = new int[cs];
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			adjMatrix[i][j] = 0;//모두 빈 셀로 초기화
		}
	}
}

template < class QE >
void WtGraph<QE>::insertMaze() {
	for (int i = 0; i < rs; i++) {
		for (int j = 0; j < cs; j++) {
			cin >> adjMatrix[i][j];
		}
	}
}

template < class QE >
void WtGraph<QE>::makeMaze() {
	int sx, sy;//시작점 x,y 좌표
	int bx, by;//박스지점 x,y 좌표
	int gx, gy;//목표지점 x,y 좌표
	for (int i = 0; i < rs; i++) {
		for (int j = 0; j < cs; j++) {
			if (adjMatrix[i][j] == '#') {
				visited[i][j] = false;//방문함
			}
			if (adjMatrix[i][j] == 'S') {
				sx = i; sy = j;
			}
			if (adjMatrix[i][j] == 'B') {
				bx = i; by = j;
			}
			if (adjMatrix[i][j] == 'T') {
				gx = i; gy = j;
			}
		}
	}

}

template < class QE >
void WtGraph<QE>::FB_BFS(int sx, int sy, int bx, int by, int gx, int gy) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (adjMatrix[i][j] == '#' || adjMatrix[i][j] == 'B') {
				visited[i][j] = false;//벽은 모두 방문한것으로 초기화
									  //박스와 플레이어의 위치가 겹치면 안되기 때문에 박스 위치도 벽으로 초기화
			}
			else//빈 공간은 모두 방문하지 않았다고 초기화
				visited[i][j] = true;
		}
	}
	box_x.enqueue(sx);
	box_y.enqueue(sy);
	while (!box_x.empty() && !box_y.empty()) {
		if (adjMatrix[box_x._front() + 2][box_y._front()] != cs && visited[box_x._front() + 1][box_y._front()] == true) {//오른쪽 탐색
																														 //오른쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 아닐 경우
			cout << "e";
			box_x.enqueue(box_x._front() + 1);
			box_y.enqueue(box_y._front());
			visited[box_x._front()][box_y._front()] == false;//방문함
		}
		if (adjMatrix[box_x._front() - 1][box_y._front()] != 0 && visited[box_x._front() - 1][box_y._front()] == true) {
			//왼쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 아닐 경우
			cout << "w";
			box_x.enqueue(box_x._front() - 1);
			box_y.enqueue(box_y._front());
			visited[box_x._front()][box_y._front()] == false;//방문함
		}
		if (adjMatrix[box_x._front()][box_y._front() + 1] != rs && visited[box_x._front()][box_y._front() + 1] == true) {
			//아래쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 아닐 경우
			cout << "s";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() + 1);
			visited[box_x._front()][box_y._front()] == false;//방문함
		}
		if (adjMatrix[box_x._front()][box_y._front() - 1] != 0 && visited[box_x._front()][box_y._front() - 1] == true) {
			//위쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 안했을 경우
			cout << "n";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() - 1);
			visited[box_x._front()][box_y._front() - 1] == false;//방문함
		}
		//===============================================================================
		if (adjMatrix[box_x._front() + 1][box_y._front()] == adjMatrix[bx][by] || adjMatrix[box_x._front()][box_y._front() + 1] == adjMatrix[bx][by]
			|| adjMatrix[box_x._front()][box_y._front() - 1] == adjMatrix[bx][by] || adjMatrix[box_x._front() - 1][box_y._front()] == adjMatrix[bx][by])//박스를 찾았을 경우
																																						//박스를 찾았을 경우
																																						//출구로 보내야하기 때문에 BFS 한 번 더 써준다.
		{
			FG_BFS(box_x._front(), box_y._front(), bx, by, gx, gy);
		}
		box_x.dequeue();
		box_y.dequeue();
	}
}
//==============================================================
//==============================================================
template < class QE >
void WtGraph<QE>::FG_BFS(int sx, int sy, int bx, int by, int gx, int gy) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (adjMatrix[i][j] == '#') {
				visited[i][j] = false;//벽은 모두 방문한것으로 초기화
			}
			else//빈 공간은 모두 방문하지 않았다고 초기화
				visited[i][j] = true;
		}
	}

	box_x.enqueue(bx);	box_y.enqueue(by);
	player_x.enqueue(sx); player_y.enqueue(sy);
	while (!box_x.empty() && !box_y.empty()) {
		if (visited[box_x._front() + 1][box_y._front()] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]
			) { //오른쪽 탐색
				//박스 기준 오른쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 아닐 경우
				//플레이어 기준 오른쪽으로 갔을 경우 오른쪽에 박스가 있어야함
			cout << "E";
			box_x.enqueue(box_x._front() + 1);
			box_y.enqueue(box_y._front());
			player_x.enqueue(player_x._front + 1);
			player_y.enqueue(player_y._front);

			visited[box_x._front() + 1][box_y._front()] == false;//방문함
		}
		if (visited[box_x._front() - 1][box_y._front()] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]) {
			//왼쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 아닐 경우
			cout << "W";
			box_x.enqueue(box_x._front() - 1);
			box_y.enqueue(box_y._front());
			player_x.enqueue(player_x._front - 1);
			player_y.enqueue(player_y._front);

			visited[box_x._front() - 1][box_y._front()] == false;//방문함
		}
		if (visited[box_x._front()][box_y._front() + 1] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]) {
			//아래쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 아닐 경우
			cout << "S";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() + 1);
			player_x.enqueue(player_x._front);
			player_y.enqueue(player_y._front + 1);
			visited[box_x._front()][box_y._front() + 1] == false;//방문함
		}
		if (visited[box_x._front()][box_y._front() - 1] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]) {
			//위쪽으로 갔을 경우 미로의 끝이 아니고 방문을(막힌 벽이) 안했을 경우
			cout << "N";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() - 1);
			player_x.enqueue(player_x._front);
			player_y.enqueue(player_y._front - 1);
			visited[box_x._front()][box_y._front() - 1] == false;//방문함
		}
		if (adjMatrix[box_x._front()][box_y._front()] == adjMatrix[gx][gy])
		{
			cout << "goal" << endl;
			break;
		}
		if ((visited[box_x._front() + 1][box_y._front()] == false
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()])
			||
			(visited[box_x._front()][box_y._front() + 1] == false
				&& adjMatrix[player_x._front()][player_y._front() + 1] == adjMatrix[box_x._front()][box_y._front()])
			||
			(visited[box_x._front() - 1][box_y._front()] == false
				&& adjMatrix[player_x._front() - 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()])
			||
			(visited[box_x._front()][box_y._front() - 1] == false
				&& adjMatrix[player_x._front()][player_y._front() - 1] == adjMatrix[box_x._front()][box_y._front()])
			)
			//막힌 길 이라면
			//막힌 길이라면 플레이어의 위치를 바꾸어 다시 박스를 찾아야한다.
		{
			FB_BFS(player_x._front(), player_y._front(), box_x._front(), box_y._front(), gx, gy);
		}
		box_x.dequeue();
		box_y.dequeue();
		player_x.dequeue();
		player_y.dequeue();
	}
}