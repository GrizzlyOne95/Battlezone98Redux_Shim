/*
 * Entry: 0044fff0
 * Name: std::_Push_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Push_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, int param_2, int param_3, Strip * param_4, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Push_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,int param_2,int param_3,Strip *param_4,
          _func___cdecl_bool_Strip_ptr_Strip_ptr *param_5)

{
  bool bVar1;
  int iVar2;
  
  if (param_2 <= param_3) {
    param_1[param_2] = param_4;
    return;
  }
  do {
    iVar2 = (param_2 + -1) / 2;
    bVar1 = (*param_5)(param_1[iVar2],param_4);
    if (!bVar1) break;
    param_1[param_2] = param_1[iVar2];
    param_2 = iVar2;
  } while (param_3 < iVar2);
  param_1[param_2] = param_4;
  return;
}
