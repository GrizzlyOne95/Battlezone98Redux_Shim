/*
 * Entry: 00451260
 * Name: std::_Median<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Median<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, Strip * * param_3, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Median<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,Strip **param_3,
          _func___cdecl_bool_Strip_ptr_Strip_ptr *param_4)

{
  int iVar1;
  
  iVar1 = (int)param_3 - (int)param_1 >> 2;
  if (0x28 < iVar1) {
    iVar1 = iVar1 + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    _Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_1,param_1 + iVar1,param_1 + iVar1 * 2,param_4);
    _Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_2 + -iVar1,param_2,param_2 + iVar1,param_4);
    _Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_3 + iVar1 * -2,param_3 + -iVar1,param_3,param_4);
    _Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_1 + iVar1,param_2,param_3 + -iVar1,param_4);
    return;
  }
  _Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(param_1,param_2,param_3,param_4);
  return;
}
