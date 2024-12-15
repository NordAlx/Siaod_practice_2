#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

// Определение точки
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Функция для вычисления площади по формуле Гаусса
double calculateArea(const vector<Point>& points) {
    double area = 0;
    int n = points.size();
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;  // Следующая точка
        area += points[i].x * points[next].y - points[i].y * points[next].x;
    }
    return abs(area) / 2.0;
}

// Итеративный метод ветвей и границ
double branchAndBound(const vector<Point>& points) {
    double maxArea = 0;
    int n = points.size();

    // Стек для хранения состояния
    stack<vector<Point>> stackPaths;
    stack<vector<bool>> stackVisited;

    // Инициализация стека
    for (int i = 0; i < n; ++i) {
        vector<Point> path = { points[i] };
        vector<bool> visited(n, false);
        visited[i] = true;
        stackPaths.push(path);
        stackVisited.push(visited);
    }

    // Итеративный процесс
    while (!stackPaths.empty()) {
        auto path = stackPaths.top();
        stackPaths.pop();
        auto visited = stackVisited.top();
        stackVisited.pop();

        // Если путь замкнут
        if (path.size() == n + 1 && path.front().x == path.back().x && path.front().y == path.back().y) {
            double area = calculateArea(path);
            maxArea = max(maxArea, area);
            continue;
        }

        // Ветвление
        for (size_t i = 0; i < n; ++i) {
            // Добавляем точку, если она ещё не посещена
            if (!visited[i]) {
                vector<Point> newPath = path;
                vector<bool> newVisited = visited;

                newPath.push_back(points[i]);
                newVisited[i] = true;

                // Проверяем, не замкнётся ли путь после добавления этой точки
                if (newPath.size() == n + 1 && newPath.front().x == newPath.back().x && newPath.front().y == newPath.back().y) {
                    maxArea = max(maxArea, calculateArea(newPath));
                }
                else {
                    stackPaths.push(newPath);
                    stackVisited.push(newVisited);
                }
            }
        }
    }

    return maxArea;
}

vector<Point> readPoints() {
    vector<Point> points;
    string line;

    cout << "Введите пары координат x и y (каждая пара с новой строки, пустая строка для завершения):" << endl;

    while (getline(cin, line)) {
        if (line.empty()) 
            break; 

        stringstream ss(line);
        double x, y;
        if (ss >> x >> y) {
            points.emplace_back(x, y); // Добавляем точку в вектор
        }
        else {
            cerr << "Ошибка ввода. Проверьте формат (должны быть два числа, разделённые пробелом)." << endl;
        }
    }

    return points;
}

int main() {
    setlocale(LC_ALL, "Ru");

    vector<Point> points = readPoints();

    double maxArea = branchAndBound(points);

    // Вывод результата
    cout << "Максимальная площадь фигуры: " << maxArea << endl;
    return 0;
}