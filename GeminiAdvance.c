//by google gemini
#include <iostream>
#include <string>

int main() {
int N, M, K;
std::string X;
std::cin >> N >> X >> M >> K;

if (K == N) {
    std::cout << "mei you mai " << X << " de" << std::endl;
} else if (K == M) {
    std::cout << "kan dao le mai " << X << " de" << std::endl;
} else {
    std::cout << "wang le zhao mai " << X << " de" << std::endl;
}

return 0;
}
#include <stdio.h>

int main() {
int N, A, B, C;
scanf("%d", &N);

for (int i = 0; i < N; i++) {
    scanf("%d %d %d", &A, &B, &C);
    if (C == A * B) {
        printf("Lv Yan\n");
    } else if (C == A + B) {
        printf("Tu Dou\n");
    } else {
        printf("zhe du shi sha ya!\n");
    }
}

return 0;
}

#include <stdio.h>

int main() {
int N, K, hats[100], guesses[100];
scanf("%d", &N);
for (int i = 0; i < N; i++) {
scanf("%d", &hats[i]);
}
scanf("%d", &K);

for (int i = 0; i < K; i++) {
    int numGuess = 0, correctGuess = 0;
    for (int j = 0; j < N; j++) {
        scanf("%d", &guesses[j]);
        if (guesses[j] != 0) {
            numGuess++;
            if (guesses[j] == hats[j]) {
                correctGuess++;
            } else {
                printf("Ai Ya\n");
                break; // 只要有一个人猜错，就不用继续判断了
            }
        }
    }
    if (numGuess > 0 && correctGuess == numGuess) { // 至少有一个人猜对，且没有人猜错
        printf("Da Jiang!!!\n");
    } else if (numGuess == 0) { // 所有人弃权
        printf("Ai Ya\n");
    }
}

return 0;
}

#include <iostream>
#include <string>

using std::string;

string S, clipboard;

void cut(int start, int end) {
clipboard = S.substr(start - 1, end - start + 1);
S.erase(start - 1, end - start + 1);
}

void paste(const string& before, const string& after) {
size_t insertPos = S.find(before);
if (insertPos == string::npos) {
insertPos = S.length(); // Insert at the end if not found
} else {
insertPos += before.length();
}
S.insert(insertPos, clipboard);
clipboard.clear();
}

int main() {
int N, start, end;
string before, after;

std::getline(std::cin, S);
std::cin >> N;

for (int i = 0; i < N; i++) {
    std::cin >> start >> end >> before >> after;
    cut(start, end);
    paste(before, after);
}

std::cout << S << std::endl;

return 0;
}
#include <stdio.h>

int main() {
    int x, y, n, i, j;

    scanf("%d %d %d", &x, &y, &n);

    int minDiff = 100000; // 初始化为一个较大的值
    int girlsRooms = 0, boysRooms = 0;
    int foundSolution = 0; // 用于标记是否找到解

    for (i = 2; i <= x; i++) { // 女生每间寝室人数从 2 开始
        if (x % i == 0) { // 女生人数能被 i 整除
            for (j = 2; j <= y; j++) { // 男生每间寝室人数从 2 开始
                if (y % j == 0) { // 男生人数能被 j 整除
                    if (x / i + y / j == n) { // 寝室总数符合要求
                        int diff = i - j;
                        if (diff < 0) 
                            diff = -diff; // 取绝对值
                        if (diff < minDiff) { // 更新最小人数差
                            minDiff = diff;
                            girlsRooms = x / i;
                            boysRooms = y / j;
                            foundSolution = 1;
                        }
                    }
                }
            }
        }
    }

    if (foundSolution) {
        printf("%d %d\n", girlsRooms, boysRooms);
    } else {
        printf("No Solution\n");
    }

    return 0;
}
#include <stdio.h>

int digitSum(long long num) {
int sum = 0;
while (num > 0) {
sum += num % 10;
num /= 10;
}
return sum;
}

int main() {
int N;
long long NA, NB;
scanf("%d", &N);

for (int i = 0; i < N; i++) {
    scanf("%lld %lld", &NA, &NB);

    int SA = digitSum(NA);
    int SB = digitSum(NB);

    if (NA % SB == 0 && NB % SA != 0) {
        printf("A\n");
    } else if (NB % SA == 0 && NA % SB != 0) {
        printf("B\n");
    } else if (NA > NB) {
        printf("A\n");
    } else {
        printf("B\n");
    }
}

return 0;
}

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

