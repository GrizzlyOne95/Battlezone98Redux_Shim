/*
 * Entry: 0050b1e9
 * Name: AIBuild_ResourceListDump
 * Namespace: Global
 * Signature: void AIBuild_ResourceListDump(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ResourceListDump(int param_1)

{
  int iVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  tlog_gdm("Dumping resource %d\n");
  iVar2 = 0;
  iVar1 = AIBuild_ResourceListFind(param_1,0,&local_c,&local_8);
  while (iVar1 != 0) {
    tlog_gdm("   #%d (%d, %d)\n");
    iVar2 = iVar2 + 1;
    iVar1 = AIBuild_ResourceListFind(param_1,iVar2,&local_c,&local_8);
  }
  return;
}
