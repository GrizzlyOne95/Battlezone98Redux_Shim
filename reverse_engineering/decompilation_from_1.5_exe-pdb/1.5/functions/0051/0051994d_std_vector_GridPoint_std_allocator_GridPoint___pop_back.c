/*
 * Entry: 0051994d
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::pop_back
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: void pop_back(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::pop_back
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffff8U) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
