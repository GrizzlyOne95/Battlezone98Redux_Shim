/*
 * Entry: 004818a4
 * Name: FindGASObject
 * Namespace: Global
 * Signature: _gas_object * FindGASObject(char * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl FindGASObject(char *param_1,_OBJ76 *param_2)

{
  int iVar1;
  _gas_object *p_Var2;
  
  p_Var2 = firstSound;
  do {
    if (p_Var2 == (_gas_object *)0x0) {
      return (_gas_object *)0x0;
    }
    if (p_Var2->obj76 == param_2) {
      if (param_1 == (char *)0x0) {
        return p_Var2;
      }
      iVar1 = _stricmp((p_Var2->gc).name,param_1);
      if (iVar1 == 0) {
        return p_Var2;
      }
    }
    p_Var2 = p_Var2->next;
  } while( true );
}
