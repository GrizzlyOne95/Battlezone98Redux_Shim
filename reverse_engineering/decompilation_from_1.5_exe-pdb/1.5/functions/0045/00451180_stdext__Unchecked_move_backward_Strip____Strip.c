/*
 * Entry: 00451180
 * Name: stdext::_Unchecked_move_backward<Strip_*_*,Strip_*_*>
 * Namespace: stdext
 * Signature: Strip * * _Unchecked_move_backward<Strip_*_*,Strip_*_*>(Strip * * param_1, Strip * * param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __cdecl
stdext::_Unchecked_move_backward<Strip_*_*,Strip_*_*>
          (Strip **param_1,Strip **param_2,Strip **param_3)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (0 < iVar1) {
    memmove_s(param_3 + -iVar1,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + -iVar1;
}
