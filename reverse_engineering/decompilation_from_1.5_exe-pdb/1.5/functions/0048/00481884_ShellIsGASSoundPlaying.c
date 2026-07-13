/*
 * Entry: 00481884
 * Name: ShellIsGASSoundPlaying
 * Namespace: Global
 * Signature: int ShellIsGASSoundPlaying(uchar * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ShellIsGASSoundPlaying(uchar *param_1)

{
  _gas_object *p_Var1;
  
  for (p_Var1 = firstSound; (p_Var1 != (_gas_object *)0x0 && (p_Var1->wavBuf != param_1));
      p_Var1 = p_Var1->next) {
  }
  return (uint)(p_Var1 != (_gas_object *)0x0);
}
