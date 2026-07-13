/*
 * Entry: 0048186d
 * Name: FindGASObject
 * Namespace: Global
 * Signature: _gas_object * FindGASObject(uchar * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl FindGASObject(uchar *param_1)

{
  _gas_object *p_Var1;
  
  for (p_Var1 = firstSound; (p_Var1 != (_gas_object *)0x0 && (p_Var1->wavBuf != param_1));
      p_Var1 = p_Var1->next) {
  }
  return p_Var1;
}
