
void FUN_0071f400(int param_1,int param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_94;
  undefined4 local_90;
  int local_8c;
  undefined1 local_84 [112];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085896e;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_94 = *param_3;
  local_90 = param_3[1];
  local_8c = param_2;
  local_14 = uVar1;
  uVar2 = FUN_00417780(param_2 + 0x48,uVar1);
  local_8 = 0;
  FUN_006af160(local_8c + 0x20,&local_94,uVar1,uVar2,local_8c,local_8c);
  FUN_0071fe40(local_8c + 0x48,&local_94,&stack0x00000010);
  local_8._0_1_ = 1;
  uVar2 = FUN_00417780(local_84);
  FUN_0071f550(uVar1,uVar2);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_00725d20(local_84,local_84);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0070ff80();
  local_8 = 0xffffffff;
  FUN_0071d8b0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

