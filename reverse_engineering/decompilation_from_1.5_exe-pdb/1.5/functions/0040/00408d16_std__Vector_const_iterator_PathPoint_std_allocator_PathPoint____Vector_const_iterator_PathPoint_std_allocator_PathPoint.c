/*
 * Entry: 00408d16
 * Name: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
 * Namespace: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>(_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * this, PathPoint * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::
_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
          (_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *this,PathPoint *param_1,
          _Container_base_aux *param_2)

{
  this->_padding_ = 0;
  if (((param_2 == (_Container_base_aux *)0x0) || (param_1 < (PathPoint *)param_2[3]._Myownedaux))
     || ((PathPoint *)param_2[4]._Myownedaux < param_1)) {
    _invalid_parameter_noinfo();
  }
  this->_padding_ = (int)param_2->_Myownedaux;
  this->_Myptr = param_1;
  return this;
}
