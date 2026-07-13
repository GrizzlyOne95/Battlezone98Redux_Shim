/*
 * Entry: 004fb2c1
 * Name: InitGouraudLookupTable
 * Namespace: Global
 * Signature: void InitGouraudLookupTable(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitGouraudLookupTable(void)

{
  int iVar1;
  int local_8;
  
  local_8 = 1;
  do {
    iVar1 = local_8 + 1;
    Gouraud_Lookup[local_8] = 1.0 / (float)local_8;
    local_8 = iVar1;
  } while (iVar1 < 0x280);
  Gouraud_Lookup[0] = 1.0;
  return;
}
