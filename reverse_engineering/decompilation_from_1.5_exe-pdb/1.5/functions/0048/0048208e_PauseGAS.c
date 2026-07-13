/*
 * Entry: 0048208e
 * Name: PauseGAS
 * Namespace: Global
 * Signature: void PauseGAS(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PauseGAS(void)

{
  _gas_object *p_Var1;
  _gas_object *p_Var2;
  
  if (!gasPaused) {
    gasPaused = true;
    p_Var2 = firstSound;
    while (p_Var2 != (_gas_object *)0x0) {
      p_Var1 = p_Var2->next;
      StopGASObject(p_Var2);
      if (((p_Var2->gc).flags & 1) == 0) {
        DeleteGASObject(p_Var2);
        p_Var2 = p_Var1;
      }
      else {
        p_Var2->flags = p_Var2->flags | 8;
        p_Var2 = p_Var1;
      }
    }
  }
  return;
}
