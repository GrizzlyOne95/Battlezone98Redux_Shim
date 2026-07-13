/*
 * Entry: 005c8220
 * Name: FUN_005c8220
 * Namespace: Global
 * Signature: undefined FUN_005c8220()
 * Symbol source: DEFAULT
 * Export status: ok
 */

undefined4 FUN_005c8220(int *param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined1 uVar3;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  undefined1 extraout_AL_01;
  undefined1 extraout_AL_02;
  undefined1 extraout_AL_03;
  undefined1 extraout_AL_04;
  undefined1 extraout_AL_05;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int *unaff_ESI;
  int iVar10;
  int local_c;
  int local_4;
  
  local_4 = unaff_ESI[7];
  if (0xff < local_4) {
    local_4 = 0xff;
  }
  iVar7 = 0;
  uVar4 = 0xffffffff;
  uVar3 = 0xff;
  local_c = 0;
  if ((*unaff_ESI == 0) || (local_4 == 0)) {
    return 0;
  }
  iVar9 = 0;
  if (unaff_ESI[0x53] == 0) {
    uVar3 = 0;
    if (0 < local_4) {
      puVar8 = (uint *)unaff_ESI[4];
      do {
        iVar9 = iVar9 + 1;
        if ((*puVar8 & 0xff) < 0xff) break;
        puVar8 = puVar8 + 1;
      } while (iVar9 < local_4);
    }
  }
  else {
    iVar5 = 0;
    if (0 < local_4) {
      do {
        uVar3 = (undefined1)uVar4;
        if ((param_3 < local_c) && (3 < iVar5)) {
          param_2 = 1;
          break;
        }
        uVar6 = *(uint *)(unaff_ESI[4] + iVar9 * 4) & 0xff;
        local_c = local_c + uVar6;
        if (uVar6 < 0xff) {
          uVar4 = *(undefined4 *)(unaff_ESI[5] + iVar9 * 8);
          iVar7 = iVar7 + 1;
          iVar5 = iVar7;
        }
        else {
          iVar5 = 0;
        }
        uVar3 = (undefined1)uVar4;
        iVar9 = iVar9 + 1;
      } while (iVar9 < local_4);
      if (iVar9 == 0xff) goto LAB_005c82f5;
    }
  }
  if (param_2 == 0) {
    return 0;
  }
LAB_005c82f5:
  unaff_ESI[10] = 0x5367674f;
  *(undefined1 *)(unaff_ESI + 0xb) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x2d) = 0;
  if ((*(uint *)unaff_ESI[4] & 0x100) == 0) {
    *(undefined1 *)((int)unaff_ESI + 0x2d) = 1;
  }
  iVar7 = 0;
  if (unaff_ESI[0x53] == 0) {
    *(byte *)((int)unaff_ESI + 0x2d) = *(byte *)((int)unaff_ESI + 0x2d) | 2;
  }
  if ((unaff_ESI[0x52] != 0) && (unaff_ESI[7] == iVar9)) {
    *(byte *)((int)unaff_ESI + 0x2d) = *(byte *)((int)unaff_ESI + 0x2d) | 4;
  }
  unaff_ESI[0x53] = 1;
  *(undefined1 *)((int)unaff_ESI + 0x2e) = uVar3;
  _allshr();
  *(undefined1 *)((int)unaff_ESI + 0x2f) = extraout_AL;
  _allshr();
  *(undefined1 *)(unaff_ESI + 0xc) = extraout_AL_00;
  _allshr();
  *(undefined1 *)((int)unaff_ESI + 0x31) = extraout_AL_01;
  _allshr();
  *(undefined1 *)((int)unaff_ESI + 0x32) = extraout_AL_02;
  _allshr();
  *(undefined1 *)((int)unaff_ESI + 0x33) = extraout_AL_03;
  _allshr();
  *(undefined1 *)(unaff_ESI + 0xd) = extraout_AL_04;
  _allshr();
  *(undefined1 *)((int)unaff_ESI + 0x35) = extraout_AL_05;
  iVar5 = unaff_ESI[0x54];
  *(char *)((int)unaff_ESI + 0x36) = (char)iVar5;
  *(char *)((int)unaff_ESI + 0x37) = (char)((uint)iVar5 >> 8);
  *(char *)(unaff_ESI + 0xe) = (char)((uint)iVar5 >> 0x10);
  *(char *)((int)unaff_ESI + 0x39) = (char)((uint)iVar5 >> 0x18);
  if (unaff_ESI[0x55] == -1) {
    unaff_ESI[0x55] = 0;
  }
  iVar5 = unaff_ESI[0x55];
  unaff_ESI[0x55] = iVar5 + 1;
  *(char *)((int)unaff_ESI + 0x3a) = (char)iVar5;
  *(char *)((int)unaff_ESI + 0x3b) = (char)((uint)iVar5 >> 8);
  *(char *)(unaff_ESI + 0xf) = (char)((uint)iVar5 >> 0x10);
  *(char *)((int)unaff_ESI + 0x3d) = (char)((uint)iVar5 >> 0x18);
  iVar10 = 0;
  iVar5 = 0;
  *(undefined1 *)((int)unaff_ESI + 0x3e) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x3f) = 0;
  *(undefined1 *)(unaff_ESI + 0x10) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x41) = 0;
  *(char *)((int)unaff_ESI + 0x42) = (char)iVar9;
  if (1 < iVar9) {
    do {
      bVar1 = *(byte *)(unaff_ESI[4] + iVar5 * 4);
      *(byte *)((int)unaff_ESI + iVar5 + 0x43) = bVar1;
      iVar10 = iVar10 + (uint)bVar1;
      bVar1 = *(byte *)(unaff_ESI[4] + 4 + iVar5 * 4);
      *(byte *)((int)unaff_ESI + iVar5 + 0x44) = bVar1;
      iVar5 = iVar5 + 2;
      iVar7 = iVar7 + (uint)bVar1;
    } while (iVar5 < iVar9 + -1);
  }
  if (iVar5 < iVar9) {
    bVar1 = *(byte *)(unaff_ESI[4] + iVar5 * 4);
    *(byte *)(iVar5 + 0x43 + (int)unaff_ESI) = bVar1;
    uVar6 = (uint)bVar1;
  }
  else {
    uVar6 = 0;
  }
  *param_1 = (int)(unaff_ESI + 10);
  unaff_ESI[0x51] = iVar9 + 0x1b;
  param_1[1] = iVar9 + 0x1b;
  iVar5 = unaff_ESI[3];
  iVar2 = *unaff_ESI;
  iVar7 = uVar6 + iVar7 + iVar10;
  param_1[3] = iVar7;
  param_1[2] = iVar5 + iVar2;
  unaff_ESI[7] = unaff_ESI[7] - iVar9;
  memmove((void *)unaff_ESI[4],(void *)(unaff_ESI[4] + iVar9 * 4),unaff_ESI[7] * 4);
  memmove((void *)unaff_ESI[5],(void *)(unaff_ESI[5] + iVar9 * 8),unaff_ESI[7] * 8);
  unaff_ESI[3] = unaff_ESI[3] + iVar7;
  ogg_page_checksum_set(param_1);
  return 1;
}
