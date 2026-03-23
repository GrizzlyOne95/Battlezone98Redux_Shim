
void FUN_006b87d0(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 auStack_e4 [160];
  undefined4 local_44;
  undefined4 local_40;
  undefined1 *local_3c;
  undefined1 *local_38;
  uint local_34;
  allocator<char> *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850ef3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  local_14 = uVar1;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xf4) {
    local_3c = (undefined1 *)0x0;
  }
  else {
    local_3c = auStack_e4;
  }
  puVar3 = &DAT_00871530;
  uVar2 = std::allocator<char>::allocator<char>(local_30);
  uVar2 = FUN_00574730(local_3c,local_30 + 0x50,&DAT_0088d764,local_30 + 0x68,&DAT_0088d764,uVar2,
                       puVar3,uVar1);
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_00574730(uVar2);
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_00574730(uVar2);
  FUN_004bc590(uVar2);
  if (&stack0x00000000 == (undefined1 *)0xf4) {
    local_38 = (undefined1 *)0x0;
  }
  else {
    local_38 = auStack_e4;
  }
  local_44 = FUN_006b7fc0(local_2c);
  local_8._0_1_ = 1;
  local_40 = local_44;
  uVar2 = FUN_00574730(local_38,local_44,&DAT_00871530,local_30 + 0x24);
  uVar2 = FUN_004bc590(uVar2);
  FUN_00574730(uVar2);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  GetPolicy(param_1);
  local_34 = local_34 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

