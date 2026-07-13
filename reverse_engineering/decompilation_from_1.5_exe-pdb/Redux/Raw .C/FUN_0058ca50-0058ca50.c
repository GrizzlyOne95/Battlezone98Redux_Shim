
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0058ca50(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  uint *local_50;
  undefined4 local_4c;
  int local_48;
  int local_44;
  uint *local_40;
  int local_3c;
  uint local_38;
  int local_34;
  int local_30;
  int local_2c;
  uint *local_28;
  undefined4 local_24;
  uint *local_20;
  int local_1c;
  int local_18;
  float *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bdcc;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (DAT_0091814c != (uint *)0x0) {
    local_2c = DAT_02a13c70 * DAT_02a13c9c;
    local_34 = (int)DAT_0091814c;
    while( true ) {
      local_44 = local_2c;
      iVar3 = local_2c + -1;
      if (local_2c == 0) break;
      local_30 = local_34 + 4;
      local_2c = iVar3;
      FUN_00422170();
      puVar4 = (undefined4 *)FID_conflict_begin(local_54);
      local_24 = *puVar4;
      while( true ) {
        uVar5 = FID_conflict_end(local_58);
        cVar1 = FID_conflict_operator__(uVar5);
        if (cVar1 == '\0') break;
        puVar4 = (undefined4 *)FUN_00421ec0();
        FUN_0058ca30(*puVar4);
        FUN_00421ee0();
      }
      FUN_0041ff50();
      local_34 = local_34 + 0x118;
    }
    local_48 = (int)DAT_0091814c;
    local_3c = (int)DAT_0091814c;
    if (DAT_0091814c == (uint *)0x0) {
      local_4c = 0;
      local_2c = iVar3;
    }
    else {
      local_2c = iVar3;
      local_4c = FUN_0058cdf0(3);
    }
    DAT_0091819c = DAT_0091819c + DAT_02a13c70 * DAT_02a13c9c * -0x118;
  }
  _DAT_00918148 = FUN_0077d680(uVar2);
  DAT_02a13cac = DAT_02ce99a0 - DAT_02ce99c0;
  DAT_02a13c90 = DAT_02ce99c4 - DAT_02cd9984;
  DAT_02a13c70 = (int)(DAT_02a13cac + 0xf + (DAT_02a13cac + 0xf >> 0x1f & 0xfU)) >> 4;
  DAT_02a13c9c = (int)(DAT_02a13c90 + 0xf + (DAT_02a13c90 + 0xf >> 0x1f & 0xfU)) >> 4;
  DAT_02a13c84 = DAT_02a13c70 + -1;
  DAT_02a13cb8 = DAT_02a13c9c + -1;
  _DAT_02a13cb4 = DAT_02a13c70 * DAT_02a13c9c;
  local_38 = DAT_02a13c70 * DAT_02a13c9c;
  uVar2 = -(uint)((int)((ulonglong)local_38 * 0x118 >> 0x20) != 0) |
          (uint)((ulonglong)local_38 * 0x118);
  local_28 = (uint *)FUN_0083d92c(-(uint)(0xfffffffb < uVar2) | uVar2 + 4);
  local_8 = 0;
  if (local_28 == (uint *)0x0) {
    local_40 = (uint *)0x0;
  }
  else {
    *local_28 = local_38;
    FUN_0083ead2(local_28 + 1,0x118,local_38,FUN_0058ce60,~<>);
    local_40 = local_28 + 1;
  }
  local_50 = local_40;
  local_8 = 0xffffffff;
  DAT_0091814c = local_40;
  DAT_0091819c = DAT_02a13c70 * DAT_02a13c9c * 0x118 + DAT_0091819c;
  local_20 = local_40;
  FUN_004bae50(DAT_02a13c9c * DAT_02a13c70 + 4);
  for (local_1c = 0; local_1c < DAT_02a13c9c; local_1c = local_1c + 1) {
    for (local_18 = 0; local_18 < DAT_02a13c70; local_18 = local_18 + 1) {
      local_14 = (float *)FUN_0058c980(1);
      local_14[4] = 9.80909e-45;
      local_14[6] = -NAN;
      *local_14 = (float)(local_18 * 0x10 + DAT_02ce99c0);
      local_14[2] = *local_14 + 16.0;
      local_14[1] = (float)(local_1c * 0x10 + DAT_02cd9984);
      local_14[3] = local_14[1] + 16.0;
      FUN_0058be60(local_14);
      FUN_0041fe40(&local_14);
      *(undefined1 *)local_20 = 0;
      FUN_00591710(local_1c,local_18);
      local_20 = local_20 + 0x46;
    }
  }
  ExceptionList = local_10;
  return;
}

