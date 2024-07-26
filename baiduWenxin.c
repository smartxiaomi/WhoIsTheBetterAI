#include <iostream>  
#include <string>  
  
int main() {  
    int N, M, K;  
    std::string X;  
    std::cin >> N >> X >> M >> K;  
  
    if (K == N) {  
        std::cout << "mei you mai " << X << " de";  
    } else if (K == M) {  
        std::cout << "kan dao le mai " << X << " de";  
    } else {  
        std::cout << "wang le zhao mai " << X << " de";  
    }  
  
    return 0;  
}
#include <iostream>  
using namespace std;  
  
int main() {  
    int N;  
    cin >> N;  
    while (N--) {  
        int A, B, C;  
        cin >> A >> B >> C;  
        if (C == A * B) {  
            cout << "Lv Yan" << endl;  
        } else if (C == A + B) {  
            cout << "Tu Dou" << endl;  
        } else {  
            cout << "zhe du shi sha ya!" << endl;  
        }  
    }  
    return 0;  
}
#include <iostream>  
#include <vector>  
using namespace std;  
  
int main() {  
    int N;  
    cin >> N;  
    vector<int> hats(N);  
    for (int i = 0; i < N; ++i) {  
        cin >> hats[i];  
    }  
  
    int K;  
    cin >> K;  
    while (K--) {  
        vector<int> guesses(N);  
        bool someoneGuessed = false;  
        bool correctGuess = false;  
        for (int i = 0; i < N; ++i) {  
            cin >> guesses[i];  
            if (guesses[i] != 0) {  
                someoneGuessed = true;  
                if (guesses[i] == hats[i]) {  
                    correctGuess = true;  
                } else {  
                    // Someone guessed wrong, no need to check further  
                    cout << "Ai Ya" << endl;  
                    break;  
                }  
            }  
        }  
        if (!someoneGuessed) {  
            cout << "Ai Ya" << endl;  
        } else if (correctGuess) {  
            cout << "Da Jiang!!!" << endl;  
        }  
    }  
  
    return 0;  
}
#include <iostream>  
#include <string>  
using namespace std;  
  
int main() {  
    string s;  
    cin >> s;  
    int n;  
    cin >> n;  
    string clipboard = "";  
  
    for (int i = 0; i < n; ++i) {  
        int start, end;  
        string before, after;  
        cin >> start >> end >> before >> after;  
  
        // Adjust position to zero-based index  
        start--;  
        end--;  
  
        // Cut operation  
        clipboard = s.substr(start, end - start + 1);  
        s.erase(start, end - start + 1);  
  
        // Paste operation  
        size_t pos = s.find(before + after);  
        if (pos != string::npos) {  
            s.insert(pos + before.length(), clipboard);  
        } else {  
            s += clipboard;  
        }  
        clipboard = ""; // Clear clipboard after paste  
    }  
  
    cout << s << endl;  
    return 0;  
}
#include <stdio.h>  
#include <limits.h>  
#include <math.h>  
int main() {  
    int n0, n1, n; // 女生人数、男生人数、寝室数  
    scanf("%d %d %d", &n0, &n1, &n);  
  
    int bestFemaleRooms = -1, bestMaleRooms = -1; // 最优解的女生和男生寝室数  
    int minDiff = INT_MAX; // 最小人数差，初始化为最大整数  
  
    // 遍历所有可能的女生寝室人数  
    for (int femalePerRoom = 2; femalePerRoom <= n0; ++femalePerRoom) {  
        if (n0 % femalePerRoom != 0) continue; // 如果不能整除，则跳过  
  
        int femaleRooms = n0 / femalePerRoom; // 女生寝室数  
        int maleRooms = n - femaleRooms; // 剩余寝室数用于男生  
  
        // 遍历所有可能的男生寝室人数  
        for (int malePerRoom = 2; malePerRoom <= n1; ++malePerRoom) {  
            if (n1 % malePerRoom != 0) continue; // 如果不能整除，则跳过  
            if (maleRooms == n1 / malePerRoom) { // 如果男生寝室数匹配  
                int diff = abs(femalePerRoom - malePerRoom); // 计算人数差  
                if (diff < minDiff) { // 如果找到了更优解  
                    minDiff = diff;  
                    bestFemaleRooms = femaleRooms;  
                    bestMaleRooms = maleRooms;  
                }  
            }  
        }  
    }  
  
    // 输出结果  
    if (bestFemaleRooms != -1 && bestMaleRooms != -1) {  
        printf("%d %d\n", bestFemaleRooms, bestMaleRooms);  
    } else {  
        printf("No Solution\n");  
    }  
  
    return 0;  
}
#include <iostream>  
using namespace std;  
  
