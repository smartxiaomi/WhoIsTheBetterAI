// by alibaba tongyi qianwen2.5
#include <stdio.h>
#include <string.h>

int main() {
    int N, M, K;
    char X[11];
    
    scanf("%d %s %d %d", &N, X, &M, &K);
    
    if (K == N) {
        printf("mei you mai %s de\n", X);
    } else if (K == M) {
        printf("kan dao_le mai %s de\n", X);
    } else {
        printf("wang le zhao mai %s de\n", X);
    }
    
    return 0;
}
#include <stdio.h>

int main() {
    int N, A, B, C;
    
    scanf("%d", &N);
    
    while (N--) {
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
#include <stdbool.h>

#define MAX_HATS 100
#define MAX_GROUPS 10

// 函数声明
bool canWinPrize(int hats[], int guesses[], int hatCount);

int main() {
    int N, K;
    int hats[MAX_HATS], guesses[MAX_HATS];
    
    // 读取帽子数量和颜色
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &hats[i]);
    }
    
    // 读取宝宝群组数量
    scanf("%d", &K);
    
    // 处理每个宝宝群组
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < N; i++) {
            scanf("%d", &guesses[i]);
        }
        
        // 判断是否可以获得大奖
        if (canWinPrize(hats, guesses, N)) {
            printf("Da Jiang!!!\n");
        } else {
            printf("Ai Ya\n");
        }
    }
    
    return 0;
}

// 判断是否可以获得大奖
bool canWinPrize(int hats[], int guesses[], int hatCount) {
    bool won = true;
    int correctGuesses = 0;
    
    for (int i = 0; i < hatCount; i++) {
        if (guesses[i] != 0 && hats[i] != guesses[i]) {
            won = false;
            break;
        }
        if (guesses[i] != 0) {
            correctGuesses++;
        }
    }
    
    return won && correctGuesses > 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* cutString(char *str, int start, int end) {
    char *cutStr = str + start - 1;
    int len = end - start + 1;
    char *clipboard = malloc(len + 1);
    strncpy(clipboard, cutStr, len);
    clipboard[len] = '\0';
    
    memmove(cutStr, cutStr + len, strlen(cutStr + len) + 1);
    
    return clipboard;
}

void pasteString(char *str, const char *clipboard, const char *before, const char *after) {
    char *insertPos = strstr(str, before);
    if (insertPos != NULL) {
        insertPos += strlen(before);
        while (*insertPos != after[0] && *insertPos != '\0') {
            insertPos++;
        }
    }
    if (insertPos == NULL || *insertPos == '\0') {
        insertPos = str + strlen(str);
    }
    
    memmove(insertPos + strlen(clipboard), insertPos, strlen(insertPos) + 1);
    memcpy(insertPos, clipboard, strlen(clipboard) + 1);
}

int main() {
    char originalStr[201];
    int operations;
    
    fgets(originalStr, sizeof(originalStr), stdin);
    originalStr[strcspn(originalStr, "\n")] = 0;
    
    scanf("%d", &operations);
    
    char *clipboard = NULL;
    int start, end;
    char before[6], after[6];
    
    for (int i = 0; i < operations; i++) {
        scanf("%d %d %s %s", &start, &end, before, after);
        
        if (clipboard != NULL) free(clipboard);
        clipboard = cutString(originalStr, start, end);
        
        pasteString(originalStr, clipboard, before, after);
    }
    
    if (clipboard != NULL) free(clipboard);
    
    printf("%s\n", originalStr);
    
    return 0;
}
#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);
    
    int bestDiff = -1;
    int bestXrooms = -1;
    int bestYrooms = -1;
    
    for (int xrooms = 1; xrooms <= n; xrooms++) {
        if (x % xrooms != 0)
            continue;
        
        int xperroom = x / xrooms;
        if (xperroom == 1)
            continue;
        
        for (int yrooms = 1; yrooms <= n; yrooms++) {
            if (y % yrooms != 0)
                continue;
            
            int yperroom = y / yrooms;
            if (yperroom == 1)
                continue;
            
            if (xrooms + yrooms != n)
                continue;
            
            int diff = abs(xperroom - yperroom);
            if (bestDiff == -1 || diff < bestDiff) {
                bestDiff = diff;
                bestXrooms = xrooms;
                bestYrooms = yrooms;
            }
        }
    }
    
    if (bestXrooms == -1 || bestYrooms == -1)
        printf("No Solution\n");
    else
        printf("%d %d\n", bestXrooms, bestYrooms);
    
    return 0;
}
#include <stdio.h>

