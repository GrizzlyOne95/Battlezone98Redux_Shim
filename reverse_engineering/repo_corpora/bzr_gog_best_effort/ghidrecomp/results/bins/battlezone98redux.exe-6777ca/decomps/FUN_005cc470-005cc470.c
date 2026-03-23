
void FUN_005cc470(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined8 local_50;
  undefined4 local_48;
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
  puStack_c = &LAB_0084c83c;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_3c = FUN_00462630(param_1,local_14);
  if (local_3c != 0) {
    iVar1 = (*(code *)**(undefined4 **)(local_3c + 0x18))();
    if (*(int *)(iVar1 + 0x14) == 0x434e5354) {
      puVar2 = (undefined4 *)FUN_004560b0(local_74,param_2);
      local_38 = *puVar2;
      local_34 = puVar2[1];
      local_30 = puVar2[2];
      puVar2 = (undefined4 *)FUN_00439de0(local_8c,param_2);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      FUN_0049cf90(&local_20,&local_38);
    }
    FUN_00477ce0();
    local_68 = param_3;
    local_64 = 8;
    local_60 = 0;
    local_40 = operator_new(0x18);
    local_8 = 0;
    if (local_40 == (void *)0x0) {
      local_44 = 0;
    }
    else {
      puVar2 = (undefined4 *)FUN_00439de0(local_80,param_2);
      local_2c = *puVar2;
      local_28 = puVar2[1];
      local_24 = puVar2[2];
      puVar2 = &local_2c;
      uVar3 = (**(code **)(*(int *)(local_3c + 0x18) + 0xc))(puVar2);
      local_44 = FUN_00460490(uVar3,puVar2);
    }
    local_48 = local_44;
    local_8 = 0xffffffff;
    local_5c = local_44;
    local_50 = 0;
    FUN_004dbaf0(&local_68);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

