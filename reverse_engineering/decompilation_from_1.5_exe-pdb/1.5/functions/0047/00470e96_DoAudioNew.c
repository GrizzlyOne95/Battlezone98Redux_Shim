/*
 * Entry: 00470e96
 * Name: DoAudioNew
 * Namespace: Global
 * Signature: _gas_object * DoAudioNew(char * param_1, _OBJ76 * param_2, GAS_CTRL * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl DoAudioNew(char *param_1,_OBJ76 *param_2,GAS_CTRL *param_3)

{
  tagENTITY *ptVar1;
  _gas_object *p_Var2;
  
  p_Var2 = (_gas_object *)0x0;
  if (param_2 == (_OBJ76 *)0x0) {
    ptVar1 = get_user_entity();
    if ((ptVar1 == (tagENTITY *)0x0) || (param_2 = ptVar1->obj76, param_2 == (_OBJ76 *)0x0)) {
      return (_gas_object *)0x0;
    }
  }
  if (param_1 != (char *)0x0) {
    p_Var2 = StartGASEvent(param_1,param_2,param_3,(GAS_PREP_INFO *)0x0);
  }
  return p_Var2;
}