// Function to calculate the sum of digits of a number
int sumOfDigits(long num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// Function to determine who is the dad
char whoIsDad(long NA, long NB) {
    int SA = sumOfDigits(NA);
    int SB = sumOfDigits(NB);

    // Check if NA is an integer multiple of SB or NB is an integer multiple of SA
    if (NA % SB == 0 && NB % SA != 0) return 'A';
    if (NB % SA == 0 && NA % SB != 0) return 'B';
    if (NA % SB == 0 && NB % SA == 0) return NA > NB ? 'A' : 'B';
    return NA > NB ? 'A' : 'B';
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        long NA, NB;
        scanf("%ld %ld", &NA, &NB);
        printf("%c\n", whoIsDad(NA, NB));
    }

    return 0;
}#include <stdio.h>

// Function to calculate the sum of digits of a number
int sumOfDigits(long num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// Function to determine who is the dad
char whoIsDad(long NA, long NB) {
    int SA = sumOfDigits(NA);
    int SB = sumOfDigits(NB);

    // Check if NA is an integer multiple of SB or NB is an integer multiple of SA
    if (NA % SB == 0 && NB % SA != 0) return 'A';
    if (NB % SA == 0 && NA % SB != 0) return 'B';
    if (NA % SB == 0 && NB % SA == 0) return NA > NB ? 'A' : 'B';
    return NA > NB ? 'A' : 'B';
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        long NA, NB;
        scanf("%ld %ld", &NA, &NB);
        printf("%c\n", whoIsDad(NA, NB));
    }

    return 0;
}
#include <stdio.h>
#define MAX_N 1000
#define MAX_DIAMETER 100

int main() {
    int N, diameters[MAX_N], A[MAX_N], B[MAX_N];
    int topA = -1, topB = -1;
    int towerCount = 0, maxTowerHeight = 0;

    // Read input
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &diameters[i]);
    }

    // Process each circle
    for (int i = 0; i < N; ++i) {
        int currentCircle = diameters[i];
        // Try to put on A
        if (topA == -1 || currentCircle <= A[topA]) {
            A[++topA] = currentCircle;
        } else {
            // If not possible, try B or move circles from B to A
            while (topB >= 0 && B[topB] < currentCircle) {
                A[++topA] = B[topB--];
            }
            if (topB == -1 || currentCircle >= B[topB]) {
                B[++topB] = currentCircle;
            } else {
                // If neither A nor B can take it, create a new tower
                towerCount++;
                maxTowerHeight = topA + 1 > maxTowerHeight ? topA + 1 : maxTowerHeight;
                topA = topB;
                A[topA] = currentCircle;
                topB = -1;
            }
        }
        maxTowerHeight = topA + 1 > maxTowerHeight ? topA + 1 : maxTowerHeight;
    }

    // Count last towers
    towerCount += (topA >= 0) + (topB >= 0);

    // Print result
    printf("%d %d\n", towerCount, maxTowerHeight);

    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_SCHOOLS 5000
#define MAX_TEAMS_PER_GYM 50
#define MAX_TEAM_NAME_LENGTH 7

typedef struct {
    char name[MAX_TEAM_NAME_LENGTH];
    int teams;
    int assignedGym;
} School;

typedef struct {
    int capacity;
    int used;
    int schools[MAX_SCHOOLS];
} Gym;

void arrangeSchools(School schools[], int schoolCount, int gymCapacity, Gym gyms[]) {
    int gymCount = 0;
    for(int i = 0; i < schoolCount; i++) {
        School *school = &schools[i];
        if(school->teams > 0) {
            if(school->teams >= gymCapacity) {
                int newGymTeams = gymCapacity;
                school->teams -= newGymTeams;
                school->assignedGym = gymCount;
                gyms[gymCount].used = newGymTeams;
                gyms[gymCount].schools[newGymTeams-1] = i;
                gymCount++;
            } else {
                int gymFound = -1;
                for(int j = 0; j < gymCount; j++) {
                    if(gyms[j].used + school->teams <= gymCapacity) {
                        gymFound = j;
                        break;
                    }
                }
                if(gymFound == -1) {
                    gymFound = gymCount;
                    gymCount++;
                    gyms[gymFound].used = school->teams;
                } else {
                    gyms[gymFound].used += school->teams;
                }
                school->assignedGym = gymFound;
                school->teams = 0;
            }
        }
    }
}

