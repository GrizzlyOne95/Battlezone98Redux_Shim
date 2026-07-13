/*
 * Entry: 005c6d2e
 * Name: _onexit
 * Namespace: Global
 * Signature: _func___cdecl_int * _onexit(_func___cdecl_int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */

_func___cdecl_int * __cdecl _onexit(_func___cdecl_int *param_1)

{
  _func___cdecl_int *p_Var1;
  undefined4 uVar2;
  undefined4 local_24;
  int local_20 [5];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00623830;
  uStack_c = 0x5c6d3a;
  local_20[0] = decode_pointer(__onexitbegin);
  if (local_20[0] == -1) {
    p_Var1 = (*(code *)&DAT_00225a9e)(param_1);
  }
  else {
    lock(8);
    local_8 = (undefined *)0x0;
    local_20[0] = decode_pointer(__onexitbegin);
    local_24 = decode_pointer(__onexitend);
    uVar2 = encode_pointer(param_1,local_20,&local_24);
    p_Var1 = (_func___cdecl_int *)___dllonexit(uVar2);
    __onexitbegin = (_func___cdecl_void **)encode_pointer(local_20[0]);
    __onexitend = (_func___cdecl_void **)encode_pointer(local_24);
    local_8 = (undefined *)0xfffffffe;
    FUN_005c6dca();
  }
  return p_Var1;
}
