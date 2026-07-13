/*
 * Entry: 00470f22
 * Name: DoAudioLooping
 * Namespace: Global
 * Signature: _gas_object * DoAudioLooping(char * param_1, _OBJ76 * param_2, GAS_CTRL * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl DoAudioLooping(char *param_1,_OBJ76 *param_2,GAS_CTRL *param_3)

{
  tagENTITY *ptVar1;
  _gas_object *p_Var2;
  GAS_PREP_INFO local_20;
  
  p_Var2 = (_gas_object *)0x0;
  InitGASPrep(&local_20);
  local_20.loopMode = 2;
  if ((param_2 == (_OBJ76 *)0x0) &&
     ((ptVar1 = get_user_entity(), ptVar1 == (tagENTITY *)0x0 ||
      (param_2 = ptVar1->obj76, param_2 == (_OBJ76 *)0x0)))) {
    p_Var2 = (_gas_object *)0x0;
  }
  else if (param_1 != (char *)0x0) {
    p_Var2 = StartGASEvent(param_1,param_2,param_3,&local_20);
  }
  return p_Var2;
}