int main() {
    int schoolCount, gymCapacity;
    scanf("%d %d", &schoolCount, &gymCapacity);
    
    School schools[MAX_SCHOOLS];
    Gym gyms[MAX_SCHOOLS];
    
    for(int i = 0; i < schoolCount; i++) {
        scanf("%s %d", schools[i].name, &schools[i].teams);
        schools[i].assignedGym = -1;
    }
    
    arrangeSchools(schools, schoolCount, gymCapacity, gyms);
    
    for(int i = 0; i < schoolCount; i++) {
        printf("%s %d\n", schools[i].name, schools[i].assignedGym + 1);
    }
    
    int gymCount = 0;
    for(int i = 0; i < schoolCount; i++) {
        if(gyms[i].used > 0) gymCount++;
    }
    printf("%d\n", gymCount);
    
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    int k;
    std::cin >> k;
    std::vector<std::vector<long long>> losers(k);
    for (int i = 0; i < k; ++i) {
        losers[i].resize(1LL << (k - i - 1));
        for (int j = 0; j < (1LL << (k - i - 1)); ++j) {
            std::cin >> losers[i][j];
        }
    }

    long long winner;
    std::cin >> winner;

    std::vector<long long> scores((1LL << k), 0);
    scores[(1LL << (k - 1))] = winner;

    bool has_solution = true;
    for (int round = k - 1; round >= 0 && has_solution; --round) {
        for (int match = 0; match < (1LL << (k - round - 1)); ++match) {
            int left_child = 2 * match;
            int right_child = left_child + 1;
            long long loser_score = losers[round][match];
            long long& left_winner_score = scores[left_child];
            long long& right_winner_score = scores[right_child];

            if (left_winner_score == 0 && right_winner_score == 0) {
                left_winner_score = loser_score + 1;
                right_winner_score = loser_score + 1;
            } else if (left_winner_score == 0) {
                left_winner_score = std::max(right_winner_score - 1, loser_score + 1);
            } else if (right_winner_score == 0) {
                right_winner_score = std::max(left_winner_score - 1, loser_score + 1);
            }

            if (left_winner_score <= loser_score || right_winner_score <= loser_score) {
                has_solution = false;
                break;
            }
        }
    }

    if (has_solution) {
        for (int i = 0; i < (1LL << k); ++i) {
            std::cout << scores[i];
            if (i < (1LL << k) - 1) std::cout << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No Solution" << std::endl;
    }

    return 0;
}
#include <iostream>
#include <vector>

const int LAND = 1;
const int TREASURE_MIN = 2;
const int TREASURE_MAX = 9;
const int VISITED = -1;

void dfs(std::vector<std::vector<int>>& map, int x, int y, bool& hasTreasure) {
    if (x < 0 || y < 0 || x >= map.size() || y >= map[0].size() || map[x][y] == VISITED) {
        return;
    }
    if (map[x][y] == LAND || (TREASURE_MIN <= map[x][y] && map[x][y] <= TREASURE_MAX)) {
        hasTreasure |= (TREASURE_MIN <= map[x][y] && map[x][y] <= TREASURE_MAX);
        map[x][y] = VISITED;
        dfs(map, x + 1, y, hasTreasure);
        dfs(map, x - 1, y, hasTreasure);
        dfs(map, x, y + 1, hasTreasure);
        dfs(map, x, y - 1, hasTreasure);
    }
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> map(N, std::vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> map[i][j];
        }
    }

    int islandCount = 0;
    int treasureIslandCount = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (map[i][j] == LAND || (TREASURE_MIN <= map[i][j] && map[i][j] <= TREASURE_MAX)) {
                bool hasTreasure = false;
                dfs(map, i, j, hasTreasure);
                islandCount++;
                if (hasTreasure) {
                    treasureIslandCount++;
                }
            }
        }
    }

    std::cout << islandCount << " " << treasureIslandCount << std::endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <limits>

struct Fighter {
    int city;
    int strength;
};

struct Path {
    int startCity;
    int endCity;
    int duration;
};

struct City {
    int id;
    std::vector<Fighter> fighters;
    std::vector<Path> paths;
};

struct Game {
    std::vector<City> cities;
    Fighter me;
    int days;
    int currentDay = 0;
    int currentCity = -1;
};

bool canBeat(Fighter& f1, Fighter& f2) {
    return f1.strength >= f2.strength;
}

Fighter findClosestBeatableOpponent(Game& game) {
    // Implementation to find the closest beatable opponent.
    // This function will be quite complex and might require
    // using data structures like priority queues.
    return Fighter{0, 0};
}

void move(Game& game, int destinationCity) {
    // Implementation to move from one city to another.
}

