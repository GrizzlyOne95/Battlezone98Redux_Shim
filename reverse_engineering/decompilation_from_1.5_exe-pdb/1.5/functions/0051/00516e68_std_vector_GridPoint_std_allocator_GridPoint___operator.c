/*
 * Entry: 00516e68
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::operator[]
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: GridPoint * operator[](vector<GridPoint,std::allocator<GridPoint>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::operator[]
          (vector<GridPoint,std::allocator<GridPoint>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 3) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
