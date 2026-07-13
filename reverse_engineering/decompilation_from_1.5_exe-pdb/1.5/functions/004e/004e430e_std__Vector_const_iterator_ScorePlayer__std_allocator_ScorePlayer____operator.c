/*
 * Entry: 004e430e
 * Name: std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator+=
 * Namespace: std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * operator+=(_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * __thiscall
std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator+=
          (_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 != (int *)0x0) goto LAB_004e4327;
    iVar2 = 0;
  }
  else {
LAB_004e4327:
    iVar2 = *piVar1;
  }
  if (this->_Myptr + param_1 <= *(ScorePlayer ***)(iVar2 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1;
    }
    if (*(ScorePlayer ***)(iVar2 + 0xc) <= this->_Myptr + param_1) goto LAB_004e434f;
  }
  _invalid_parameter_noinfo();
LAB_004e434f:
  this->_Myptr = this->_Myptr + param_1;
  return this;
}
