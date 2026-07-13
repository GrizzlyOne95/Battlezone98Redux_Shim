/*
 * Entry: 00452830
 * Name: std::sort_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void sort_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::sort_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3)

{
  Strip *pSVar1;
  int iVar2;
  
  for (iVar2 = (int)param_2 - (int)param_1; 1 < iVar2 >> 2; iVar2 = iVar2 + -4) {
    pSVar1 = *(Strip **)((int)param_1 + iVar2 + -4);
    *(Strip **)((int)param_1 + iVar2 + -4) = *param_1;
    _Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_1,0,iVar2 + -4 >> 2,pSVar1,param_3);
  }
  return;
}