void fight(Game& game, Fighter& opponent) {
    // Implementation to fight an opponent.
}

int main() {
    // Input reading code goes here.
    // You would read the number of fighters, cities, paths, and days.
    // Then you would populate your game object accordingly.
    
    Game game;
    // Populate game with data from input.

    while (game.currentDay < game.days && !isGameOver(game)) {
        Fighter opponent = findClosestBeatableOpponent(game);
        if (opponent.city != game.currentCity) {
            move(game, opponent.city);
        }
        fight(game, opponent);
    }

    // Output writing code goes here.
    // You would write the results of the game to stdout.

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100000
#define INF 1000000000

typedef struct Node {
    int color;
    int cost;
    int numChildren;
    int* children;
    int* dp;
} Node;

Node* createNode(int color, int cost, int numChildren) {
    Node* node = malloc(sizeof(Node));
    node->color = color;
    node->cost = cost;
    node->numChildren = numChildren;
    node->children = malloc(numChildren * sizeof(int));
    node->dp = malloc(2 * sizeof(int));
    node->dp[0] = INF;
    node->dp[1] = INF;
    return node;
}

void addChildren(Node* node, int child) {
    node->children[node->numChildren++] = child;
}

void dfs(Node* nodes, int index) {
    Node* node = &nodes[index];
    if (node->numChildren == 0) {
        node->dp[node->color] = 0;
        node->dp[1 - node->color] = node->cost;
        return;
    }
    for (int i = 0; i < node->numChildren; i++) {
        dfs(nodes, node->children[i]);
    }
    for (int bal = 0; bal <= 1; bal++) {
        int balCost = bal ? node->cost : 0;
        for (int i = 0; i < node->numChildren; i++) {
            int minCost = INF;
            for (int childBal = 0; childBal <= 1; childBal++) {
                int curCost = nodes[node->children[i]].dp[childBal];
                if ((bal + childBal) % 2 == 0) {
                    minCost = curCost < minCost ? curCost : minCost;
                }
            }
            balCost += minCost;
        }
        node->dp[bal] = balCost;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    Node nodes[MAX_NODES];
    for (int i = 0; i < N; i++) {
        int color, cost, numChildren;
        scanf("%d %d %d", &color, &cost, &numChildren);
        Node* node = &nodes[i];
        node->color = color;
        node->cost = cost;
        node->numChildren = numChildren;
        node->children = malloc(numChildren * sizeof(int));
        node->dp = malloc(2 * sizeof(int));
        node->dp[0] = INF;
        node->dp[1] = INF;
        for (int j = 0; j < numChildren; j++) {
            int child;
            scanf("%d", &child);
            addChildren(node, --child);
        }
    }
    dfs(nodes, 0);
    printf("%d\n", nodes[0].dp[0] < nodes[0].dp[1] ? nodes[0].dp[0] : nodes[0].dp[1]);
    return 0;
}
#include <stdio.h>

#define MOD 998244353
#define MAX_N 100005

long long modpow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

long long inv(long long a) {
    return modpow(a, MOD - 2);
}

long long nCr[MAX_N][MAX_N];

void precomputeBinomialCoefficients() {
    for (int i = 0; i < MAX_N; i++) {
        nCr[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % MOD;
        }
    }
}

long long solve(int n, int m, int* l, int* r) {
    long long dp[2][MAX_N] = {{0}};
    dp[0][0] = 1;
    dp[0][1] = 1;
    for (int i = 1; i <= m; i++) {
        int len = r[i - 1] - l[i - 1] + 1;
        for (int j = 0; j <= n; j++) {
            dp[i & 1][j] = 0;
            for (int k = 0; k <= j; k++) {
                long long ways = nCr[j][k] * nCr[n - j][len - k] % MOD;
                ways *= dp[(i & 1) ^ 1][j - k];
                ways %= MOD;
                dp[i & 1][j] = (dp[i & 1][j] + ways) % MOD;
            }
        }
        long long total = modpow(2, n);
        long long invTotal = inv(total);
        for (int j = 0; j <= n; j++) {
            dp[i & 1][j] = dp[i & 1][j] * invTotal % MOD;
        }
    }
    long long result = 0;
    for (int i = 0; i <= n; i++) {
        result = (result + dp[m & 1][i]) % MOD;
    }
    return result;
}

int main() {
    int t;
    scanf("%d", &t);
    precomputeBinomialCoefficients();
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        int l[m], r[m];
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &l[i], &r[i]);
        }
        long long answer = solve(n, m, l, r);
        printf("%lld\n", answer);
    }
    return 0;
}