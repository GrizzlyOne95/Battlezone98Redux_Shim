/*
 * Entry: 00452620
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Ufill
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: Strip * * _Ufill(vector<Strip_*,std::allocator<Strip_*>_> * this, Strip * * param_1, uint param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::_Ufill
          (vector<Strip_*,std::allocator<Strip_*>_> *this,Strip **param_1,uint param_2,
          Strip **param_3)

{
  uint uVar1;
  Strip **ppSVar2;
  
  ppSVar2 = param_1;
  for (uVar1 = param_2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *ppSVar2 = *param_3;
    ppSVar2 = ppSVar2 + 1;
  }
  return param_1 + param_2;
}
