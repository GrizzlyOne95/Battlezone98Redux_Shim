/*
 * Entry: 0051704f
 * Name: std::_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::operator-
 * Namespace: std::_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>
 * Signature: int operator-(_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> * this, _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
std::_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::operator-
          (_Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> *this,
          _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return (int)this->_Myptr - (int)param_1->_Myptr >> 3;
}
