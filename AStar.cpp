#include <iostream>
#include <queue>

using namespace std;

struct cap {
	int* row;
	int c; //cost
	int h; //heuristic
	int ik; //king place
	cap(int * _row, int _c, int _h, int _ik) {
		row = _row;
		c = _c;
		h = _h;
		ik = _ik;
	}
};

int n, c = 0;
int* goal;
priority_queue<cap, vector<cap>, greater<cap> > frontier;
int mode[4][4] = { { -4, -3, -1, 4 }, { -4, 1, 3, 4 }, { -4, -1, 1, 4 }, { -4, -1, 1, 4 } };

bool operator<(cap const& p1, cap const& p2) {
	return p1.c + p1.h < p2.c + p2.h;
}

bool operator>(cap const& p1, cap const& p2) {
	return p1.c + p1.h > p2.c + p2.h;
}

int heuristic(int* row) {
	int x = 0;
	for (int i = 0; i < n; i++) if (row[i] != goal[i]) x++;
	return x;
}

bool isGoal(cap x) {
	if (heuristic(x.row) == 0) return 1;
	return 0;
}

void copyRow(int* a, int* b) {
	for (int i = 0; i < n; i++) a[i] = b[i];
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main() {
	int* srow;
	cin >> n;
	goal = new int[n];
	for (int i = 0; i < n; i++) cin >> goal[i];
	//start state
	srow = new int[n];
	for (int i = 0; i < n; i++) srow[i] = i + 1;
	int ik = 1;
	cap curr = *(new cap(srow, c, heuristic(srow), ik));
	frontier.push(curr);
	//A*
	while (!isGoal(curr)) {
		c++;
		for (int i = 0; i < 4; i++) {
			int m = ik + mode[curr.ik % 4][i];
			if (0 < m && m <= n) {
				int* trow = new int[n];
				copyRow(trow, curr.row);
				swap(trow[m - 1], trow[ik - 1]);
				frontier.push(*(new cap(trow, c, heuristic(trow), m)));
			}
		}
		curr = frontier.top();
		c = curr.c;
		ik = curr.ik;
		frontier.pop();
	}
	cout << curr.c;
	return 0;
}
