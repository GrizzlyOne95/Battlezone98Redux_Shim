/*
 * Entry: 00470f75
 * Name: DoAudioFixedLoc
 * Namespace: Global
 * Signature: _gas_object * DoAudioFixedLoc(char * param_1, _OBJ76 * param_2, GAS_CTRL * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

_gas_object * __cdecl DoAudioFixedLoc(char *param_1,_OBJ76 *param_2,GAS_CTRL *param_3)

{
  tagENTITY *ptVar1;
  _gas_object *local_38;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_38 = (_gas_object *)0x0;
  if ((param_2 == (_OBJ76 *)0x0) &&
     ((ptVar1 = get_user_entity(), ptVar1 == (tagENTITY *)0x0 ||
      (param_2 = ptVar1->obj76, param_2 == (_OBJ76 *)0x0)))) {
    local_38 = (_gas_object *)0x0;
  }
  else if (param_1 != (char *)0x0) {
    if (param_3 == (GAS_CTRL *)0x0) {
      param_3 = &local_34;
      InitGASCtrl(param_3);
    }
    param_3->flags = param_3->flags | 0x200;
    local_38 = StartGASEvent(param_1,param_2,param_3,(GAS_PREP_INFO *)0x0);
  }
  return local_38;
}
