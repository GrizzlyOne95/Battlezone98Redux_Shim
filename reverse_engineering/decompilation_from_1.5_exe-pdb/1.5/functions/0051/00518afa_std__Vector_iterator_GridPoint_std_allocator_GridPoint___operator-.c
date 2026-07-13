/*
 * Entry: 00518afa
 * Name: std::_Vector_iterator<GridPoint,std::allocator<GridPoint>_>::operator-=
 * Namespace: std::_Vector_iterator<GridPoint,std::allocator<GridPoint>_>
 * Signature: _Vector_iterator<GridPoint,std::allocator<GridPoint>_> * operator-=(_Vector_iterator<GridPoint,std::allocator<GridPoint>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GridPoint,std::allocator<GridPoint>_> * __thiscall
std::_Vector_iterator<GridPoint,std::allocator<GridPoint>_>::operator-=
          (_Vector_iterator<GridPoint,std::allocator<GridPoint>_> *this,int param_1)

{
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::operator+=
            ((_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> *)this,-param_1);
  return this;
}
