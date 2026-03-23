
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0077e230(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  int local_1c;
  int local_18;
  int local_14;
  ushort local_10;
  int local_c;
  
  fVar8 = DAT_009454b0 / 0.1;
  for (local_c = 0; local_c < 0x10000; local_c = local_c + 1) {
    *(short *)(&DAT_02c119d0 + local_c * 2) = (short)(int)fVar8;
  }
  for (local_c = 0; local_c < 0x1000; local_c = local_c + 1) {
    iVar3 = rand();
    uVar4 = iVar3 >> 8 & 0xf;
    if (uVar4 < 8) {
      if (uVar4 < 4) {
        if (uVar4 < 2) {
          local_10 = 3;
        }
        else {
          local_10 = 2;
        }
      }
      else {
        local_10 = 1;
      }
    }
    else {
      local_10 = 0;
    }
    *(ushort *)(&DAT_02c0f9d0 + local_c * 2) = (ushort)((iVar3 >> 0xc & 7U) << 4) | local_10;
  }
  DAT_02cc5104 = &DAT_02c119d0;
  for (local_c = 0; iVar2 = DAT_02cc40b0, iVar3 = DAT_02cc40ac, local_c < 0x4000;
      local_c = local_c + 1) {
    *(undefined **)(&DAT_02cc5108 + local_c * 4) = &DAT_02c119d0;
    *(undefined **)(&DAT_02cd99a0 + local_c * 4) = &DAT_02c0f9d0;
  }
  iVar6 = DAT_02cc40b0 + _DAT_02cc40a8;
  iVar7 = DAT_02cc40ac + _DAT_02cc40b4;
  local_1c = 0;
  for (local_14 = DAT_02cc40ac; local_14 < iVar7; local_14 = local_14 + 1) {
    for (local_18 = iVar2; local_18 < iVar6; local_18 = local_18 + 1) {
      iVar1 = (local_14 + 0x18) * 0x80 + 0x18 + local_18;
      uVar5 = FUN_00785c00(local_1c);
      *(undefined4 *)(&DAT_02cc5108 + iVar1 * 4) = uVar5;
      uVar5 = FUN_00785c20(local_1c);
      *(undefined4 *)(&DAT_02cd99a0 + iVar1 * 4) = uVar5;
      local_1c = local_1c + 1;
    }
  }
  DAT_02ce99c0 = iVar2 << 8;
  DAT_02ce99a0 = iVar6 * 0x100;
  DAT_02cd9984 = iVar3 << 8;
  DAT_02ce99c4 = iVar7 * 0x100;
  DAT_02cd912c = (float)DAT_02ce99c0 * 5.0;
  DAT_02cd9124 = (float)DAT_02ce99a0 * 5.0;
  DAT_02cd9130 = (float)(iVar3 << 8) * 5.0;
  DAT_02cd9128 = (float)DAT_02ce99c4 * 5.0;
  return;
}

