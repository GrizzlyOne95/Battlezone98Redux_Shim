
void FUN_00713840(int param_1,int param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_8c;
  undefined4 local_88;
  int local_80;
  undefined1 local_7c [104];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857e0b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8c = *param_3;
  local_88 = param_3[1];
  local_80 = param_2;
  local_14 = uVar1;
  uVar2 = FUN_00417780(param_2 + 0x38,uVar1);
  local_8 = 0;
  if (param_1 != 0) {
    if (*(char *)(local_80 + 0x34) == '\0') {
      local_8c = *(undefined4 *)(local_80 + 0x20);
      local_88 = *(undefined4 *)(local_80 + 0x24);
    }
    else {
      FUN_006aecc0(*(undefined4 *)(local_80 + 0x30),&local_8c,uVar1,uVar2,local_80,local_80);
    }
  }
  FUN_006f4510(local_80 + 0x38,&local_8c);
  local_8._0_1_ = 1;
  uVar2 = FUN_00417780(local_7c);
  FUN_00713990(uVar1,uVar2);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_0071b360(local_7c,local_7c);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006e4540();
  local_8 = 0xffffffff;
  FUN_00712090();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

