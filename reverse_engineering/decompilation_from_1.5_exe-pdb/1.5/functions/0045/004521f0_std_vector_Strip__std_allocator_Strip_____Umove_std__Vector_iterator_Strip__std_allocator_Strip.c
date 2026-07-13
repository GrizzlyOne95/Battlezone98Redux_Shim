/*
 * Entry: 004521f0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Umove<std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>_>
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: Strip * * _Umove<std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>_>(vector<Strip_*,std::allocator<Strip_*>_> * this, _Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_1, _Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::
_Umove<std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>_>
          (vector<Strip_*,std::allocator<Strip_*>_> *this,
          _Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_1,
          _Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_2,Strip **param_3)

{
  int iVar1;
  
  iVar1 = (int)(param_2._4_4_ - param_1._4_4_) >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,(void *)param_1._4_4_,iVar1 * 4);
  }
  return param_3 + iVar1;
}
