/*
 * Entry: 00481704
 * Name: UnPauseGAS
 * Namespace: Global
 * Signature: void UnPauseGAS(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnPauseGAS(void)

{
  _gas_object *p_Var1;
  _gas_object *p_Var2;
  
  if (gasPaused) {
    gasPaused = false;
    p_Var2 = firstSound;
    while (p_Var1 = p_Var2, p_Var1 != (_gas_object *)0x0) {
      p_Var2 = p_Var1->next;
      if ((p_Var1->flags & 8) != 0) {
        p_Var1->flags = p_Var1->flags & 0xfffffff7;
      }
    }
  }
  return;
}
