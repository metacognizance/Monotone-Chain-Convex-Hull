#include <vector>
#include <algorithm>
#include <time.h>

typedef int coord_t;

typedef long long coord2_t;

struct Point
{
	Point() :
		m_x(0),
		m_y(0)
	{

	}
	
	Point(const coord_t & p_x, const coord_t & p_y) :
		m_x(p_x),
		m_y(p_y)
	{

	}

	~Point()
	{

	}

	coord_t m_x, m_y;

	bool operator<(const Point & p_point)
	{
		return (m_x < p_point.m_x) ? m_x < p_point.m_x:(m_x == p_point.m_x ? m_y < p_point.m_y:false);
	}

	bool operator>(const Point & p_point)
	{
		return (m_x > p_point.m_x) ? m_x > p_point.m_x:(m_x == p_point.m_x ? m_y > p_point.m_y:false);
	}
};

std::vector<Point> ConvexHull(std::vector<Point> & p_points);

int main()
{
	srand(static_cast<int>(time(NULL)));

	std::vector<Point> points;

	for (int i = 0; i < 32; ++i)
	{
		points.push_back(Point((-100 + (std::rand() % (100 - (-100)) + 1)), (-100 + (std::rand() % (100 - (-100)) + 1))));
	}

	points = ConvexHull(points);

	return 0;
}

coord2_t cross(const Point & p_O, const Point & p_A, const Point & p_B)
{
	return ((p_A.m_x - p_O.m_x) * (coord2_t)(p_B.m_y - p_O.m_y) - (p_A.m_y - p_O.m_y) * (coord2_t)(p_B.m_x - p_O.m_x));
}

std::vector<Point> ConvexHull(std::vector<Point> & p_points)
{
	int n = p_points.size();
	int k = 0;

	std::vector<Point> H(2*n);

	std::sort(p_points.begin(), p_points.end());


	//lower
	for (int i = 0; i < n; ++i)
	{
		while(k >= 2 && cross(H[k-2], H[k-1], p_points[i]) <= 0)
		{
		    k--;
		}
		H[k++] = p_points[i];
	}


	//upper
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], p_points[i]) <= 0)
		{
			k--;
		}
		H[k++] = p_points[i];
	}
 
	H.resize(k);
	return H;
}