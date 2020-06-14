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
			visited[i][j] = true;//�湮���� �ʾҴٰ� �ʱ�ȭ
		}
	}

	for (int i = 0; i < r; i++) {
		adjMatrix[i] = new int[cs];
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			adjMatrix[i][j] = 0;//��� �� ���� �ʱ�ȭ
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
	int sx, sy;//������ x,y ��ǥ
	int bx, by;//�ڽ����� x,y ��ǥ
	int gx, gy;//��ǥ���� x,y ��ǥ
	for (int i = 0; i < rs; i++) {
		for (int j = 0; j < cs; j++) {
			if (adjMatrix[i][j] == '#') {
				visited[i][j] = false;//�湮��
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
				visited[i][j] = false;//���� ��� �湮�Ѱ����� �ʱ�ȭ
									  //�ڽ��� �÷��̾��� ��ġ�� ��ġ�� �ȵǱ� ������ �ڽ� ��ġ�� ������ �ʱ�ȭ
			}
			else//�� ������ ��� �湮���� �ʾҴٰ� �ʱ�ȭ
				visited[i][j] = true;
		}
	}
	box_x.enqueue(sx);
	box_y.enqueue(sy);
	while (!box_x.empty() && !box_y.empty()) {
		if (adjMatrix[box_x._front() + 2][box_y._front()] != cs && visited[box_x._front() + 1][box_y._front()] == true) {//������ Ž��
																														 //���������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) �ƴ� ���
			cout << "e";
			box_x.enqueue(box_x._front() + 1);
			box_y.enqueue(box_y._front());
			visited[box_x._front()][box_y._front()] == false;//�湮��
		}
		if (adjMatrix[box_x._front() - 1][box_y._front()] != 0 && visited[box_x._front() - 1][box_y._front()] == true) {
			//�������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) �ƴ� ���
			cout << "w";
			box_x.enqueue(box_x._front() - 1);
			box_y.enqueue(box_y._front());
			visited[box_x._front()][box_y._front()] == false;//�湮��
		}
		if (adjMatrix[box_x._front()][box_y._front() + 1] != rs && visited[box_x._front()][box_y._front() + 1] == true) {
			//�Ʒ������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) �ƴ� ���
			cout << "s";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() + 1);
			visited[box_x._front()][box_y._front()] == false;//�湮��
		}
		if (adjMatrix[box_x._front()][box_y._front() - 1] != 0 && visited[box_x._front()][box_y._front() - 1] == true) {
			//�������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) ������ ���
			cout << "n";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() - 1);
			visited[box_x._front()][box_y._front() - 1] == false;//�湮��
		}
		//===============================================================================
		if (adjMatrix[box_x._front() + 1][box_y._front()] == adjMatrix[bx][by] || adjMatrix[box_x._front()][box_y._front() + 1] == adjMatrix[bx][by]
			|| adjMatrix[box_x._front()][box_y._front() - 1] == adjMatrix[bx][by] || adjMatrix[box_x._front() - 1][box_y._front()] == adjMatrix[bx][by])//�ڽ��� ã���� ���
																																						//�ڽ��� ã���� ���
																																						//�ⱸ�� �������ϱ� ������ BFS �� �� �� ���ش�.
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
				visited[i][j] = false;//���� ��� �湮�Ѱ����� �ʱ�ȭ
			}
			else//�� ������ ��� �湮���� �ʾҴٰ� �ʱ�ȭ
				visited[i][j] = true;
		}
	}

	box_x.enqueue(bx);	box_y.enqueue(by);
	player_x.enqueue(sx); player_y.enqueue(sy);
	while (!box_x.empty() && !box_y.empty()) {
		if (visited[box_x._front() + 1][box_y._front()] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]
			) { //������ Ž��
				//�ڽ� ���� ���������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) �ƴ� ���
				//�÷��̾� ���� ���������� ���� ��� �����ʿ� �ڽ��� �־����
			cout << "E";
			box_x.enqueue(box_x._front() + 1);
			box_y.enqueue(box_y._front());
			player_x.enqueue(player_x._front + 1);
			player_y.enqueue(player_y._front);

			visited[box_x._front() + 1][box_y._front()] == false;//�湮��
		}
		if (visited[box_x._front() - 1][box_y._front()] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]) {
			//�������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) �ƴ� ���
			cout << "W";
			box_x.enqueue(box_x._front() - 1);
			box_y.enqueue(box_y._front());
			player_x.enqueue(player_x._front - 1);
			player_y.enqueue(player_y._front);

			visited[box_x._front() - 1][box_y._front()] == false;//�湮��
		}
		if (visited[box_x._front()][box_y._front() + 1] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]) {
			//�Ʒ������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) �ƴ� ���
			cout << "S";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() + 1);
			player_x.enqueue(player_x._front);
			player_y.enqueue(player_y._front + 1);
			visited[box_x._front()][box_y._front() + 1] == false;//�湮��
		}
		if (visited[box_x._front()][box_y._front() - 1] == true
			&& adjMatrix[player_x._front() + 1][player_y._front()] == adjMatrix[box_x._front()][box_y._front()]) {
			//�������� ���� ��� �̷��� ���� �ƴϰ� �湮��(���� ����) ������ ���
			cout << "N";
			box_x.enqueue(box_x._front());
			box_y.enqueue(box_y._front() - 1);
			player_x.enqueue(player_x._front);
			player_y.enqueue(player_y._front - 1);
			visited[box_x._front()][box_y._front() - 1] == false;//�湮��
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
			//���� �� �̶��
			//���� ���̶�� �÷��̾��� ��ġ�� �ٲپ� �ٽ� �ڽ��� ã�ƾ��Ѵ�.
		{
			FB_BFS(player_x._front(), player_y._front(), box_x._front(), box_y._front(), gx, gy);
		}
		box_x.dequeue();
		box_y.dequeue();
		player_x.dequeue();
		player_y.dequeue();
	}
}