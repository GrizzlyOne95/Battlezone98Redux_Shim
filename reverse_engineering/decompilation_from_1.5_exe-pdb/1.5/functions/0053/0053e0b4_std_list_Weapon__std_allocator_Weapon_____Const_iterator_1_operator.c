/*
 * Entry: 0053e0b4
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator==
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>
 * Signature: bool operator==(_Const_iterator<1> * this, _Const_iterator<1> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator==
          (_Const_iterator<1> *this,_Const_iterator<1> *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return (bool)('\x01' - (this->_Ptr != param_1->_Ptr));
}
