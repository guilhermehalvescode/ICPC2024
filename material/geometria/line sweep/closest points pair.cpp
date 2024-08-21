#include <bits/stdc++.h>

using namespace std;

// Defina a estrutura para um ponto
struct Point
{
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  bool operator<(Point a)
  {
    if (x != a.x)
      return x < a.x;
    return y < a.y;
  }
};
// Função para calcular a distância euclidiana entre dois pontos
double distpointpoint(Point a, Point b)
{
  double dx = b.x - a.x;
  double dy = b.y - a.y;
  double resp = sqrt(dx * dx + dy * dy);
  return resp;
}
// Função para encontrar a distância mínima entre dois pontos
pair<Point, Point> closestPoints(vector<Point> s)
{
  // Ordene os pontos de acordo com sua coordenada x
  sort(s.begin(), s.end());
  int p = 0;
  set<pair<double, int>> activated;
  // Inicialize a distância mínima como a distância entre os doisprimeiros pontos
  double answer = distpointpoint(s[0], s[1]);
  pair<Point, Point> closestPair(s[0], s[1]);
  for (int i = 0; i < (int)s.size(); i++)
  {
    // Verifique apenas os pontos que estão dentro da distância mínima atual no eixo x
    while (s[i].x - s[p].x > answer)
    {
      activated.erase({s[p].y, p});
      p++;
    }
    pair<double, int> searchpoint = {s[i].y - floor(answer), 0};
    auto it = activated.lower_bound(searchpoint);
    // Verifique os pontos que estão dentro da distância mínima atual no eixo y
    while (it != activated.end() && it->first <= s[i].y +
                                                     floor(answer))
    {
      // Atualize a distância mínima e os pontos mais próximos se necessário
      double distance = distpointpoint(s[it->second], s[i]);
      if (distance < answer)
      {
        answer = distance;
        closestPair = {s[it->second], s[i]};
      }
      it++;
    }
    activated.insert({s[i].y, i});
  }
  return closestPair;
}