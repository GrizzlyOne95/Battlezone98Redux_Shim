/*
 * Entry: 00452290
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Umove<Strip_*_*>
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: Strip * * _Umove<Strip_*_*>(vector<Strip_*,std::allocator<Strip_*>_> * this, Strip * * param_1, Strip * * param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::_Umove<Strip_*_*>
          (vector<Strip_*,std::allocator<Strip_*>_> *this,Strip **param_1,Strip **param_2,
          Strip **param_3)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
