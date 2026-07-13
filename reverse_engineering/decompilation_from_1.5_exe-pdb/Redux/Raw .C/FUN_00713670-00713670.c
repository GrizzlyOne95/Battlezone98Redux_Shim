
void FUN_00713670(int param_1,int param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_94;
  undefined4 local_90;
  int local_88;
  undefined1 local_84 [112];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857dbe;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_94 = *param_3;
  local_90 = param_3[1];
  local_88 = param_2;
  local_14 = uVar1;
  uVar2 = FUN_00417780(param_2 + 0x38,uVar1);
  local_8 = 0;
  if (param_1 != 0) {
    if (*(char *)(local_88 + 0x34) == '\0') {
      local_94 = *(undefined4 *)(local_88 + 0x20);
      local_90 = *(undefined4 *)(local_88 + 0x24);
    }
    else {
      FUN_006aecc0(*(undefined4 *)(local_88 + 0x30),&local_94,uVar1,uVar2,local_88,local_88);
    }
  }
  FUN_006f44e0(local_88 + 0x38,&local_94);
  local_8._0_1_ = 1;
  uVar2 = FUN_00417780(local_84);
  FUN_007137e0(uVar1,uVar2);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_0071b310(local_84,local_84);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006e4520();
  local_8 = 0xffffffff;
  FUN_00712000();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

