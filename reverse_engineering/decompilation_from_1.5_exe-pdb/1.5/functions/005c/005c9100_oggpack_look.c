/*
 * Entry: 005c9100
 * Name: oggpack_look
 * Namespace: Global
 * Signature: undefined oggpack_look()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_look */

uint __cdecl oggpack_look(int *param_1,uint param_2)

{
  int iVar1;
  byte *pbVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  
  if (0x20 < param_2) {
    return 0xffffffff;
  }
  iVar1 = param_1[1];
  iVar5 = param_2 + iVar1;
  if (param_1[4] + -4 <= *param_1) {
    if (param_1[4] - (iVar5 + 7 >> 3) < *param_1) {
      return 0xffffffff;
    }
    if (iVar5 == 0) {
      return 0;
    }
  }
  pbVar2 = (byte *)param_1[3];
  uVar4 = (uint)(*pbVar2 >> (*(byte *)(param_1 + 1) & 0x1f));
  if ((((8 < iVar5) &&
       (cVar3 = (char)iVar1, uVar4 = uVar4 | (uint)pbVar2[1] << (8U - cVar3 & 0x1f), 0x10 < iVar5))
      && (uVar4 = uVar4 | (uint)pbVar2[2] << (0x10U - cVar3 & 0x1f), 0x18 < iVar5)) &&
     ((uVar4 = uVar4 | (uint)pbVar2[3] << (0x18U - cVar3 & 0x1f), 0x20 < iVar5 && (iVar1 != 0)))) {
    uVar4 = uVar4 | (uint)pbVar2[4] << (0x20U - cVar3 & 0x1f);
  }
  return uVar4 & *(uint *)(&DAT_00623708 + param_2 * 4);
}
