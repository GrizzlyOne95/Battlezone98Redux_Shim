/*
 * Entry: 0049fd8f
 * Name: SetThreadName
 * Namespace: Global
 * Signature: void SetThreadName(ulong param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */

void __cdecl SetThreadName(ulong param_1,char *param_2)

{
  ULONG_PTR local_2c;
  char *local_28;
  ulong local_24;
  undefined4 local_20;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &_xdata_x;
  uStack_c = 0x49fd9b;
  Sleep(10);
  local_2c = 0x1000;
  local_28 = param_2;
  local_24 = param_1;
  local_20 = 0;
  local_8 = (undefined *)0x0;
  RaiseException(0x406d1388,0,4,&local_2c);
  return;
}
