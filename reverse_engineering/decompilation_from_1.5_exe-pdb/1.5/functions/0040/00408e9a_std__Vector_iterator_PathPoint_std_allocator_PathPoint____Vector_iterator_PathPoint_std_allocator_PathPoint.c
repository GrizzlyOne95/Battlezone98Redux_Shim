/*
 * Entry: 00408e9a
 * Name: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
 * Namespace: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> * _Vector_iterator<PathPoint,std::allocator<PathPoint>_>(_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * this, PathPoint * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::
_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
          (_Vector_iterator<PathPoint,std::allocator<PathPoint>_> *this,PathPoint *param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
            ((_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *)this,param_1,param_2);
  return this;
}
