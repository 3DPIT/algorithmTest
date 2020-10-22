#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
#define NS 10
int visit[NS][NS];//방문 배열 
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int c = 0;
void DFS(int y, int x, int cnt,int size,int **matrix) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir]; int nx = x + dx[dir];
		if (0 <= ny && ny < size && 0 <= nx && nx < size&&matrix[ny][nx] == 1 && visit[ny][nx] == 0) {
			visit[ny][nx] = cnt;
			c++;
			DFS(ny, nx, cnt, size, matrix);
		}
	 }
}
void solution(int sizeOfMatrix, int **matrix) {
	// TODO: 이곳에 코드를 작성하세요.
	int cnt = 0;
	int ret = 0;
	vector<int>D;
	for (int i = 0; i < sizeOfMatrix; i++) {
		for (int j = 0; j < sizeOfMatrix; j++) {
			if (matrix[i][j] == 1 && visit[i][j] == 0) {
				c = 0;//배열 몇개 인지 체크를 위함
				++cnt;
				visit[i][j] = cnt;
				DFS(i, j, cnt,sizeOfMatrix,matrix);
				D.push_back(c);//몇개인지 확인
			}
		}
	}
	sort(D.begin(), D.end());
	cout << cnt << endl;
	if (cnt != 0) {
		for (int i = 0; i < D.size(); i++) {
			cout << D[i] + 1 << " ";
		}
		cout << endl;
	}
}

struct input_data {
	int sizeOfMatrix;
	int **matrix;
};

void process_stdin(struct input_data& inputData) {
	string line;
	istringstream iss;

	getline(cin, line);
	iss.str(line);
	iss >> inputData.sizeOfMatrix;

	inputData.matrix = new int*[inputData.sizeOfMatrix];
	for (int i = 0; i < inputData.sizeOfMatrix; i++) {
		getline(cin, line);
		iss.clear();
		iss.str(line);
		inputData.matrix[i] = new int[inputData.sizeOfMatrix];
		for (int j = 0; j < inputData.sizeOfMatrix; j++) {
			iss >> inputData.matrix[i][j];
		}
	}
}

int main() {
	struct input_data inputData;
	process_stdin(inputData);

	solution(inputData.sizeOfMatrix, inputData.matrix);
	return 0;
}