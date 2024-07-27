#include <bits/stdc++.h>

using namespace std;

// Função para calcular o produto vetorial de três pontos (cross > 0 -> anti-horário/cross < 0 -> horário/cross == 0 -> colineares)
int cross(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
  return (b.first - a.first) * (c.second - a.second) - (b.second -
                                                        a.second) *
                                                           (c.first - a.first);
}
// Forma o fecho convexo no sentido anti-horário dos pontos
vector<pair<int, int>> convexHull(vector<pair<int, int>> &points)
{
  int n = points.size(), k = 0;
  vector<pair<int, int>> hull(2 * n);
  // Ordena os pontos a partir de sua abcissa (eixo x)
  sort(points.begin(), points.end());
  // Constrói o casco inferior
  for (int i = 0; i < n; ++i)
  {
    while (k >= 2 && cross(hull[k - 2], hull[k - 1], points[i]) < 0)
      k--;
    hull[k++] = points[i];
  }
  // Constrói o casco superior
  for (int i = n - 1, t = k + 1; i > 0; --i)
  {
    while (k >= t && cross(hull[k - 2], hull[k - 1], points[i - 1]) < 0)
      k--;
    hull[k++] = points[i - 1];
  }
  hull.resize(k - 1);
  return hull;
}