// 计算整数的各位数字之和  
int sumOfDigits(int n) {  
    int sum = 0;  
    while (n > 0) {  
        sum += n % 10;  
        n /= 10;  
    }  
    return sum;  
}  
  
// 判断谁是“爹”  
char determineWinner(int NA, int NB) {  
    int SA = sumOfDigits(NA);  
    int SB = sumOfDigits(NB);  
  
    if (NA == SB * (NA / SB) && NA % SB == 0) {  
        return 'A';  
    } else if (NB == SA * (NB / SA) && NB % SA == 0) {  
        return 'B';  
    } else {  
        return NA > NB ? 'A' : 'B';  
    }  
}  
  
int main() {  
    int N;  
    cin >> N;  
    for (int i = 0; i < N; i++) {  
        int NA, NB;  
        cin >> NA >> NB;  
        cout << determineWinner(NA, NB) << endl;  
    }  
    return 0;  
}
#include <iostream>  
#include <stack>  
#include <vector>  
using namespace std;  
  
int main() {  
    int N;  
    cin >> N;  
    vector<int> diameters(N);  
    for (int i = 0; i < N; i++) {  
        cin >> diameters[i];  
    }  
  
    stack<int> A, B;  
    vector<int> towers; // 用于记录每个宝塔的层数  
  
    for (int i = 0; i < N; i++) {  
        int current = diameters[i];  
        if (A.empty() || current <= A.top()) {  
            A.push(current);  
        } else {  
            while (!B.empty() && current > B.top()) {  
                A.push(B.top());  
                B.pop();  
            }  
            if (B.empty() || current <= B.top()) {  
                B.push(current);  
            } else {  
                while (!A.empty()) {  
                    towers.push_back(A.size());  
                    A.pop();  
                }  
                while (!B.empty()) {  
                    A.push(B.top());  
                    B.pop();  
                }  
                A.push(current);  
            }  
        }  
    }  
  
    // 处理剩余的A柱和B柱  
    while (!A.empty()) {  
        towers.push_back(A.size());  
        A.pop();  
    }  
    while (!B.empty()) {  
        towers.push_back(B.size());  
        B.pop();  
    }  
  
    cout << towers.size() << " " << *max_element(towers.begin(), towers.end()) << endl;  
  
    return 0;  
}
#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <map>  
#include <string>  
  
using std::cin;  
using std::cout;  
using std::endl;  
using std::vector;  
using std::map;  
using std::string;  
using std::pair;  
using std::make_pair;  
  
int main() {  
    int N, C;  
    cin >> N >> C;  
  
    vector<pair<string, int>> schools(N);  
    for (int i = 0; i < N; ++i) {  
        cin >> schools[i].first >> schools[i].second;  
    }  
  
    // 根据学校未安排的人数进行排序，人数多的排在前面  
    sort(schools.begin(), schools.end(), [](const pair<string, int>& a, const pair<string, int>& b) {  
        return a.second > b.second;  
    });  
  
    map<int, int> classrooms; // 考场编号到剩余座位数的映射  
    vector<int> supervisorCounts(N, 0); // 每所学校需要联系的监考人数  
    int classroomCount = 0; // 考场编号（从1开始）  
  
    for (int i = 0; i < N; ++i) {  
        int remaining = schools[i].second;  
        if (remaining >= C) {  
            // 如果剩余人数大于等于考场容量，则新开一个考场  
            ++classroomCount;  
            classrooms[classroomCount] = C - remaining;  
            supervisorCounts[i] = 1;  
        } else {  
            // 否则，寻找剩余座位数大于等于剩余人数的最小编号考场  
            auto it = classrooms.lower_bound(0); // 从编号最小的考场开始查找  
            while (it != classrooms.end() && it->second < remaining) {  
                ++it;  
            }  
            if (it == classrooms.end()) {  
                // 如果没有找到，则新开一个考场  
                ++classroomCount;  
                classrooms[classroomCount] = C - remaining;  
                supervisorCounts[i] = 1;  
            } else {  
                // 找到了合适的考场，安排学生进去，并更新剩余座位数  
                supervisorCounts[i] = it->first;  
                classrooms[it->first] -= remaining;  
                if (classrooms[it->first] == 0) {  
                    // 如果考场座位全满了，则从映射中删除该考场  
                    classrooms.erase(it);  
                }  
            }  
        }  
    }  
  
    // 输出每所学校需要联系的监考人数  
    for (int i = 0; i < N; ++i) {  
        cout << schools[i].first << " " << supervisorCounts[i] << endl;  
    }  
  
    // 输出总共开设的考场数  
    cout << classroomCount << endl;  
  
    return 0;  
}
#include <iostream>  
#include <vector>  
#include <algorithm>  
  
