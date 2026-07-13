/*
 * Entry: 00450ee0
 * Name: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>
 * Namespace: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> * _Vector_iterator<Strip_*,std::allocator<Strip_*>_>(_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * this, Strip * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * __thiscall
std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::
_Vector_iterator<Strip_*,std::allocator<Strip_*>_>
          (_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *this,Strip **param_1,
          _Container_base_aux *param_2)

{
  *(undefined4 *)this = 0;
  if (((param_2 == (_Container_base_aux *)0x0) || (param_1 < param_2[3]._Myownedaux)) ||
     (param_2[4]._Myownedaux < param_1)) {
    _invalid_parameter_noinfo();
  }
  *(_Aux_cont **)this = param_2->_Myownedaux;
  *(Strip ***)&this->field_0x4 = param_1;
  return this;
}
