#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef  int island_id;

struct island_range {
  int x_beg;
  int x_end;
  island_id id;
  island_range(int xb, int xe, island_id id) : x_beg{xb}, x_end{xe}, id{id}  {}
};

int main()
{	
  vector<vector<int>> vmap {
                            { 1, 1, 1, 0, 1, 0, 0, 0 },
                            { 0, 0, 0, 0, 1, 0, 1, 0 },
                            { 1, 1, 1, 0, 1, 1, 1, 0 }
                            };

  vector<island_range>* vec_top = new vector<island_range>{};
  vector<island_range>* vec_current = new vector<island_range>{};
  vec_top->reserve(vmap[0].size()/2+1);
  vec_current->reserve(vmap[0].size()/2+1);
  unordered_set<island_id> unique_islands;

  island_id island_id_count = 0;

  for (auto &vec: vmap)
  {
    for (auto &p: vec)
      cout << p << " ";
    cout << endl;
  }

  for (auto y_itr = vmap.begin() ; y_itr != vmap.end(); ++y_itr)
  {
    auto& vt = *vec_top;
    auto& vc = *vec_current;

    auto vtop_itr = vt.begin();

    //cout << "\nanalizing line number " << y+1 << endl;

    for (auto x_itr = y_itr->begin() ; x_itr != y_itr->end(); ++x_itr)
    {
      int& value = *x_itr;
      //cout << "*** analyzing the point ( " << x << "," << y << ") with value: " << value <<endl; 

      if (value)
      {
        island_id left=0, top=0;
        int x = distance(y_itr->begin(), x_itr);

        while (vtop_itr != vt.end())
        {
          //cout << "checking top rage with island id :" << vtop_itr->id <<endl; 
          if (x >= vtop_itr->x_beg && x <= vtop_itr->x_end)
          {
            top = vtop_itr->id;
          }
          if (x > vtop_itr->x_end)
          {
            ++vtop_itr;
            //cout << "jumping to the next top range... " <<endl; 
            continue;
          }
          break;
        }

        if (!vc.empty())
        {
          if (x-1 == vc.rbegin()->x_end)
          left = vc.rbegin()->id;
        }

        //cout << "left adjacent island id: " << left << ", top adjacent island id: " << top << endl; 

        if (left && top) //we have island at top and at left
        {
          auto id = vc.rbegin()->id;
          if (id != vtop_itr->id)
          {
            unique_islands.erase(vtop_itr->id);
            //cout << "two island with different island ids!.. merge happens!..";
            //cout << " erasing merged island id: " << vtop_itr->id << endl;
            vtop_itr->id = id;
          }
          vc.rbegin()->x_end = x; 
        } 
        else if (left) // we have island on left
        {
          vc.rbegin()->x_end = x; 

        } else if (top) // we have island on top
        {
          vec_current->emplace_back(x,x,top);
        }
        else //lonely island
        {
          vec_current->emplace_back(x,x, ++island_id_count);
          unique_islands.insert(island_id_count);

          //cout << "inserting new island id : " << island_id_count << endl;
        }
      }
    }

    //cout <<endl; 

    vec_top->clear();
    auto tmp = vec_top;
    vec_top = vec_current;
    vec_current = tmp;

    /*cout << "vec_top "; 
    for (auto &p: *vec_top)
      cout << "(" << p.x_beg << "," << p.x_end << "," << p.id << ")  ";
    cout << endl;*/

  }

  cout << "Number of island:" << unique_islands.size() << endl;

}
