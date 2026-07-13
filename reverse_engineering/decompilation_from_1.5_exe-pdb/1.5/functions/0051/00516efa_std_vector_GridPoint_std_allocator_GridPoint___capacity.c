/*
 * Entry: 00516efa
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::capacity
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: uint capacity(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::capacity
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  if (this->_Myfirst == (GridPoint *)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 3;
}
