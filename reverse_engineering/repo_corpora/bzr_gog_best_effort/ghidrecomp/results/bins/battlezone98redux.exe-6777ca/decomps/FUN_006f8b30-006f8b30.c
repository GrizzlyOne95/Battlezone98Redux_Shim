
void FUN_006f8b30(void)

{
  char cVar1;
  shared_ptr<class___ExceptionPtr> *psVar2;
  int iVar3;
  uint uVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar5;
  uint uVar6;
  undefined1 auStack_e8 [160];
  undefined4 local_48;
  undefined4 local_44;
  undefined1 *local_40;
  shared_ptr<class___ExceptionPtr> local_3c [8];
  uint local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085590b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  FUN_0068b0a0(local_14);
  local_8 = 0;
  cVar1 = FUN_006e1c30();
  if (cVar1 == '\0') {
    psVar2 = (shared_ptr<class___ExceptionPtr> *)FUN_00700780();
    std::shared_ptr<class___ExceptionPtr>::operator=(local_3c,psVar2);
    FUN_00421ec0();
    FUN_006cc070();
    iVar3 = FUN_004170c0();
    *(int *)(local_30 + 0x4a9c) = *(int *)(local_30 + 0x4a9c) - iVar3;
    FUN_007007a0();
    cVar1 = FUN_006d4590(0x400);
    if (cVar1 != '\0') {
      FUN_00574400(3,1);
      local_8._0_1_ = 1;
      if (&stack0x00000000 == (undefined1 *)0xf8) {
        local_40 = (undefined1 *)0x0;
      }
      else {
        local_40 = auStack_e8;
      }
      uVar6 = *(uint *)(local_30 + 0x4a9c);
      uVar4 = FUN_006f2e50(" buffer size: ");
      pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_40,"write_pop: message count: ");
      pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,uVar4);
      pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar5);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,uVar6);
      local_48 = GetPolicy(local_2c);
      local_8._0_1_ = 2;
      local_44 = local_48;
      FUN_006d4480(0x400,local_48);
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00417f10();
    }
    shared_ptr<>(local_3c);
    local_34 = local_34 | 1;
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else {
    shared_ptr<>(local_3c);
    local_34 = local_34 | 1;
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

