/*
 * Entry: 0050aeae
 * Name: AIBuild_ReservedAreaNew
 * Namespace: Global
 * Signature: void AIBuild_ReservedAreaNew(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ReservedAreaNew(int param_1)

{
  int iVar1;
  uchar *puVar2;
  
  iVar1 = 8;
  puVar2 = reserved_used[param_1];
  for (; iVar1 != 0; iVar1 = iVar1 + -1) {
    puVar2[0] = '\0';
    puVar2[1] = '\0';
    puVar2[2] = '\0';
    puVar2[3] = '\0';
    puVar2 = puVar2 + 4;
  }
  return;
}
