
void __fastcall FUN_004dab60(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 **ppuVar4;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  void *local_44;
  undefined4 local_40;
  int local_3c;
  void *local_38;
  void *local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 *local_20;
  int local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084a0e3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = GameObject::vftable;
  param_1[6] = GameObject::vftable;
  local_8 = 1;
  local_20 = param_1;
  local_14 = param_1;
  puVar2 = (undefined4 *)FID_conflict_end(local_48);
  local_24 = *puVar2;
  ppuVar4 = &local_20;
  puVar2 = (undefined4 *)FID_conflict_end(local_4c);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_50);
  puVar2 = (undefined4 *)FUN_0046e930(local_54,*puVar2,uVar3,ppuVar4,uVar1);
  local_28 = *puVar2;
  FID_conflict_erase(local_58,local_28,local_24);
  FUN_0049f300(0);
  if (local_14[0x5e] != -1) {
    FUN_005e0f50(local_14[0x5e],0);
  }
  if (local_14[0x3f] != 0) {
    local_2c = (undefined4 *)local_14[0x3f];
    local_18 = local_2c;
    if (local_2c == (undefined4 *)0x0) {
      local_30 = 0;
    }
    else {
      local_30 = (**(code **)*local_2c)(1);
    }
  }
  if (local_14[0x61] != 0) {
    local_34 = (void *)local_14[0x61];
    operator_delete__(local_34);
  }
  if (local_14[0x40] != 0) {
    local_38 = (void *)local_14[0x40];
    operator_delete__(local_38);
  }
  if (local_14[0x66] != 0) {
    local_3c = local_14[0x66];
    local_1c = local_3c;
    if (local_3c == 0) {
      local_40 = 0;
    }
    else {
      local_40 = FUN_0049ba10(1);
    }
  }
  if (local_14[0x67] != 0) {
    local_44 = (void *)local_14[0x67];
    operator_delete(local_44);
  }
  if (local_14 == DAT_00917afc) {
    DAT_00917afc = (undefined4 *)0x0;
  }
  if (local_14[0x28] != 0) {
    *(undefined4 *)(local_14[0x28] + 0x300) = 0;
  }
  *(undefined4 *)(local_14[0x3d] + 0x8c) = 0;
  local_8 = local_8 & 0xffffff00;
  FUN_004b79f0();
  local_8 = 0xffffffff;
  FUN_00477440();
  ExceptionList = local_10;
  return;
}

