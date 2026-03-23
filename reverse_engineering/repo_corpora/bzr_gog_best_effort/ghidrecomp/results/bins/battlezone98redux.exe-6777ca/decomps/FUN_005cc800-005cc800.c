
void FUN_005cc800(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_90 [12];
  undefined1 local_84 [12];
  undefined1 local_78 [12];
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int local_54;
  int local_50;
  undefined4 local_4c;
  int local_48;
  undefined4 local_44;
  void *local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c8ac;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_3c = FUN_00462630(param_1,local_14);
  if ((local_3c != 0) && (local_48 = FUN_004ff060(param_2), local_48 != 0)) {
    iVar1 = (*(code *)**(undefined4 **)(local_3c + 0x18))();
    if (*(int *)(iVar1 + 0x14) == 0x434e5354) {
      puVar2 = (undefined4 *)FUN_004560b0(local_78,param_3);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      puVar2 = (undefined4 *)FUN_00439de0(local_90,param_3);
      local_2c = *puVar2;
      local_28 = puVar2[1];
      local_24 = puVar2[2];
      FUN_0049cf90(&local_2c,&local_20);
    }
    FUN_00477ce0();
    local_6c = param_4;
    local_68 = 0x15;
    local_64 = 0;
    local_40 = operator_new(0x18);
    local_8 = 0;
    if (local_40 == (void *)0x0) {
      local_44 = 0;
    }
    else {
      puVar2 = (undefined4 *)FUN_00439de0(local_84,param_3);
      local_38 = *puVar2;
      local_34 = puVar2[1];
      local_30 = puVar2[2];
      puVar2 = &local_38;
      uVar3 = (**(code **)(*(int *)(local_3c + 0x18) + 0xc))(puVar2);
      local_44 = FUN_00460490(uVar3,puVar2);
    }
    local_4c = local_44;
    local_8 = 0xffffffff;
    local_60 = local_44;
    local_50 = local_48 >> 0x1f;
    local_54 = local_48;
    FUN_004dbaf0(&local_6c);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

