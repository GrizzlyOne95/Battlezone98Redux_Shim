/*
 * Entry: 005192d0
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::_Tidy
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: void _Tidy(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::_Tidy
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  if (this->_Myfirst != (GridPoint *)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (GridPoint *)0x0;
  this->_Mylast = (GridPoint *)0x0;
  this->_Myend = (GridPoint *)0x0;
  return;
}
