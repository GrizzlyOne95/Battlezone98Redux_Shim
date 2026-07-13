/*
 * Entry: 0051f7fa
 * Name: RemoveCoplanarFlags
 * Namespace: Global
 * Signature: void RemoveCoplanarFlags(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RemoveCoplanarFlags(int param_1,int param_2,int param_3,int param_4)

{
  ushort *puVar1;
  int iVar2;
  
  for (; iVar2 = param_2, param_1 <= param_3; param_1 = param_1 + 1) {
    for (; iVar2 <= param_4; iVar2 = iVar2 + 1) {
      puVar1 = GetZonePtr(param_1,iVar2);
      *puVar1 = *puVar1 & 0x3fff;
    }
  }
  return;
}