int main() {
int N;
std::cin >> N;

vector<int> rings(N);
for (int i = 0; i < N; ++i) {
    std::cin >> rings[i];
}

stack<int> A, B;
int towerCount = 0, maxHeight = 0;

for (int ring : rings) {
    if (A.empty() || ring < A.top()) {
        A.push(ring);
    } else {
        while (!B.empty() && ring < B.top()) {
            A.push(B.top());
            B.pop();
        }
        B.push(ring);
    }

    if (A.size() > maxHeight) {
        maxHeight = A.size();
    }
}

towerCount += !A.empty();
towerCount += !B.empty();

std::cout << towerCount << " " << maxHeight << std::endl;

return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SCHOOLS 5000
#define MAX_NAME_LEN 7

typedef struct {
char name[MAX_NAME_LEN];
int numStudents;
int numSupervisors;
} School;

int compare(const void *a, const void *b) {
return ((School *)b)->numStudents - ((School *)a)->numStudents;
}

int main() {
int N, C, numVenues = 0;
School schools[MAX_SCHOOLS];
int venueCapacity[MAX_SCHOOLS] = {0}; // Initialize all venue capacities to 0

scanf("%d %d", &N, &C);
for (int i = 0; i < N; i++) {
    scanf("%s %d", schools[i].name, &schools[i].numStudents);
    schools[i].numSupervisors = 0;
}

qsort(schools, N, sizeof(School), compare); // Sort schools by student count in descending order

for (int i = 0; i < N; i++) {
    int studentsLeft = schools[i].numStudents;
    int venueIndex = 0;
    while (studentsLeft > 0) {
        if (venueCapacity[venueIndex] + studentsLeft <= C) {
            venueCapacity[venueIndex] += studentsLeft;
            schools[i].numSupervisors++;
            studentsLeft = 0;
        } else {
            venueIndex++;
            if (venueIndex == numVenues) { // Need to open a new venue
                numVenues++;
                venueCapacity[venueIndex] = C; // Set capacity of the new venue
            }
        }
    }
}

for (int i = 0; i < N; i++) {
    printf("%s %d\n", schools[i].name, schools[i].numSupervisors);
}
printf("%d\n", numVenues);

return 0;
}
#include <stdio.h>
#include <math.h>

#define MAX_K 18
#define MAX_N (1 << MAX_K)

int losers[MAX_K][MAX_N / 2];
int abilities[MAX_N];

int main() {
int k, winner;
scanf("%d", &k);
int n = 1 << k; // n = 2^k

for (int i = 0; i < k; i++) {
    for (int j = 0; j < (1 << (k - i - 1)); j++) {
        scanf("%d", &losers[i][j]);
    }
}
scanf("%d", &winner);

abilities[0] = winner;
int hasSolution = 1; // Flag to track if a solution exists

for (int i = k - 1; i >= 0; i--) {
    for (int j = 0; j < (1 << (k - i - 1)); j++) {
        int loserIndex = (1 << i) + j;
        int winnerIndex = loserIndex - 1;

        if (abilities[winnerIndex] == -1) {
            abilities[winnerIndex] = losers[i][j] + 1; // Winner must be stronger
        } else if (abilities[winnerIndex] <= losers[i][j]) {
            hasSolution = 0; // No solution possible
            break;
        }

        abilities[loserIndex] = losers[i][j];
    }

    if (!hasSolution) {
        break;
    }
}

if (hasSolution) {
    for (int i = 0; i < n; i++) {
        printf("%d ", abilities[i]);
    }
    printf("\n");
} else {
    printf("No Solution\n");
}

return 0;
}
#include <stdio.h>

#define MAX_N 100
#define MAX_M 100

int N, M;
int map[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];

int dx[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y, int *hasTreasure) {
    visited[x][y] = 1;
    if (map[x][y] > 1) {
        *hasTreasure = 1; // Mark the island as having treasure
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && map[nx][ny] >= 1 && !visited[nx][ny]) {
            dfs(nx, ny, hasTreasure);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d", &map[i][j]);
            visited[i][j] = 0;
        }
    }

    int islandCount = 0, treasureIslandCount = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] >= 1 && !visited[i][j]) {
                int hasTreasure = 0;
                dfs(i, j, &hasTreasure);
                islandCount++;
                if (hasTreasure) {
                    treasureIslandCount++;
                }
            }
        }
    }

    printf("%d %d\n", islandCount, treasureIslandCount);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_M 200
#define INF 1000000000

typedef struct {
int city;
int ability;
} Player;

typedef struct {
int city1;
int city2;
int time;
} Road;

int N, M, Me, D;
Player players[MAX_N];
Road roads[MAX_M];
int dist[MAX_M][MAX_M]; // Distance matrix

int compare(const void *a, const void *b) {
Player *pa = (Player *)a;
Player *pb = (Player *)b;
return pa->ability - pb->ability;
}

// Floyd-Warshall algorithm to calculate shortest paths
void floydWarshall() {
for (int i = 0; i < M; i++) {
for (int j = 0; j < M; j++) {
if (i == j) {
dist[i][j] = 0;
} else {
dist[i][j] = INF;
}
}
}

for (int k = 0; k < Me; k++) {
    int city1 = roads[k].city1;
    int city2 = roads[k].city2;
    int time = roads[k].time;
    dist[city1][city2] = dist[city2][city1] = time;
}

for (int k = 0; k < M; k++) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (dist[i][j] > dist[i][k] + dist[k][j]) {
                dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}
}

