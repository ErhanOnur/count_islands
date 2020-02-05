#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class island {

  static vector<island> List_Of_Islands;

  vector<vector<pair<int,int>>> m_point_vec_vec;

  static inline island * GetTopAdjacentIsland(const vector<int>* pTopVec, island* pTopIsland, int x, int y) {
    if ((*pTopVec)[x]) {
        
      if (pTopIsland)
        return pTopIsland;

      auto itr = find_if(List_Of_Islands.begin(), List_Of_Islands.end(), [ & ](auto & xx) {
        return xx.isNearByTop(x, y);
      });

      if (itr == List_Of_Islands.end())
        pTopIsland = nullptr;
      else
        pTopIsland = &(*itr);
    } else
      pTopIsland = nullptr;

    return pTopIsland;
  }

public:

  bool isNearByTop(int x, int y) const {
    for (const auto & point_vec: m_point_vec_vec) {
      if (binary_search(point_vec.begin(), point_vec.end(), make_pair(x, y - 1)))
        return true;
    }
    return false;
  }

  inline void join(int x, int y) {
    m_point_vec_vec[0].push_back(make_pair(x, y));
  }

  static void MergeIsland(island & isl1, island & isl2) {
    move(isl1.m_point_vec_vec.begin(), isl1.m_point_vec_vec.end(), back_inserter(isl2.m_point_vec_vec));
    isl1.m_point_vec_vec.clear();
  }

  static island NewForLonelyIsland(int i, int j) {
    vector<pair<int,int>> point_vec;
    point_vec.emplace_back(i, j);

    island islnew {};
    islnew.m_point_vec_vec.push_back(point_vec);

    return islnew;
  }

  static int GetNumberOfIslands(vector<vector<int>> & vmap) {
    int i = 0, j = 0;

    island *pLeftIsland, *pTopIsland;
    pLeftIsland = pTopIsland = nullptr;

    vector<int>* prevline = & vmap[0];
    int prevpoint = (*prevline)[0];

    if (prevpoint) //first point
    {
      List_Of_Islands.push_back(NewForLonelyIsland(i, j));
      pLeftIsland = &List_Of_Islands[0];
    }

    i = 1;
    for_each(next(prevline->begin()), prevline->end(), [ & ](auto & x) { //first line
      if (x) // we are on the land..
      {
        if (pLeftIsland) //we have a land on previous point...		
          pLeftIsland->join(i, j);
        else {
          List_Of_Islands.push_back(NewForLonelyIsland(i, j));
          pLeftIsland = &(List_Of_Islands.back());
        }
      } else
        pLeftIsland = nullptr;

      i++;
    });

    j = 1;
    for_each(next(vmap.begin()), vmap.end(), [ & ](auto & yvec) {

      pTopIsland = pLeftIsland = nullptr;
      i = 0;

      for_each(yvec.begin(), yvec.end(), [ & ](auto & x) {
        if (x) // we are on the land..
        {
          pTopIsland = GetTopAdjacentIsland(prevline, pTopIsland, i, j);

          if (pLeftIsland && pTopIsland) //we have a land on top and left adjacent points...
          {
            pLeftIsland->join(i, j);
            if (pTopIsland != pLeftIsland)
              MergeIsland( * pTopIsland, * pLeftIsland);
          } else if (pLeftIsland) //we have a land on left adjacent point...
          {
            pLeftIsland->join(i, j);
          } else if (pTopIsland) //we have a land on top adjacent point...
          {
            pTopIsland->join(i, j);
            pLeftIsland = pTopIsland;
          } else //lonely land.. no neigbor at top and left...
          {
            List_Of_Islands.push_back(NewForLonelyIsland(i, j));
            pLeftIsland = & (List_Of_Islands.back());
          }
        } else
          pLeftIsland = nullptr;

        i++;

      });

      prevline = & yvec;
      j++;
    });

    return count_if(List_Of_Islands.begin(), List_Of_Islands.end(), [](const auto & ix) {
      return ix.m_point_vec_vec.size() > 0;
    });
  }

};

vector < island > island::List_Of_Islands {};

int main() {
  vector <vector<int>> vmap  { {1,1,1,0,1,0,0,0},
							   {0,0,0,0,1,0,1,0},
							   {1,1,1,0,1,1,1,0}};

  for (auto & vec: vmap) {
    for (auto & p: vec)
      cout << p << " ";
    cout << endl;
  }

  cout << "Number of island:" << island::GetNumberOfIslands(vmap) << endl;

}
