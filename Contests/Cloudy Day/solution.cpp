/*
 * HackerRank - Cloudy Day
 * https://www.hackerrank.com/contests/hourrank-26/challenges/cloudy-day/problem
 * Author: Rafal Kozik
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

#define LOG(x) std::cout << x << std::endl

struct Object
{
    enum class Type
    {
        CloudStart,
        CloudEnd,
        City
    };

    int64_t position;
    Type type;
    int index;

    Object(int64_t p, Type t, int i) : position(p), type(t), index(i) { }

    bool operator<(const Object& o) const
    {
        if (position == o.position)
        {
            return type < o.type;
        }
        return position < o.position;
    }
};

int64_t maximumPeople(std::vector<int64_t>& p, std::vector<int64_t>& x, std::vector<int64_t>& y, std::vector<int64_t>& r)
{
    std::vector<Object> objects;
    std::map<int,int64_t> made_happier;
    std::set<int> clouds;
    int64_t happy = 0;
    for (auto i = 0u; i < x.size(); ++i)
    {
        objects.emplace_back(x[i], Object::Type::City, i);
    }
    for (auto i = 0u; i < y.size(); ++i)
    {
        objects.emplace_back(y[i] - r[i], Object::Type::CloudStart, i);
        objects.emplace_back(y[i] + r[i] + 1, Object::Type::CloudEnd, i);
    }
    std::sort(objects.begin(), objects.end());
    for (auto i = 0u; i < objects.size(); ++i)
    {
        if (objects[i].type == Object::Type::City)
        {
            if (clouds.size() == 1)
            {
                made_happier[*clouds.begin()] += p[objects[i].index];
            }
            else if (clouds.size() == 0)
            {
                happy += p[objects[i].index];
            }
        }
        else if (objects[i].type == Object::Type::CloudStart)
        {
            clouds.insert(objects[i].index);
        }
        else
        {
            clouds.erase(objects[i].index);
        }
    }
    int64_t max = 0;
    for (auto pair : made_happier)
    {
        max = std::max(max, pair.second);
    }
    return happy + max;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int64_t> p(n);
    for (int i = 0; i < n; i++)
    {
       std::cin >> p[i];
    }
    std::vector<int64_t> x(n);
    for (int i = 0; i < n; i++)
    {
       std::cin >> x[i];
    }
    int m;
    std::cin >> m;
    std::vector<int64_t> y(m);
    for (int i = 0; i < m; i++)
    {
       std::cin >> y[i];
    }
    std::vector<int64_t> r(m);
    for (int i = 0; i < m; i++)
    {
       std::cin >> r[i];
    }
    LOG(maximumPeople(p, x, y, r));
}

