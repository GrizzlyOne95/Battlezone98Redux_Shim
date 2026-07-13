/*
 * Entry: 0044f750
 * Name: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator!=
 * Namespace: std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: bool operator!=(_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * this, _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator!=
          (_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *this,
          _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr != param_1->_Myptr;
}
