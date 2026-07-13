/*
 * Entry: 00518ebf
 * Name: std::_Vector_iterator<GridPoint,std::allocator<GridPoint>_>::_Vector_iterator<GridPoint,std::allocator<GridPoint>_>
 * Namespace: std::_Vector_iterator<GridPoint,std::allocator<GridPoint>_>
 * Signature: _Vector_iterator<GridPoint,std::allocator<GridPoint>_> * _Vector_iterator<GridPoint,std::allocator<GridPoint>_>(_Vector_iterator<GridPoint,std::allocator<GridPoint>_> * this, GridPoint * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GridPoint,std::allocator<GridPoint>_> * __thiscall
std::_Vector_iterator<GridPoint,std::allocator<GridPoint>_>::
_Vector_iterator<GridPoint,std::allocator<GridPoint>_>
          (_Vector_iterator<GridPoint,std::allocator<GridPoint>_> *this,GridPoint *param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>
            ((_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> *)this,param_1,param_2);
  return this;
}
