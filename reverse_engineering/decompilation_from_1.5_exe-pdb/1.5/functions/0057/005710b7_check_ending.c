/*
 * Entry: 005710b7
 * Name: check_ending
 * Namespace: Global
 * Signature: int check_ending(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl check_ending(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar1 = GetRunning();
  iVar2 = CheckPlayerSide();
  if (param_1 != iVar2) {
    return 0;
  }
  iVar3 = CheckMissionIndex();
  if (param_2 == 0) {
    if (-1 < iVar3) {
      bVar4 = iVar1 == 1;
      goto LAB_005710f5;
    }
  }
  else if (-1 < iVar3) {
    bVar4 = nMissionStatus == 2;
LAB_005710f5:
    if (bVar4) {
      iVar3 = iVar3 + 1;
    }
    goto LAB_005710f8;
  }
  iVar3 = 0;
LAB_005710f8:
  if (iVar2 == 1) {
    if (iVar3 == 0x11) {
      return 1;
    }
  }
  else {
    if (iVar2 == 2) {
      bVar4 = iVar3 == 8;
    }
    else {
      if (iVar2 != 3) {
        return 0;
      }
      bVar4 = iVar3 == 4;
    }
    if (bVar4) {
      return 1;
    }
  }
  return 0;
}
