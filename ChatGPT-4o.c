//by chatGPT4o
#include <stdio.h>
#include <string.h>

int main() {
    int N, M, K;
    char X[11];  // X's length is at most 10 plus the null terminator
    scanf("%d %s %d %d", &N, X, &M, &K);

    if (K == N) {
        printf("mei you mai %s de\n", X);
    } else if (K == M) {
        printf("kan dao le mai %s de\n", X);
    } else {
        printf("wang le zhao mai %s de\n", X);
    }

    return 0;
}
#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int A, B, C;
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
    int N;
    scanf("%d", &N);

    int hats[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &hats[i]);
    }

    int K;
    scanf("%d", &K);

    for (int i = 0; i < K; i++) {
        int guesses[N];
        int correctGuesses = 0;
        int wrongGuesses = 0;
        for (int j = 0; j < N; j++) {
            scanf("%d", &guesses[j]);
            if (guesses[j] != 0) {
                if (guesses[j] == hats[j]) {
                    correctGuesses++;
                } else {
                    wrongGuesses++;
                }
            }
        }
        if (wrongGuesses == 0 && correctGuesses > 0) {
            printf("Da Jiang!!!\n");
        } else {
            printf("Ai Ya\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <string.h>

void cut(char *str, int start, int end, char *clipboard) {
    int len = end - start + 1;
    strncpy(clipboard, str + start - 1, len);
    clipboard[len] = '\0';
    strcpy(str + start - 1, str + end);
}

void paste(char *str, char *before, char *after, char *clipboard) {
    char *pos = strstr(str, before);
    if (pos == NULL) {
        strcat(str, clipboard);
    } else {
        pos += strlen(before);
        char temp[201];
        strcpy(temp, pos);
        strcpy(pos, clipboard);
        strcat(str, temp);
    }
    clipboard[0] = '\0';
}

int main() {
    char str[201], clipboard[201] = {0};
    int N;

    scanf("%200s", str);
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int start, end;
        char before[6], after[6];
        scanf("%d %d %s %s", &start, &end, before, after);
        cut(str, start, end, clipboard);
        paste(str, before, after, clipboard);
    }

    printf("%s\n", str);

    return 0;
}
#include <stdio.h>
#include <limits.h>

int main() {
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);

    int min_diff = INT_MAX;
    int best_girls_rooms = -1;
    int best_boys_rooms = -1;

    for (int girls_rooms = 1; girls_rooms <= n; girls_rooms++) {
        if (x % girls_rooms != 0) continue;
        int girls_per_room = x / girls_rooms;

        int boys_rooms = n - girls_rooms;
        if (boys_rooms <= 0) continue;
        if (y % boys_rooms != 0) continue;
        int boys_per_room = y / boys_rooms;

        if (girls_per_room < 2 || boys_per_room < 2) continue;

        int diff = abs(girls_per_room - boys_per_room);
        if (diff < min_diff) {
            min_diff = diff;
            best_girls_rooms = girls_rooms;
            best_boys_rooms = boys_rooms;
        }
    }

    if (best_girls_rooms == -1 || best_boys_rooms == -1) {
        printf("No Solution\n");
    } else {
        printf("%d %d\n", best_girls_rooms, best_boys_rooms);
    }

    return 0;
}
#include <stdio.h>

// Function to calculate the sum of the digits of a number
int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        int NA, NB;
        scanf("%d %d", &NA, &NB);

        int SA = sumOfDigits(NA);
        int SB = sumOfDigits(NB);

        // Determine the "dad" based on the given rules
        if ((NB % SA == 0) && (NA % SB == 0)) {
            if (NA > NB) {
                printf("A\n");
            } else {
                printf("B\n");
            }
        } else if (NB % SA == 0) {
            printf("B\n");
        } else if (NA % SB == 0) {
            printf("A\n");
        } else {
            if (NA > NB) {
                printf("A\n");
            } else {
                printf("B\n");
            }
        }
    }

    return 0;
}
#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int circles[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &circles[i]);
    }

    int towers = 0, max_height = 0, current_height = 0;
    int a_top = -1, b_top = -1;
    int a_stack[N], b_stack[N];

    for (int i = 0; i < N; i++) {
        int C = circles[i];
        
        if (a_top == -1 || C < a_stack[a_top]) {
            a_stack[++a_top] = C;
            current_height++;
        } else {
            while (b_top != -1 && C >= b_stack[b_top]) {
                a_stack[++a_top] = b_stack[b_top--];
                current_height++;
            }
            if (b_top == -1 || C > b_stack[b_top]) {
                b_stack[++b_top] = C;
            } else {
                towers++;
                if (current_height > max_height) {
                    max_height = current_height;
                }
                current_height = 1;
                a_top = -1;
                b_top = -1;
                a_stack[++a_top] = C;
            }
        }
    }

    towers++;
    if (current_height > max_height) {
        max_height = current_height;
    }

    while (b_top != -1) {
        current_height++;
        b_top--;
    }
    towers++;
    if (current_height > max_height) {
        max_height = current_height;
    }

    printf("%d %d\n", towers, max_height);

    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_SCHOOLS 5000
