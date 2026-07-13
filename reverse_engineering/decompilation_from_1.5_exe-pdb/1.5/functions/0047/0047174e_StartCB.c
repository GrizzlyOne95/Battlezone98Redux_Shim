/*
 * Entry: 0047174e
 * Name: StartCB
 * Namespace: Global
 * Signature: _gas_object * StartCB(_cb_queue * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

_gas_object * __cdecl StartCB(_cb_queue *param_1)

{
  DWORD DVar1;
  _gas_object *p_Var2;
  GAS_PREP_INFO local_50;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((param_1->pri == 4) && (DVar1 = Get_TimeNow(), 10000 < DVar1 - param_1->time)) {
    return (_gas_object *)0x0;
  }
  InitGASCtrl(&local_34);
  InitGASPrep(&local_50);
  local_34.eofCallback = NextCBInQueue;
  local_34.flags = 5;
  local_50.pri = 10000;
  p_Var2 = StartGASEvent(param_1->name,(_OBJ76 *)0x0,&local_34,&local_50);
  return p_Var2;
}
