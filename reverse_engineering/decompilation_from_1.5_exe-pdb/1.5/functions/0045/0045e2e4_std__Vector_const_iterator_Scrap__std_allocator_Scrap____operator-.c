/*
 * Entry: 0045e2e4
 * Name: std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator-
 * Namespace: std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: int operator-(_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> * this, _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator-
          (_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *this,
          _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return (int)this->_Myptr - (int)param_1->_Myptr >> 2;
}
