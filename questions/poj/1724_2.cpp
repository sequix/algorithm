// POJ No.1724 ROADS (DFS+剪枝) (4920K 532MS)
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_N = 100;

struct Road { int dest, length, toll; };
struct City { int nroads; Road roads[MAX_N+5]; };
City city[MAX_N+5];
int K, N, R;
int curLen, curToll, ans;
bool visited[MAX_N+5];
int minLen[MAX_N+5][MAX_N*MAX_N+5]; // minLen[i][j] 从1到i，花费j的最短路长度

void dfs(int n)
{
	if(n == N) {
		ans = min(ans, curLen);
		return;
	}
	for(int i = 0; i < city[n].nroads; ++i) {
		int d = city[n].roads[i].dest;
		if(visited[d]) continue;
		int toll = curToll + city[n].roads[i].toll;
		int len = curLen + city[n].roads[i].length;
		if(toll > K) continue;
		if(len >= ans || len >= minLen[d][toll]) continue;
		minLen[d][toll] = len;

		curLen += city[n].roads[i].length;
		curToll += city[n].roads[i].toll;
		visited[d] = 1;
		dfs(d);	
		visited[d] = 0;
		curLen -= city[n].roads[i].length;
		curToll -= city[n].roads[i].toll;
	}
}

int main()
{
	cin >> K >> N >> R;
	for(int i = 0; i < R; ++i) {
		int s; Road r;
		cin >> s >> r.dest >> r.length >> r.toll;
		if(s != r.dest) city[s].roads[city[s].nroads++] = r;
	}
	memset(minLen, 0x3f, sizeof(minLen));
	memset(visited, 0, sizeof(visited));
	visited[1] = 1;
	curLen = curToll = 0;
	ans = 0x3f3f3f3f;
	dfs(1);
	if(ans == 0x3f3f3f3f)
		cout << -1 << endl;
	else
		cout << ans << endl;
	return 0;
}
