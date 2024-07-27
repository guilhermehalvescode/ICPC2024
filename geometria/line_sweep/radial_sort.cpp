#include <bits/stdc++.h>

using namespace std;

class Point
{
public:
  double x, y;
  Point(double x, double y)
  { // Construtor
    this->x = x;
    this->y = y;
  }
  Point operator-(const Point &a) const
  {
    // permite subtrair dois objetos Point, retornando um novo  Point que representa o vetor resultante

    // subtração das coordenadas dos dois pontos.
    return Point(this->x - a.x, this->y - a.y);
  }
  double operator*(const Point &a) const
  {
    // Produto vetorial de dois vetores
    return this->x * a.y - this->y * a.x;
  }
  double operator%(const Point &a) const
  {
    // Produto escalar de dois vetores
    return this->x * a.x + this->y * a.y;
  }
  int region_value(const Point &P0) const
  {
    // Determine o valor da região de um ponto relativo a P0
    Point rel = *this - P0;
    if (rel.y > 0 || (rel.y == 0 && rel.x >= 0))
    {
      return 0;
    }
    return 1;
  }
  bool operator<(const Point &a) const
  {
    // Isso será redefinido na função principal
    return false;
  }
};
Point P0(0.0, 0.0); // Ponto de referência para ordenação radial
bool radial_compare(const Point &p1, const Point &p2)
{
  if (p1.region_value(P0) != p2.region_value(P0))
  {
    return p1.region_value(P0) < p2.region_value(P0); // aqui na região, vai ser a referência para as direções anti horária ou horária

    // você define ela em region_value
  }
  Point relP1 = p1 - P0;
  Point relP2 = p2 - P0;
  if (relP1 * relP2 != 0)
  {
    return relP1 * relP2 > 0; // aqui pega em sentido anti horário, se quiser sentido horário só trocar o sinal para menor
  }
  return relP1 % relP1 < relP2 % relP2;
  // se estiver na mesma "reta", pega o mais perto, se quiser o mais longe, é só trocar o sinal para maior
}

void radial_sort(vector<Point> V)
{
  // Ordene a lista de pontos com base na comparação radial em relação a P0

  sort(V.begin(), V.end(), radial_compare);
}