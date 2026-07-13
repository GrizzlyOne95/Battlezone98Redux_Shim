/*
 * Entry: 005848da
 * Name: swd_init
 * Namespace: Global
 * Signature: int swd_init(lzo1y_999_swd_t * param_1, uchar * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl swd_init(lzo1y_999_swd_t *param_1,uchar *param_2,ulong param_3)

{
  undefined1 *puVar1;
  lzo1y_999_swd_t *plVar2;
  uint uVar3;
  uint uVar4;
  uint in_EAX;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  uint *unaff_ESI;
  ulong unaff_EDI;
  
  unaff_ESI[7] = 0;
  unaff_ESI[8] = 0;
  puVar5 = unaff_ESI + 0xb;
  iVar7 = 0x22;
  do {
    puVar5[0x24] = 0;
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  unaff_ESI[1] = 0x800;
  unaff_ESI[3] = 0x800;
  unaff_ESI[4] = 0x800;
  unaff_ESI[0x58] = (int)unaff_ESI + 0xc96b;
  *unaff_ESI = 0xbfff;
  unaff_ESI[2] = 1;
  unaff_ESI[5] = 0;
  unaff_ESI[6] = 0;
  unaff_ESI[0x57] = 0xc7ff;
  unaff_ESI[0x59] = 0xbfff;
  memset(unaff_ESI + 0x11c5a,0,0x8000);
  memset(unaff_ESI + 0x13c5a,0xff,0x20000);
  unaff_ESI[0x54] = 0;
  unaff_ESI[0x52] = 0;
  unaff_ESI[0x51] = 0;
  unaff_ESI[0x53] = 0;
  if ((in_EAX != 0) && (param_1 != (lzo1y_999_swd_t *)0x0)) {
    plVar2 = (lzo1y_999_swd_t *)*unaff_ESI;
    if (plVar2 < param_1) {
      in_EAX = (in_EAX - (int)plVar2) + (int)param_1;
      param_1 = plVar2;
    }
    unaff_ESI[0x53] = (uint)param_1;
    unaff_ESI[0x51] = in_EAX;
    unaff_ESI[0x52] = (int)param_1->best_off + (in_EAX - 0x2c);
    memcpy(unaff_ESI + 0x5b,in_EAX,param_1);
    unaff_ESI[0x54] = (uint)param_1;
  }
  uVar3 = unaff_ESI[0x54];
  uVar4 = unaff_ESI[0x2d];
  unaff_ESI[0x55] = uVar3;
  unaff_ESI[0x5a] = uVar3;
  uVar6 = *(int *)(uVar4 + 0x24) - *(int *)(uVar4 + 0x1c);
  unaff_ESI[9] = uVar6;
  if (uVar6 != 0) {
    if (unaff_ESI[1] < uVar6) {
      unaff_ESI[9] = unaff_ESI[1];
    }
    memcpy(uVar3 + 0x16c + (int)unaff_ESI,*(undefined4 *)(uVar4 + 0x1c),unaff_ESI[9]);
    *(int *)(unaff_ESI[0x2d] + 0x1c) = *(int *)(unaff_ESI[0x2d] + 0x1c) + unaff_ESI[9];
    unaff_ESI[0x54] = unaff_ESI[0x54] + unaff_ESI[9];
  }
  if (unaff_ESI[0x54] == unaff_ESI[0x57]) {
    unaff_ESI[0x54] = 0;
  }
  if ((1 < unaff_ESI[9]) && (unaff_ESI[0x53] != 0)) {
    swd_insertdict((lzo1y_999_swd_t *)0x0,unaff_ESI[0x53],unaff_EDI);
  }
  uVar3 = unaff_ESI[0x5a];
  uVar4 = unaff_ESI[0x59];
  unaff_ESI[0x56] = uVar3;
  if (uVar3 < uVar4) {
    unaff_ESI[0x56] = (unaff_ESI[0x57] - uVar4) + uVar3;
  }
  else {
    unaff_ESI[0x56] = uVar3 - uVar4;
  }
  if (unaff_ESI[9] < 3) {
    puVar1 = (undefined1 *)(unaff_ESI[0x55] + unaff_ESI[9] + 0x16c + (int)unaff_ESI);
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = 0;
  }
  return 0;
}
