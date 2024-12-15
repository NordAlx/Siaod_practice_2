#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Line {
    double x1, y1, x2, y2;
    Line(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

double calculateArea(vector<Point> points) {
    double area = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        area += points[i].x * points[(i + 1) % n].y - points[i].y * points[(i + 1) % n].x;
    }

    for (int i = 0; i < points.size(); i++)
        cout << "(" << points[i].x << "; " << points[i].y << ") ";
    cout << abs(area) / 2.0 << endl;

    return abs(area) / 2.0;
}

bool intersection(vector<Line> lines) {
    for (int i = 0; i < lines.size() - 1; i++) {
        for (int j = i + 1; j < lines.size(); j++) {
            double cross1 = (lines[i].x2 - lines[i].x1) * (lines[j].y1 - lines[i].y1) - (lines[i].y2 - lines[i].y1) * (lines[j].x1 - lines[i].x1);
            double cross2 = (lines[i].x2 - lines[i].x1) * (lines[j].y2 - lines[i].y1) - (lines[i].y2 - lines[i].y1) * (lines[j].x2 - lines[i].x1);
            double cross3 = (lines[j].x2 - lines[j].x1) * (lines[i].y1 - lines[j].y1) - (lines[j].y2 - lines[j].y1) * (lines[i].x1 - lines[j].x1);
            double cross4 = (lines[j].x2 - lines[j].x1) * (lines[i].y2 - lines[j].y1) - (lines[j].y2 - lines[j].y1) * (lines[i].x2 - lines[j].x1);

            double A_x_min = min(lines[i].x1, lines[i].x2);
            double A_x_max = max(lines[i].x1, lines[i].x2);
            double A_y_min = min(lines[i].y1, lines[i].y2);
            double A_y_max = max(lines[i].y1, lines[i].y2);

            double B_x_min = min(lines[j].x1, lines[j].x2);
            double B_x_max = max(lines[j].x1, lines[j].x2);
            double B_y_min = min(lines[j].y1, lines[j].y2);
            double B_y_max = max(lines[j].y1, lines[j].y2);

            if (
                (cross1 * cross2 < 0 && cross3 * cross4 < 0) ||

                (cross1 == 0 && cross2 == 0 && cross3 == 0 && cross4 == 0 &&
                    A_x_max >= B_x_min && B_x_max >= A_x_min &&
                    A_y_max >= B_y_min && B_y_max >= A_y_min)
                ) {
                return true; 
            }
        }
    }
    return false; 
}

double branchAndBound(const vector<Point>& points) {
    double sum = 0, count = 0;
    int n = points.size();

    stack<vector<Point>> stackPaths;
    stack<vector<bool>> stackVisited;
    stack<vector<Line>> stackLines;

    vector<Point> path = {points[0]};
    vector<bool> visited(n, false);
    vector<Line> lines;
    stackPaths.push(path);
    stackVisited.push(visited);
    stackLines.push(lines);

    while (!stackPaths.empty()) {
        auto path = stackPaths.top();
        stackPaths.pop();
        auto visited = stackVisited.top();
        stackVisited.pop();
        auto lines = stackLines.top();
        stackLines.pop();

        if (path.size() == n + 1 && path.front().x == path.back().x && path.front().y == path.back().y) {
            sum += calculateArea(path);
            count++;
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                vector<Point> newPath = path;
                vector<bool> newVisited = visited;
                vector<Line> newLines = lines;

                newLines.emplace_back(newPath.back().x, newPath.back().y, points[i].x, points[i].y);

                if (!(points[i].x == newPath.back().x) && !(points[i].y == newPath.back().y) && !(newPath.size() == n) || intersection(newLines))
                    continue;

                newPath.push_back(points[i]);
                newVisited[i] = true;

                stackLines.push(newLines);
                stackPaths.push(newPath);
                stackVisited.push(newVisited);
            }
        }
    }

    return sum / count;
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
            points.emplace_back(x, y); 
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

    cout << "Максимальная площадь фигуры: " << maxArea << endl;
    return 0;
}