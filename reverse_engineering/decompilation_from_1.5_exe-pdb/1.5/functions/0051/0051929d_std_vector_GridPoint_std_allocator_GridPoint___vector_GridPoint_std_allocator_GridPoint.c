/*
 * Entry: 0051929d
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::vector<GridPoint,std::allocator<GridPoint>_>
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: vector<GridPoint,std::allocator<GridPoint>_> * vector<GridPoint,std::allocator<GridPoint>_>(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<GridPoint,std::allocator<GridPoint>_> * __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::vector<GridPoint,std::allocator<GridPoint>_>
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  _Vector_val<GridPoint,std::allocator<GridPoint>_>::
  _Vector_val<GridPoint,std::allocator<GridPoint>_>
            ((_Vector_val<GridPoint,std::allocator<GridPoint>_> *)this,SUB41(this,0));
  _Buy(this,0);
  return this;
}
