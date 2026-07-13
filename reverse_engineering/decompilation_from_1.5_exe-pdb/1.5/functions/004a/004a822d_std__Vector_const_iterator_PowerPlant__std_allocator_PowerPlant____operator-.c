/*
 * Entry: 004a822d
 * Name: std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator-
 * Namespace: std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: int operator-(_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator-
          (_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,
          _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return (int)this->_Myptr - (int)param_1->_Myptr >> 2;
}
