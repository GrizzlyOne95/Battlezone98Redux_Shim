/*
 * Entry: 00492044
 * Name: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator-
 * Namespace: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: int operator-(_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * this, _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator-
          (_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *this,
          _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *param_1)

{
  if ((*(int *)this == 0) || (*(int *)this != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return *(int *)&this->field_0x4 - (int)param_1->_Myptr >> 2;
}
