/*
 * Entry: 00481131
 * Name: AllocSound
 * Namespace: Global
 * Signature: _gas_object * AllocSound(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl AllocSound(void)

{
  _gas_object *p_Var1;
  
  p_Var1 = malloc(0x84);
  p_Var1->next = firstSound;
  firstSound = p_Var1;
  return p_Var1;
}