using std::cin;  
using std::cout;  
using std::vector;  
  
void restorePlayers(vector<vector<int>>& losers, int k, int winner) {  
    int n = 1 << k;  
    vector<int> players(n, 0);  
    vector<bool> used(n + 1, false);  
  
    // 从最终胜者开始回溯  
    players[n - 1] = winner;  
    used[winner] = true;  
  
    for (int i = k; i > 0; --i) {  
        for (int j = 0; j < (1 << (k - i)); ++j) {  
            int winnerIdx = (1 << (k - i + 1)) - 1 + j * 2;  
            int loserIdx = losers[i - 1][j] - 1;  
            int otherLoserIdx = winnerIdx - 1;  
  
            if (players[winnerIdx] == 0) {  
                // 确定胜者  
                if (players[loserIdx] != 0 && players[otherLoserIdx] != 0) {  
                    if (players[loserIdx] > players[otherLoserIdx]) {  
                        players[winnerIdx] = players[loserIdx];  
                    } else {  
                        players[winnerIdx] = players[otherLoserIdx];  
                    }  
                } else if (players[loserIdx] != 0) {  
                    players[winnerIdx] = players[loserIdx];  
                } else if (players[otherLoserIdx] != 0) {  
                    players[winnerIdx] = players[otherLoserIdx];  
                }  
            }  
  
            // 确定另一名选手  
            if (players[loserIdx] == 0 && !used[players[winnerIdx]]) {  
                players[loserIdx] = players[winnerIdx];  
                used[players[winnerIdx]] = true;  
            }  
            if (players[otherLoserIdx] == 0 && !used[players[winnerIdx]]) {  
                players[otherLoserIdx] = players[winnerIdx];  
                used[players[winnerIdx]] = true;  
            }  
        }  
    }  
  
    // 填充剩余能力值  
    for (int i = 0; i < n; ++i) {  
        if (players[i] == 0) {  
            for (int val = 1; val <= n; ++val) {  
                if (!used[val]) {  
                    players[i] = val;  
                    used[val] = true;  
                    break;  
                }  
            }  
        }  
    }  
  
    // 检查是否所有能力值都已分配  
    for (int i = 1; i <= n; ++i) {  
        if (!used[i]) {  
            cout << "No Solution" << std::endl;  
            return;  
        }  
    }  
  
    // 输出结果  
    for (int i = 0; i < n; ++i) {  
        cout << players[i] << (i < n - 1 ? " " : "\n");  
    }  
}  
  
int main() {  
    int k;  
    cin >> k;  
  
    vector<vector<int>> losers(k);  
    for (int i = 0; i < k; ++i) {  
        int size = 1 << (k - i - 1);  
        losers[i].resize(size);  
        for (int j = 0; j < size; ++j) {  
            cin >> losers[i][j];  
        }  
    }  
  
    int winner;  
    cin >> winner;  
  
    restorePlayers(losers, k, winner);  
  
    return 0;  
}
#include <iostream>  
#include <vector>  
  
using std::cin;  
using std::cout;  
using std::vector;  
  
struct Point {  
    int x, y;  
};  
  
// 方向数组，用于遍历上下左右四个方向  
const vector<Point> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  
  
bool isValid(int x, int y, int n, int m) {  
    return x >= 0 && x < n && y >= 0 && y < m;  
}  
  
