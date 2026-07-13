/*
 * Entry: 004820cf
 * Name: StartGASEvent
 * Namespace: Global
 * Signature: _gas_object * StartGASEvent(char * param_1, _OBJ76 * param_2, GAS_CTRL * param_3, GAS_PREP_INFO * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl
StartGASEvent(char *param_1,_OBJ76 *param_2,GAS_CTRL *param_3,GAS_PREP_INFO *param_4)

{
  _gas_object *p_Var1;
  long lVar2;
  GAS_CTRL *unaff_ESI;
  _gas_object *unaff_retaddr;
  
  if (GM == (GAS_MASTER *)0x0) {
    return (_gas_object *)0x0;
  }
  p_Var1 = NewGASObject(param_1,param_2,unaff_ESI,unaff_retaddr);
  if (p_Var1 != (_gas_object *)0x0) {
    lVar2 = OpenGASObject(GM,p_Var1,param_4);
    if (lVar2 != 0) {
      return p_Var1;
    }
    DeleteGASObject(p_Var1);
  }
  return (_gas_object *)0x0;
}
