/*
 * Entry: 00450bb0
 * Name: std::_Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, Strip * * param_3, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,Strip **param_3,
          _func___cdecl_bool_Strip_ptr_Strip_ptr *param_4)

{
  Strip *pSVar1;
  bool bVar2;
  
  bVar2 = (*param_4)(*param_2,*param_1);
  if ((bVar2) && (param_2 != param_1)) {
    pSVar1 = *param_2;
    *param_2 = *param_1;
    *param_1 = pSVar1;
  }
  bVar2 = (*param_4)(*param_3,*param_2);
  if ((bVar2) && (param_3 != param_2)) {
    pSVar1 = *param_3;
    *param_3 = *param_2;
    *param_2 = pSVar1;
  }
  bVar2 = (*param_4)(*param_2,*param_1);
  if ((bVar2) && (param_2 != param_1)) {
    pSVar1 = *param_2;
    *param_2 = *param_1;
    *param_1 = pSVar1;
  }
  return;
}
