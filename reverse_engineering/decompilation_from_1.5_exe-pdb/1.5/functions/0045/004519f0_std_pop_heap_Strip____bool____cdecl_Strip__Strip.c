/*
 * Entry: 004519f0
 * Name: std::pop_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void pop_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::pop_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3)

{
  Strip *pSVar1;
  
  if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
    pSVar1 = param_2[-1];
    param_2[-1] = *param_1;
    _Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_1,0,(int)(((int)param_2 - (int)param_1) - 4U) >> 2,pSVar1,param_3);
  }
  return;
}
