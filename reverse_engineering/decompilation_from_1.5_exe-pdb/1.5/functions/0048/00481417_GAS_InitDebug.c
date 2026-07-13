/*
 * Entry: 00481417
 * Name: GAS_InitDebug
 * Namespace: Global
 * Signature: void GAS_InitDebug(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GAS_InitDebug(void)

{
  mHdl = Mono_Register(GAS_Refresh);
  lastMonoLine = 0;
  return;
}
