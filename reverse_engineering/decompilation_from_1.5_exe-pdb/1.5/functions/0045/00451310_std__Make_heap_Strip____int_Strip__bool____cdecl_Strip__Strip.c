/*
 * Entry: 00451310
 * Name: std::_Make_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Make_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3, int * param_4, Strip * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Make_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3,
          int *param_4,Strip **param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (int)param_2 - (int)param_1 >> 2;
  iVar2 = iVar3 - ((int)param_2 - (int)param_1 >> 0x1f) >> 1;
  while (0 < iVar2) {
    iVar1 = iVar2 + -1;
    iVar2 = iVar2 + -1;
    _Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_1,iVar2,iVar3,param_1[iVar1],param_3);
  }
  return;
}
