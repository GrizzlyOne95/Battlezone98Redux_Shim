/*
 * Entry: 0054a023
 * Name: isDipthong
 * Namespace: Global
 * Signature: int isDipthong(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isDipthong(char *param_1)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if (*param_1 == -0x7d) {
    uVar1 = (uint)(byte)param_1[1];
    if (uVar1 < 0x49) {
      if (uVar1 == 0x48) {
        return 1;
      }
      iVar2 = uVar1 - 0x40;
LAB_0054a046:
      if (iVar2 == 0) {
        return 1;
      }
      if (iVar2 == 2) {
        return 1;
      }
      if (iVar2 == 4) {
        return 1;
      }
      iVar2 = iVar2 + -6;
      goto LAB_0054a088;
    }
    iVar2 = uVar1 - 0x83;
  }
  else {
    if (*param_1 != -0x7e) {
      return 0;
    }
    uVar1 = (uint)(byte)param_1[1];
    if (uVar1 < 0xa8) {
      if (uVar1 == 0xa7) {
        return 1;
      }
      iVar2 = uVar1 - 0x9f;
      goto LAB_0054a046;
    }
    iVar2 = uVar1 - 0xe1;
  }
  if (iVar2 == 0) {
    return 1;
  }
  if (iVar2 == 2) {
    return 1;
  }
  if (iVar2 == 4) {
    return 1;
  }
  iVar2 = iVar2 + -0xb;
LAB_0054a088:
  if (iVar2 == 0) {
    return 1;
  }
  return 0;
}
