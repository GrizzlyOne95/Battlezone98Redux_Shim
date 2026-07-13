
void FUN_005cc9a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_70 [12];
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  void *local_3c;
  int local_38;
  int local_34;
  int local_30;
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c8ec;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = FUN_00462630(param_1,local_14);
  if (((local_30 != 0) && (local_38 = FUN_004ff060(param_2), local_38 != 0)) &&
     (local_34 = FUN_00460fc0(param_3), local_34 != 0)) {
    iVar1 = (*(code *)**(undefined4 **)(local_30 + 0x18))();
    if (*(int *)(iVar1 + 0x14) == 0x434e5354) {
      puVar2 = (undefined4 *)
               FUN_004e5270(local_70,*(undefined4 *)
                                      (*(int *)(local_34 + 8) + -8 + *(int *)(local_34 + 4) * 8),
                            *(undefined4 *)
                             (*(int *)(local_34 + 8) + -4 + *(int *)(local_34 + 4) * 8));
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      uVar3 = FUN_00462490();
      FUN_0049cf90(&local_20,uVar3);
    }
    FUN_005c8190(local_2c,local_34,0);
    FUN_00477ce0();
    local_64 = param_4;
    local_60 = 0x15;
    local_5c = 0;
    local_3c = operator_new(0x18);
    local_8 = 0;
    if (local_3c == (void *)0x0) {
      local_40 = 0;
    }
    else {
      puVar4 = local_2c;
      uVar3 = (**(code **)(*(int *)(local_30 + 0x18) + 0xc))(puVar4);
      local_40 = FUN_00460490(uVar3,puVar4);
    }
    local_44 = local_40;
    local_8 = 0xffffffff;
    local_58 = local_40;
    local_48 = local_38 >> 0x1f;
    local_4c = local_38;
    FUN_004dbaf0(&local_64);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