#define MAX_NAME_LEN 7

typedef struct {
    char name[MAX_NAME_LEN];
    int students;
    int invigilators;
} School;

int main() {
    int N, C;
    scanf("%d %d", &N, &C);

    School schools[MAX_SCHOOLS];
    int total_seats = 0;

    for (int i = 0; i < N; ++i) {
        scanf("%s %d", schools[i].name, &schools[i].students);
        schools[i].invigilators = 0;
    }

    for (int i = 0; i < N; ++i) {
        int remaining_students = schools[i].students;

        while (remaining_students > 0) {
            if (remaining_students >= C) {
                remaining_students -= C;
                schools[i].invigilators++;
                total_seats++;
            } else {
                int placed = 0;

                for (int j = 0; j < total_seats; ++j) {
                    if (schools[j].students < C && (C - schools[j].students) >= remaining_students) {
                        schools[j].students += remaining_students;
                        placed = 1;
                        break;
                    }
                }

                if (!placed) {
                    schools[i].invigilators++;
                    total_seats++;
                    remaining_students = 0;
                } else {
                    remaining_students = 0;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        printf("%s %d\n", schools[i].name, schools[i].invigilators);
    }

    printf("%d\n", total_seats);

    return 0;
}
#include <stdio.h>
#include <math.h>

#define MAX_K 18
#define MAX_N (1 << MAX_K)

int losers[MAX_K][MAX_N / 2];
int results[MAX_N];
int final_winner;

int validate(int k, int n) {
    for (int round = 1; round <= k; round++) {
        int matches = n / (1 << round);
        for (int match = 1; match <= matches; match++) {
            int idx = (match - 1) * (1 << round);
            int a = results[idx];
            int b = results[idx + (1 << (round - 1))];
            if (a == losers[round - 1][match - 1] || b == losers[round - 1][match - 1]) {
                if (a == losers[round - 1][match - 1]) {
                    results[idx] = b;
                    results[idx + (1 << (round - 1))] = a;
                }
            } else {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int k;
    scanf("%d", &k);
    int n = 1 << k;

    for (int i = 0; i < k; i++) {
        int matches = n / (1 << (i + 1));
        for (int j = 0; j < matches; j++) {
            scanf("%d", &losers[i][j]);
        }
    }

    scanf("%d", &final_winner);
    results[n - 1] = final_winner;

    for (int i = 0; i < (1 << (k - 1)); i++) {
        int idx1 = i * 2;
        int idx2 = idx1 + 1;
        results[idx1] = losers[0][i];
        results[idx2] = final_winner;
    }

    if (!validate(k, n)) {
        printf("No Solution\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("%d", results[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}
#include <stdio.h>

#define MAX_N 1000
#define MAX_M 100

int map[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int N, M;

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int x, int y, int *has_treasure) {
    visited[x][y] = 1;

    if (map[x][y] > 1) {
        *has_treasure = 1;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if (nx >= 0 && nx < N && ny >= 0 && ny < M && map[nx][ny] > 0 && !visited[nx][ny]) {
            dfs(nx, ny, has_treasure);
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

    int total_islands = 0;
    int treasure_islands = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] > 0 && !visited[i][j]) {
                int has_treasure = 0;
                dfs(i, j, &has_treasure);
                total_islands++;
                if (has_treasure) {
                    treasure_islands++;
                }
            }
        }
    }

    printf("%d %d\n", total_islands, treasure_islands);

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100000
#define MAX_M 200

typedef struct {
    int city;
    int power;
} Superhero;

typedef struct {
    int city1;
    int city2;
    int time;
} Road;

typedef struct {
    int city;
    int power;
} Alliance;

Superhero superheroes[MAX_N];
Road roads[MAX_N];
int city_count[MAX_M];
Alliance city_alliances[MAX_M];
int city_superheroes[MAX_M][MAX_N];
int distances[MAX_M][MAX_M];
int visited[MAX_M];

int N, M, Me, D;

void init_distances() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            distances[i][j] = (i == j) ? 0 : INT_MAX / 2;
        }
    }
}

void floyd_warshall() {
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                if (distances[i][j] > distances[i][k] + distances[k][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }
}

int find_nearest_target(int my_city, int my_power, int *target_city, int *target_power) {
    int min_distance = INT_MAX;
    int found = 0;
    for (int i = 0; i < M; i++) {
        if (i == my_city) continue;
        if (city_alliances[i].power > 0 && city_alliances[i].power <= my_power) {
            if (distances[my_city][i] < min_distance) {
                min_distance = distances[my_city][i];
                *target_city = i;
                *target_power = city_alliances[i].power;
                found = 1;
            } else if (distances[my_city][i] == min_distance) {
                if (city_count[i] < city_count[*target_city]) {
                    *target_city = i;
                    *target_power = city_alliances[i].power;
                } else if (city_count[i] == city_count[*target_city]) {
                    if (i < *target_city) {
                        *target_city = i;
                        *target_power = city_alliances[i].power;
                    }
                }
            }
        }
    }
    return found;
}

void add_to_alliance(int city, int power) {
    city_alliances[city].power += power;
}

void remove_from_alliance(int city, int power) {
    city_alliances[city].power -= power;
}

void move(int from, int to, int day) {
    printf("Move from %d to %d.\n", from, to);
}

void get(int power, int city, int day) {
    printf("Get %d at %d on day %d.\n", power, city, day);
}

void win(int power, int day) {
    printf("WIN on day %d with %d!\n", day, power);
}

void lose(int power, int day) {
    printf("Lose on day %d with %d.\n", day, power);
}

void game_over(int power) {
    printf("Game over with %d.\n", power);
}

int main() {
    scanf("%d %d %d %d", &N, &M, &Me, &D);
    for (int i = 0; i < N; i++) {
        int city, power;
        scanf("%d %d", &city, &power);
        superheroes[i].city = city;
        superheroes[i].power = power;
        city_superheroes[city][city_count[city]++] = power;
        add_to_alliance(city, power);
    }

    init_distances();
    for (int i = 0; i < Me; i++) {
        int city1, city2, time;
        scanf("%d %d %d", &city1, &city2, &time);
        distances[city1][city2] = distances[city2][city1] = time;
    }

    floyd_warshall();

    int my_city = superheroes[0].city;
    int my_power = superheroes[0].power;
    int day = 0;

    while (day < D) {
        int target_city, target_power;
        if (!find_nearest_target(my_city, my_power, &target_city, &target_power)) {
            game_over(my_power);
            return 0;
        }

        day += distances[my_city][target_city];
        if (day >= D) {
            game_over(my_power);
            return 0;
        }

        my_city = target_city;
        move(superheroes[0].city, target_city, day);

        day++;
        get(target_power, target_city, day);
        my_power += target_power;
        remove_from_alliance(target_city, target_power);

        if (city_alliances[target_city].power > my_power) {
            lose(my_power, day);
            return 0;
        }
    }

    win(my_power, day);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int color;
    int cost;
    int children_count;
    int children[MAX_N];
} Node;

Node nodes[MAX_N];
int dp[MAX_N][2];  // dp[i][0] is the min cost to make subtree rooted at i good without changing i's color
                   // dp[i][1] is the min cost to make subtree rooted at i good with changing i's color

void dfs(int current) {
    dp[current][0] = dp[current][1] = 0;
    int black = nodes[current].color == 1 ? 1 : 0;
    int white = 1 - black;
    int sub_cost[2][2] = {0};

    for (int i = 0; i < nodes[current].children_count; i++) {
        int child = nodes[current].children[i];
        dfs(child);

        black += dp[child][1];
        white += dp[child][0];

        sub_cost[0][0] += dp[child][0];
        sub_cost[0][1] += dp[child][1];
        sub_cost[1][0] += dp[child][1];
        sub_cost[1][1] += dp[child][0];
    }

    dp[current][0] = sub_cost[0][0];
    dp[current][1] = nodes[current].cost + sub_cost[1][1];

    if (abs(black - white) > 1) {
        dp[current][0] = sub_cost[1][0];
        dp[current][1] = nodes[current].cost + sub_cost[0][1];
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &nodes[i].color, &nodes[i].cost, &nodes[i].children_count);
        for (int j = 0; j < nodes[i].children_count; j++) {
            scanf("%d", &nodes[i].children[j]);
        }
    }

    dfs(1);

    printf("%d\n", dp[1][1] < dp[1][0] ? dp[1][1] : dp[1][0]);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef struct {
    int left;
    int right;
} Interval;

int t, n, m;
Interval intervals[100000];

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &intervals[i].left, &intervals[i].right);
        }

        int count = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int valid = 1;
                for (int k = 0; k < m; k++) {
                    int l = intervals[k].left;
                    int r = intervals[k].right;

                    if ((l <= i && i <= r) || (l <= j && j <= r)) {
                        if (!((l <= i && i <= r) && (l <= j && j <= r))) {
                            valid = 0;
                            break;
                        }
                    }
                }

                if (valid) {
                    count++;
                    if (count >= MOD) {
                        count -= MOD;
                    }
                }
            }
        }

        printf("%d\n", count);
    }

    return 0;
}
