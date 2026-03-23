
void FUN_00590eb0(float param_1,float param_2,float param_3,float param_4,uint *param_5,
                 undefined4 *param_6)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  void *local_50;
  void *local_4c;
  void *local_48;
  int local_44;
  undefined4 local_40;
  uint local_3c;
  void *local_38;
  char *local_34;
  char *local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bf4b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_5 = 0;
  *param_6 = DAT_00918170;
  param_1 = param_1 * DAT_02cc50e4;
  param_2 = param_2 * DAT_02cc50e4;
  param_3 = param_3 * DAT_02cc50e4;
  param_4 = param_4 * DAT_02cc50e4;
  FUN_0058c8f0(uVar2);
  local_8 = 0;
  local_90 = param_1;
  local_8c = param_2;
  local_88 = param_3;
  local_84 = param_4;
  iVar3 = FUN_0058be00(param_2);
  local_1c = (int)((iVar3 - DAT_02cd9984) + (iVar3 - DAT_02cd9984 >> 0x1f & 0xfU)) >> 4;
  iVar3 = FUN_0058be00(param_4);
  iVar3 = (iVar3 - DAT_02cd9984) + 0xf;
  local_20 = (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4;
  iVar3 = FUN_0058be00(param_1);
  local_24 = (int)((iVar3 - DAT_02ce99c0) + (iVar3 - DAT_02ce99c0 >> 0x1f & 0xfU)) >> 4;
  iVar3 = FUN_0058be00(param_3);
  iVar3 = (iVar3 - DAT_02ce99c0) + 0xf;
  local_28 = (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4;
  if ((local_20 < 0) || (local_28 < 0)) {
    local_8 = 0xffffffff;
    FUN_0058c910();
  }
  else if ((local_1c < DAT_02a13c9c) && (local_24 < DAT_02a13c70)) {
    if (DAT_0091814c == 0) {
      local_8 = 0xffffffff;
      FUN_0058c910();
    }
    else {
      if (local_1c < 0) {
        local_1c = 0;
      }
      if (local_24 < 0) {
        local_24 = 0;
      }
      if (DAT_02a13c9c < local_20) {
        local_20 = DAT_02a13c9c;
      }
      if (DAT_02a13c70 < local_28) {
        local_28 = DAT_02a13c70;
      }
      for (local_18 = local_1c; local_18 < local_20; local_18 = local_18 + 1) {
        for (local_14 = local_24; local_14 < local_28; local_14 = local_14 + 1) {
          iVar3 = FUN_00453d10(local_18,0,DAT_02a13cb8);
          iVar3 = iVar3 * DAT_02a13c70;
          local_44 = FUN_00453d10(local_14,0,DAT_02a13c84);
          local_44 = iVar3 + local_44;
          local_30 = (char *)(local_44 * 0x118 + DAT_0091814c);
          if (*local_30 == '\0') {
            FUN_00591710(local_18,local_14);
          }
          local_34 = local_30 + 4;
          FUN_00422170();
          puVar4 = (undefined4 *)FID_conflict_begin(local_54);
          local_2c = *puVar4;
          while( true ) {
            uVar5 = FID_conflict_end(local_58);
            cVar1 = FID_conflict_operator__(uVar5);
            if (cVar1 == '\0') break;
            puVar4 = (undefined4 *)FUN_00421ec0();
            local_40 = *puVar4;
            cVar1 = FUN_0058cea0(local_40,&local_90);
            if (cVar1 != '\0') {
              if (*param_5 == DAT_00918198) {
                if (DAT_00918198 == 0) {
                  DAT_00918170 = (void *)FUN_0083d92c(0x80);
                  DAT_00918198 = 0x20;
                  local_48 = DAT_00918170;
                }
                else {
                  local_3c = DAT_00918198 << 1;
                  local_4c = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)local_3c * 4 >> 0x20) !=
                                                         0) | (uint)((ulonglong)local_3c * 4));
                  local_38 = local_4c;
                  memcpy(local_4c,DAT_00918170,DAT_00918198 << 2);
                  local_50 = DAT_00918170;
                  operator_delete__(DAT_00918170);
                  DAT_00918170 = local_38;
                  DAT_00918198 = local_3c;
                }
              }
              *(undefined4 *)((int)DAT_00918170 + *param_5 * 4) = local_40;
              *param_5 = *param_5 + 1;
            }
            FUN_00421ee0();
          }
        }
      }
      *param_6 = DAT_00918170;
      local_8 = 0xffffffff;
      FUN_0058c910();
    }
  }
  else {
    local_8 = 0xffffffff;
    FUN_0058c910();
  }
  ExceptionList = local_10;
  return;
}

