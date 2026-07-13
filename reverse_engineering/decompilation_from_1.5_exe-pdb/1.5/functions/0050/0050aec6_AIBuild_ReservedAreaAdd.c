/*
 * Entry: 0050aec6
 * Name: AIBuild_ReservedAreaAdd
 * Namespace: Global
 * Signature: int AIBuild_ReservedAreaAdd(int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_ReservedAreaAdd(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  iVar1 = 0;
  if (reserved_used[param_1][0] != '\0') {
    do {
      if (0x1f < iVar1) {
        return -1;
      }
      iVar1 = iVar1 + 1;
    } while (reserved_used[param_1][iVar1] != '\0');
    if (0x1f < iVar1) {
      return -1;
    }
  }
  reserved_area[param_1][iVar1].x = (short)param_2;
  reserved_area[param_1][iVar1].y = (short)param_3;
  reserved_area[param_1][iVar1].width = (short)param_4;
  reserved_area[param_1][iVar1].height = (short)param_5;
  reserved_used[param_1][iVar1] = '\x01';
  return iVar1;
}
