/*
 * Entry: 004b2c4d
 * Name: Texture_Cleanup
 * Namespace: Global
 * Signature: void Texture_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Texture_Cleanup(void)

{
  int iVar1;
  
  for (iVar1 = tcacheUsed; -1 < iVar1; iVar1 = tcache[iVar1].next) {
    operator_delete__(tcache[iVar1].texture_array);
    tcache[iVar1].texture_array = (char *)0x0;
  }
  TexCache_Cleanup();
  return;
}
