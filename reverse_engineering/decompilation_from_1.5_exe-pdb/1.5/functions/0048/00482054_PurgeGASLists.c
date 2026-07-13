/*
 * Entry: 00482054
 * Name: PurgeGASLists
 * Namespace: Global
 * Signature: void PurgeGASLists(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PurgeGASLists(void)

{
  _gas_object *p_Var1;
  _gas_object *p_Var2;
  
  if (GM != (GAS_MASTER *)0x0) {
    KillCBQueue(0);
    p_Var2 = firstSound;
    while (p_Var2 != (_gas_object *)0x0) {
      p_Var1 = p_Var2->next;
      DeleteGASObject(p_Var2);
      p_Var2 = p_Var1;
    }
    UsedMemory = 0;
    gasPaused = false;
  }
  return;
}
