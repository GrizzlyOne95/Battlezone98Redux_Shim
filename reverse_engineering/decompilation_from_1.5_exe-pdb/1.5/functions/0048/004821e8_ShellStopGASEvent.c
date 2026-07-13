/*
 * Entry: 004821e8
 * Name: ShellStopGASEvent
 * Namespace: Global
 * Signature: int ShellStopGASEvent(uchar * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ShellStopGASEvent(uchar *param_1)

{
  _gas_object *p_Var1;
  
  for (p_Var1 = firstSound; (p_Var1 != (_gas_object *)0x0 && (p_Var1->wavBuf != param_1));
      p_Var1 = p_Var1->next) {
  }
  if (p_Var1 == (_gas_object *)0x0) {
    return 0;
  }
  DeleteGASObject(p_Var1);
  return 1;
}
