/*
 * Entry: 0040557b
 * Name: Find
 * Namespace: Global
 * Signature: ushort Find(ushort * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl Find(ushort *param_1,ushort param_2)

{
  ushort *puVar1;
  ushort uVar2;
  
  puVar1 = param_1 + param_2;
  if (*puVar1 != param_2) {
    uVar2 = Find(param_1,*puVar1);
    *puVar1 = uVar2;
  }
  return *puVar1;
}
