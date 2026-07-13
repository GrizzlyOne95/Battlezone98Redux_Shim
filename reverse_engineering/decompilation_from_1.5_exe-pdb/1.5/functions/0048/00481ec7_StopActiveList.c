/*
 * Entry: 00481ec7
 * Name: StopActiveList
 * Namespace: Global
 * Signature: void StopActiveList(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StopActiveList(void)

{
  _gas_object *p_Var1;
  
  for (p_Var1 = firstSound; p_Var1 != (_gas_object *)0x0; p_Var1 = p_Var1->next) {
    if ((p_Var1->flags & 4) != 0) {
      StopGASObject(p_Var1);
    }
  }
  return;
}
