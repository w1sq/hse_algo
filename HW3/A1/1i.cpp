#include <iostream>
#include <random>
#include <cmath>

using namespace std;

bool isInsideCircle(double x, double y, double cx, double cy, double r)
{
    return pow(x - cx, 2) + pow(y - cy, 2) <= pow(r, 2);
}

int main()
{
    double x1, y1, r1, x2, y2, r2, x3, y3, r3;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    cin >> x3 >> y3 >> r3;

    double minX = min(min(x1 - r1, x2 - r2), x3 - r3);
    double maxX = max(max(x1 + r1, x2 + r2), x3 + r3);
    double minY = min(min(y1 - r1, y2 - r2), y3 - r3);
    double maxY = max(max(y1 + r1, y2 + r2), y3 + r3);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disX(minX, maxX);
    uniform_real_distribution<> disY(minY, maxY);

    int totalPoints = 1000000;
    int pointsInside = 0;

    for (int i = 0; i < totalPoints; i++)
    {
        double x = disX(gen);
        double y = disY(gen);

        if (isInsideCircle(x, y, x1, y1, r1) &&
            isInsideCircle(x, y, x2, y2, r2) &&
            isInsideCircle(x, y, x3, y3, r3))
        {
            pointsInside++;
        }
    }

    double area = (maxX - minX) * (maxY - minY) * pointsInside / totalPoints;
    cout.precision(17);
    cout << area << endl;

    return 0;
}