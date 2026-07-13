
void FUN_006ea380(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  uint uVar5;
  undefined1 auStack_dc [160];
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 *local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00854aab;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_006ab7d0(local_14);
  if (cVar1 == '\0') {
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else {
    FUN_00421ec0();
    FUN_006cc070();
    iVar2 = FUN_004170c0();
    *(int *)(local_30 + 0x4a9c) = iVar2 + *(int *)(local_30 + 0x4a9c);
    FUN_006f2e70(&stack0x00000004);
    cVar1 = FUN_006d4590(0x400);
    if (cVar1 != '\0') {
      FUN_00574400(3,1);
      local_8._0_1_ = 1;
      if (&stack0x00000000 == (undefined1 *)0xec) {
        local_34 = (undefined1 *)0x0;
      }
      else {
        local_34 = auStack_dc;
      }
      uVar5 = *(uint *)(local_30 + 0x4a9c);
      uVar3 = FUN_006f2e50(" buffer size: ");
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_34,"write_push: message count: ");
      pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar3);
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar4);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar5);
      local_3c = GetPolicy(local_2c);
      local_8._0_1_ = 2;
      local_38 = local_3c;
      FUN_006d4480(0x400,local_3c);
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00417f10();
    }
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

