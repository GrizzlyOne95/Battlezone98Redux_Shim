/*
 * Entry: 00450c20
 * Name: std::_Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, int param_2, int param_3, Strip * param_4, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,int param_2,int param_3,Strip *param_4,
          _func___cdecl_bool_Strip_ptr_Strip_ptr *param_5)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_2;
  while( true ) {
    iVar1 = iVar3 * 2;
    iVar4 = iVar1 + 2;
    if (param_3 <= iVar4) break;
    bVar2 = (*param_5)(param_1[iVar4],param_1[iVar1 + 1]);
    if (bVar2) {
      iVar4 = iVar1 + 1;
    }
    param_1[iVar3] = param_1[iVar4];
    iVar3 = iVar4;
  }
  if (iVar4 == param_3) {
    param_1[iVar3] = param_1[param_3 + -1];
    iVar3 = param_3 + -1;
  }
  _Push_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
            (param_1,iVar3,param_2,param_4,param_5);
  return;
}
