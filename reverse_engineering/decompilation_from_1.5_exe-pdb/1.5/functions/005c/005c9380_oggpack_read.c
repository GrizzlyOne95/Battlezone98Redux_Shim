/*
 * Entry: 005c9380
 * Name: oggpack_read
 * Namespace: Global
 * Signature: undefined oggpack_read()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_read */

uint __cdecl oggpack_read(int *param_1,uint param_2)

{
  uint uVar1;
  byte *pbVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  
  if (param_2 < 0x21) {
    uVar1 = *(uint *)(&DAT_00623708 + param_2 * 4);
    iVar4 = param_1[1];
    param_2 = param_2 + iVar4;
    if (param_1[4] + -4 <= *param_1) {
      if (param_1[4] - ((int)(param_2 + 7) >> 3) < *param_1) goto LAB_005c9452;
      if (param_2 == 0) {
        return 0;
      }
    }
    pbVar2 = (byte *)param_1[3];
    bVar3 = (byte)iVar4;
    uVar5 = (uint)(*pbVar2 >> (bVar3 & 0x1f));
    if ((((8 < (int)param_2) &&
         (uVar5 = uVar5 | (uint)pbVar2[1] << (8 - bVar3 & 0x1f), 0x10 < (int)param_2)) &&
        (uVar5 = uVar5 | (uint)pbVar2[2] << (0x10 - bVar3 & 0x1f), 0x18 < (int)param_2)) &&
       ((uVar5 = uVar5 | (uint)pbVar2[3] << (0x18 - bVar3 & 0x1f), 0x20 < (int)param_2 &&
        (iVar4 != 0)))) {
      uVar5 = uVar5 | (uint)pbVar2[4] << (0x20 - bVar3 & 0x1f);
    }
    iVar4 = (int)(param_2 + ((int)param_2 >> 0x1f & 7U)) >> 3;
    param_1[3] = (int)(pbVar2 + iVar4);
    *param_1 = iVar4 + *param_1;
    param_1[1] = param_2 & 7;
    return uVar5 & uVar1;
  }
LAB_005c9452:
  param_1[3] = 0;
  *param_1 = param_1[4];
  param_1[1] = 1;
  return 0xffffffff;
}
