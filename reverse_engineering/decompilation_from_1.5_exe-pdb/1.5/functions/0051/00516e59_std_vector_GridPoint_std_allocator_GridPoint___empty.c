/*
 * Entry: 00516e59
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::empty
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: bool empty(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::empty
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffff8U) != 0));
}