int main() {
scanf("%d %d %d %d", &N, &M, &Me, &D);

// Read player information
for (int i = 0; i < N; i++) {
    scanf("%d %d", &players[i].city, &players[i].ability);
}
qsort(players, N, sizeof(Player), compare); // Sort players by ability

// Read road information
for (int i = 0; i < Me; i++) {
    scanf("%d %d %d", &roads[i].city1, &roads[i].city2, &roads[i].time);
}

floydWarshall(); // Calculate shortest paths

// Game simulation
int currentCity = players[0].city;
int currentAbility = players[0].ability;
int day = 1;

while (day <= D) {
    // Find the next target
    int target = -1;
    int minDiff = INF;
    int minDist = INF;
    int minCity = INF;

    for (int i = 1; i < N; i++) {
        if (players[i].ability <= currentAbility) {
            int diff = currentAbility - players[i].ability;
            int distance = dist[currentCity][players[i].city];
            if (diff < minDiff || (diff == minDiff && distance < minDist) ||
                (diff == minDiff && distance == minDist && players[i].city < minCity)) {
                target = i;
                minDiff = diff;
                minDist = distance;
                minCity = players[i].city;
            }
        }
    }

    // If no target found, try to find a city with weaker opponents
    if (target == -1) {
        for (int i = 0; i < M; i++) {
            int weakerCount = 0;
            int totalAbility = 0;
            for (int j = 1; j < N; j++) {
                if (players[j].city == i && players[j].ability <= currentAbility) {
                    weakerCount++;
                    totalAbility += players[j].ability;
                }
            }
            if (weakerCount > 0 && totalAbility <= currentAbility) {
                target = i; // Move to the city with weaker opponents
                break;
            }
        }
    }

    // If still no target, the game is over
    if (target == -1) {
        if (day == D) {
            printf("Lose on day %d with %d.\n", day, currentAbility);
        } else {
            printf("Game over with %d.\n", currentAbility);
        }
        break;
    }

    // Move to the target city or player
    if (target < M) { // Move to a city
        printf("Move from %d to %d.\n", currentCity, target);
        day += dist[currentCity][target];
        currentCity = target;
    } else { // Fight a player
        printf("Get %d at %d on day %d.\n", players[target].ability, players[target].city, day + 1);
        currentAbility += players[target].ability;
        players[target].ability = -1; // Mark the player as defeated
        day++;
    }

    // Check if the player has won
    int remaining = 0;
    for (int i = 1; i < N; i++) {
        if (players[i].ability != -1) {
            remaining++;
        }
    }
    if (remaining == 0) {
        printf("WIN on day %d with %d!\n", day, currentAbility);
        break;
    }
}

return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct Node {
int color;
int cost;
int numChildren;
int children[MAX_N];
} Node;

Node tree[MAX_N + 1]; // 1-indexed tree
long long minCost = 0;

int dfs(int node) {
int blackCount = 0, whiteCount = 0;
for (int i = 0; i < tree[node].numChildren; i++) {
int child = tree[node].children[i];
int childBalance = dfs(child);
blackCount += (childBalance > 0) ? childBalance : 0;
whiteCount += (childBalance < 0) ? -childBalance : 0;
}

if (tree[node].color == 1) { // Black node
    blackCount++;
} else { // White node
    whiteCount++;
}

int balance = blackCount - whiteCount;
if (abs(balance) > 1) {
    // Need to change color to make the subtree balanced
    minCost += tree[node].cost;
    tree[node].color = 1 - tree[node].color; // Flip the color
    balance = -balance; // Update balance after color change
}

return balance;
}

int main() {
int N;
scanf("%d", &N);

for (int i = 1; i <= N; i++) {
    scanf("%d %d %d", &tree[i].color, &tree[i].cost, &tree[i].numChildren);
    for (int j = 0; j < tree[i].numChildren; j++) {
        scanf("%d", &tree[i].children[j]);
    }
}

dfs(1); // Start DFS from the root node

printf("%lld\n", minCost);
return 0;
}
#include <stdio.h>

#define MOD 998244353

int t, n, m;
int l[100005], r[100005];
int dp[100005][2]; // dp[i][j] 表示前 i 晚得到 j 个 1 的方案数

int solve() {
scanf("%d %d", &n, &m);
for (int i = 0; i < m; i++) {
scanf("%d %d", &l[i], &r[i]);
}

dp[0][0] = 1;
dp[0][1] = 1; // 初始状态，两种可能性

for (int i = 1; i <= m; i++) {
    dp[i][0] = dp[i - 1][0] * (l[i - 1] - 1) % MOD; // 第 i 晚得到 0 的方案数
    dp[i][1] = (dp[i - 1][1] * (n - r[i - 1]) + dp[i - 1][0] * (r[i - 1] - l[i - 1] + 1)) % MOD; // 第 i 晚得到 1 的方案数
}

int ans = 0;
for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
        int valid = 1;
        for (int k = 0; k < m; k++) {
            if ((l[k] <= i && i <= r[k]) ^ (l[k] <= j && j <= r[k])) { // 异或运算判断是否只有一个在区间内
                valid = 0;
                break;
            }
        }
        ans = (ans + valid * dp[m][1]) % MOD; // 只有得到 1 的情况才可能唯一确定
    }
}

return ans;
}

int main() {
scanf("%d", &t);
while (t--) {
printf("%d\n", solve());
}
return 0;
}






