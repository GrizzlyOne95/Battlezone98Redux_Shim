
void FUN_006b9760(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  allocator<char> *paVar4;
  undefined *puVar5;
  int iVar6;
  undefined *puVar7;
  undefined1 auStack_e8 [160];
  undefined4 local_48;
  undefined4 local_44;
  undefined1 *local_40;
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
  puStack_c = &LAB_008510c3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  local_14 = uVar1;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xf8) {
    local_38 = (undefined1 *)0x0;
  }
  else {
    local_38 = auStack_e8;
  }
  paVar4 = local_30 + 0x48;
  puVar7 = &DAT_0088d764;
  iVar6 = *(int *)(local_30 + 0x6c);
  puVar5 = &DAT_0088d764;
  uVar2 = std::allocator<char>::allocator<char>(local_30);
  uVar2 = FUN_00574730(local_38,uVar2,puVar5,iVar6,puVar7,paVar4,uVar1);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar6);
  uVar2 = FUN_004bc590(pbVar3);
  FUN_00574730(uVar2);
  if (&stack0x00000000 == (undefined1 *)0xf8) {
    local_3c = (undefined1 *)0x0;
  }
  else {
    local_3c = auStack_e8;
  }
  local_48 = FUN_006b7fc0(local_2c);
  local_8._0_1_ = 1;
  local_44 = local_48;
  uVar2 = FUN_004bc590(local_3c,&DAT_00871530,local_48,&DAT_00871530);
  uVar2 = FUN_00574730(uVar2);
  FUN_004bc590(uVar2);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  if (&stack0x00000000 == (undefined1 *)0xf8) {
    local_40 = (undefined1 *)0x0;
  }
  else {
    local_40 = auStack_e8;
  }
  FUN_00574730(local_40,local_30 + 0x24);
  GetPolicy(param_1);
  local_34 = local_34 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