void dfs(vector<vector<int>>& map, vector<vector<bool>>& visited, int x, int y, int n, int m, bool& hasTreasure) {  
    visited[x][y] = true;  
    if (map[x][y] >= 2 && map[x][y] <= 9) {  
        hasTreasure = true;  
    }  
    for (const auto& dir : directions) {  
        int newX = x + dir.x;  
        int newY = y + dir.y;  
        if (isValid(newX, newY, n, m) && !visited[newX][newY] && map[newX][newY] != 0) {  
            dfs(map, visited, newX, newY, n, m, hasTreasure);  
        }  
    }  
}  
  
int main() {  
    int n, m;  
    cin >> n >> m;  
    vector<vector<int>> map(n, vector<int>(m));  
    for (int i = 0; i < n; ++i) {  
        for (int j = 0; j < m; ++j) {  
            cin >> map[i][j];  
        }  
    }  
  
    vector<vector<bool>> visited(n, vector<bool>(m, false));  
    int totalIslands = 0;  
    int treasureIslands = 0;  
  
    for (int i = 0; i < n; ++i) {  
        for (int j = 0; j < m; ++j) {  
            if (!visited[i][j] && map[i][j] != 0) {  
                bool hasTreasure = false;  
                dfs(map, visited, i, j, n, m, hasTreasure);  
                ++totalIslands;  
                if (hasTreasure) {  
                    ++treasureIslands;  
                }  
            }  
        }  
    }  
  
    cout << totalIslands << " " << treasureIslands << std::endl;  
  
    return 0;  
}
#include <iostream>  
#include <vector>  
#include <queue>  
#include <algorithm>  
#include <climits>  
  
using std::cin;  
using std::cout;  
using std::vector;  
using std::priority_queue;  
using std::pair;  
using std::make_pair;  
  
struct City {  
    int index;  
    int power;  
    bool operator<(const City& other) const {  
        return power < other.power;  
    }  
};  
  
struct Union {  
    int power;  
    vector<int> cities;  
};  
  
struct Move {  
    int from;  
    int to;  
    int time;  
};  
  
int main() {  
    int N, M, Me, D;  
    cin >> N >> M >> Me >> D;  
  
    vector<pair<int, int>> players(N); // city, power  
    vector<vector<Move>> graph(M);  
    vector<vector<City>> cities(M);  
    vector<vector<int>> distances(M, vector<int>(M, INT_MAX));  
  
    for (int i = 0; i < N; ++i) {  
        cin >> players[i].first >> players[i].second;  
        cities[players[i].first].push_back({i, players[i].second});  
    }  
  
    for (int i = 0; i < Me; ++i) {  
        int u, v, t;  
        cin >> u >> v >> t;  
        graph[u].push_back({u, v, t});  
        graph[v].push_back({v, u, t});  
        distances[u][v] = t;  
        distances[v][u] = t;  
    }  
  
    // Floyd-Warshall algorithm for shortest paths  
    for (int k = 0; k < M; ++k) {  
        for (int i = 0; i < M; ++i) {  
            for (int j = 0; j < M; ++j) {  
                if (distances[i][k] != INT_MAX && distances[k][j] != INT_MAX) {  
                    distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);  
                }  
            }  
        }  
    }  
  
    int myCity = players[0].first;  
    int myPower = players[0].second;  
    int day = 0;  
  
    auto compare = [&](const pair<int, int>& a, const pair<int, int>& b) {  
        if (abs(a.second - myPower) != abs(b.second - myPower)) {  
            return abs(a.second - myPower) < abs(b.second - myPower);  
        } else if (distances[myCity][a.first] != distances[myCity][b.first]) {  
            return distances[myCity][a.first] < distances[myCity][b.first];  
        } else {  
            return a.first < b.first;  
        }  
    };  
  
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> pq(compare);  
  
    for (int i = 0; i < N; ++i) {  
        if (players[i].first != myCity || players[i].second == myPower) continue;  
        pq.push({players[i].first, players[i].second});  
    }  
  
    while (day < D) {  
        if (pq.empty()) {  
            cout << "Game over with " << myPower << "." << std::endl;  
            return 0;  
        }  
  
        pair<int, int> target = pq.top();  
        pq.pop();  
  
        if (target.second >= myPower) {  
            cout << "Lose on day " << day + 1 << " with " << myPower << "." << std::endl;  
            return 0;  
        }  
  
        int targetCity = target.first;  
        int targetPower = target.second;  
  
        cout << "Move from " << myCity << " to " << targetCity << "." << std::endl;  
        myCity = targetCity;  
        cout << "Get " << targetPower << " at " << targetCity << " on day " << day + 1 << "." << std::endl;  
        myPower += targetPower;  
        day++;  
  
        vector<City> newCities;  
        for (City& city : cities[myCity]) {  
            if (city.power <= myPower) {  
                myPower += city.power;  
            } else {  
                newCities.push_back(city);  
            }  
        }  
  
        cities[myCity] = newCities;  
  
        for (City& city : cities[myCity]) {  
            pq.push({city.index, city.power});  
        }  
  
        if (pq.size() + cities[myCity].size() == 1) {  
            cout << "WIN on day " << day << " with " << myPower << "!" << std::endl;  
            return 0;  
        }  
    }  
  
    cout << "Game over with " << myPower << "." << std::endl;  
    return 0;  
}

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define MAXN 100005  
#define MIN(a, b) ((a) < (b) ? (a) : (b))  
  
