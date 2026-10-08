#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double distance(Point a, Point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main(void)
{
    Point origin = {0.0, 0.0};
    Point p = {3.0, 4.0};

    printf("Distance: %.1f\n", distance(origin, p));
    return 0;
}
