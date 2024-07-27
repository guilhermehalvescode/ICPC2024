#include <bits/stdc++.h>

using namespace std;

const double EPS = 1E-9; // Constante para comparação de precisão
struct pt
{
  double x, y; // Estrutura para representar um ponto
};
struct seg
{
  pt p, q; // Dois pontos definindo um segmento
  int id;  // Identificador do segmento
  double get_y(double x) const
  {
    if (abs(p.x - q.x) < EPS)                           // Se p.x e q.x são praticamente iguais
      return p.y;                                       // Retorna a coordenada y de p
    return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x); // Calcula a coordenada y para a coordenada x dada
  }
};
// Função para verificar se dois intervalos 1D se intersectam
bool intersect1d(double l1, double r1, double l2, double r2)
{
  if (l1 > r1)
    swap(l1, r1); // Garante que l1 <= r1
  if (l2 > r2)
    swap(l2, r2);                          // Garante que l2 <= r2
  return max(l1, l2) <= min(r1, r2) + EPS; // Verifica se há interseção
}
// Função para calcular o vetor entre três pontos
int vec(const pt &a, const pt &b, const pt &c)
{
  double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x -
                                                        a.x);
  return abs(s) < EPS ? 0 : s > 0 ? +1
                                  : -1; // Retorna 0 se os pontos são colineares, +1 se c está à esquerda de ab, -1 se c está à direita de ab
}
// Função para verificar se dois segmentos se intersectam
bool intersect(const seg &a, const seg &b)
{
  return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
         intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
         vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
         vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}
// Sobrecarga do operador < para comparar segmentos com base na coordenada y

bool operator<(const seg &a, const seg &b)
{
  double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
  return a.get_y(x) < b.get_y(x) - EPS;
}
struct event
{
  double x;   // Coordenada x do evento
  int tp, id; // Tipo de evento e id do segmento
  event() {}
  event(double x, int tp, int id) : x(x), tp(tp), id(id) {}
  bool operator<(const event &e) const
  {
    if (abs(x - e.x) > EPS)
      return x < e.x; // Compara pela coordenada x
    return tp > e.tp; // Se as coordenadas x são iguais, compara pelo tipo de evento
  }
};
set<seg> s;                       // Conjunto de segmentos ativos
vector<set<seg>::iterator> where; // Vetor de iteradores para os segmentos

// Função para obter o iterador anterior
set<seg>::iterator
prev(set<seg>::iterator it)
{
  return it == s.begin() ? s.end() : --it;
}
// Função para obter o próximo iterador
set<seg>::iterator next(set<seg>::iterator it)
{
  return ++it;
}
// Função principal para resolver o problema de interseção de segmentos

pair<int, int>
solve(const vector<seg> &a)
{
  int n = (int)a.size();
  vector<event> e;
  for (int i = 0; i < n; ++i)
  {
    e.push_back(event(min(a[i].p.x, a[i].q.x), +1, i)); // Evento de início de segmento

    e.push_back(event(max(a[i].p.x, a[i].q.x), -1, i)); // Evento de término de segmento
  }
  sort(e.begin(), e.end()); // Ordena os eventos
  s.clear();                // Limpa o conjunto de segmentos
  where.resize(a.size());   // Redimensiona o vetor de iteradores
  for (size_t i = 0; i < e.size(); ++i)
  {
    int id = e[i].id;
    if (e[i].tp == +1)
    { // Evento de início de segmento
      set<seg>::iterator nxt = s.lower_bound(a[id]), prv =
                                                         prev(nxt);
      if (nxt != s.end() && intersect(*nxt, a[id]))
        return make_pair(nxt->id, id); // Se o próximo segmento intersecta, retorna os ids
      if (prv != s.end() && intersect(*prv, a[id]))
        return make_pair(prv->id, id); // Se o segmento anterior intersecta, retorna os ids

      where[id] = s.insert(nxt, a[id]); // Insere o segmento no conjunto
    }
    else
    { // Evento de término de segmento
      set<seg>::iterator nxt = next(where[id]), prv =
                                                    prev(where[id]);
      if (nxt != s.end() && prv != s.end() &&
          intersect(*nxt, *prv))
        return make_pair(prv->id, nxt->id); // Se os segmentos anterior e próximo intersectam, retorna os ids

      s.erase(where[id]); // Remove o segmento do conjunto
    }
  }
  return make_pair(-1, -1); // Se não houver interseções, retorna(-1, -1)
}