int N;  
int color[MAXN], cost[MAXN];  
int dp[MAXN][2]; // dp[i][0] 表示节点i为白色的最小代价，dp[i][1] 表示节点i为黑色的最小代价  
int childCount[MAXN];  
int *children[MAXN];  
  
void dfs(int node, int parent) {  
    dp[node][color[node]] = 0;  
    dp[node][1 - color[node]] = cost[node];  
  
    for (int i = 0; i < childCount[node]; i++) {  
        int child = children[node][i];  
        if (child == parent) continue;  
        dfs(child, node);  
          
        // 根据子节点的DP值来更新当前节点的DP值  
        int whiteCost = MIN(dp[child][0], dp[child][1]);  
        int blackCost = MIN(dp[child][0] + 1, dp[child][1]); // +1 表示改变颜色  
        dp[node][0] += whiteCost;  
        dp[node][1] += blackCost;  
    }  
}  
int main() {  
    scanf("%d", &N);  
    for (int i = 1; i <= N; i++) {  
        scanf("%d %d %d", &color[i], &cost[i], &childCount[i]);  
        children[i] = (int *)malloc(childCount[i] * sizeof(int));  
        for (int j = 0; j < childCount[i]; j++) {  
            scanf("%d", &children[i][j]);  
        }  
    }  
  
    dfs(1, -1); // 从根节点开始深度优先搜索  
  
    // 输出根节点变为白色或黑色的最小代价中的较小值  
    printf("%d\n", MIN(dp[1][0], dp[1][1]));  
  
    // 释放内存  
    for (int i = 1; i <= N; i++) {  
        free(children[i]);  
    }  
  
    return 0;  
}
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define MOD 998244353  
#define MAXN 100005  
  
int t, n, m;  
int l[MAXN], r[MAXN];  
int dp[2][MAXN]; // dp[i][j] 表示前i个夜晚后，有j个区间被完全覆盖的方案数  
int sum[MAXN]; // sum[i] 表示前i个区间的长度和  
  
void add(int *a, int b) {  
    *a = (*a + b) % MOD;  
}  
  
int main() {  
    scanf("%d", &t);  
    while (t--) {  
        scanf("%d %d", &n, &m);  
        for (int i = 1; i <= m; i++) {  
            scanf("%d %d", &l[i], &r[i]);  
        }  
  
        memset(dp, 0, sizeof(dp));  
        memset(sum, 0, sizeof(sum));  
        dp[0][0] = 1;  
  
        for (int i = 1; i <= m; i++) {  
            int len = r[i] - l[i] + 1;  
            sum[i] = sum[i - 1] + len;  
            for (int j = 0; j <= n; j++) {  
                dp[i % 2][j] = 0;  
            }  
            for (int j = 0; j <= n; j++) {  
                if (dp[(i - 1) % 2][j] == 0) continue;  
                add(&dp[i % 2][j], dp[(i - 1) % 2][j]); // 不选当前区间  
                if (j + len <= n) {  
                    add(&dp[i % 2][j + len], dp[(i - 1) % 2][j]); // 选当前区间  
                }  
            }  
        }  
  
        int ans = 0;  
        for (int i = 2; i <= n; i++) {  
            int covered = sum[m] - (n - i); // 被覆盖的长度  
            if (covered >= 0 && covered <= m && dp[m % 2][covered]) {  
                add(&ans, dp[m % 2][covered]);  
            }  
        }  
  
        printf("%d\n", ans);  
    }  
    return 0;  
}