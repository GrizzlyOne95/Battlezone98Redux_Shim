/*
 * Entry: 00516e4f
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::size
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: uint size(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::size
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 3;
}
