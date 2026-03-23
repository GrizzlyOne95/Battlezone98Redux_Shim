
void __fastcall FUN_004a7ea0(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 **ppuVar4;
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00849680;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Craft::vftable;
  param_1[6] = Craft::vftable;
  local_8 = 1;
  local_14 = param_1;
  if (param_1[0x3f] != 0) {
    local_1c = (undefined4 *)param_1[0x3f];
    local_18 = local_1c;
    if (local_1c == (undefined4 *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = (**(code **)*local_1c)(1,uVar1);
    }
  }
  local_24 = local_14;
  puVar2 = (undefined4 *)FID_conflict_end(local_30);
  local_28 = *puVar2;
  ppuVar4 = &local_24;
  puVar2 = (undefined4 *)FID_conflict_end(local_34);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_38);
  puVar2 = (undefined4 *)FUN_0046e930(local_3c,*puVar2,uVar3,ppuVar4);
  local_2c = *puVar2;
  FID_conflict_erase(local_40,local_2c,local_28);
  local_8 = local_8 & 0xffffff00;
  _eh_vector_destructor_iterator_(local_14 + 0x8f,4,8,FUN_0044dc30);
  local_8 = 0xffffffff;
  FUN_004dab60();
  ExceptionList = local_10;
  return;
}

