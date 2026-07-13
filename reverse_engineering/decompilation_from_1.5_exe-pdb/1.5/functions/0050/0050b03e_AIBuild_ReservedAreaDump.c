/*
 * Entry: 0050b03e
 * Name: AIBuild_ReservedAreaDump
 * Namespace: Global
 * Signature: void AIBuild_ReservedAreaDump(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ReservedAreaDump(int param_1)

{
  int iVar1;
  
  tlog_gdm("Dumping Reserved Areas\n");
  iVar1 = 0;
  do {
    if (reserved_used[param_1][iVar1] != '\0') {
      tlog_gdm("   (%d, %d)->(%d, %d)");
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x20);
  return;
}
