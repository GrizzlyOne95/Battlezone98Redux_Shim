
void FUN_005cc2e0(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_4c [12];
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  int local_34;
  undefined8 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
  if (*(int *)(iVar1 + 0x14) == 0x434e5354) {
    puVar2 = (undefined4 *)
             FUN_004e5270(local_4c,*(undefined4 *)
                                    (*(int *)(param_2 + 8) + -8 + *(int *)(param_2 + 4) * 8),
                          *(undefined4 *)(*(int *)(param_2 + 8) + -4 + *(int *)(param_2 + 4) * 8));
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    uVar3 = FUN_00462490();
    FUN_0049cf90(&local_20,uVar3);
  }
  FUN_00477ce0();
  local_40 = param_3;
  local_3c = 8;
  local_38 = 0;
  local_34 = param_2;
  local_28 = 0;
  FUN_004dbaf0(&local_40);
  FUN_0083e885();
  return;
}

