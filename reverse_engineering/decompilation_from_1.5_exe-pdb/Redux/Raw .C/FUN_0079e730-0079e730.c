
void FUN_0079e730(void)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  int local_68;
  uint local_60;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085fc78;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar1 = FUN_007cb0a0(local_14);
  FUN_007cb5c0();
  if (iVar1 != -1) {
    piVar2 = (int *)FUN_004200d0(iVar1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(*piVar2 + 0x130));
    local_8 = 0;
    vector<>();
    local_8._0_1_ = 1;
    local_68 = 0;
    while( true ) {
      iVar1 = FUN_004170c0();
      if ((iVar1 == 0) || (0x10 < local_68)) break;
      uVar3 = FUN_0045e1d0(local_44,0,0x20);
      local_8._0_1_ = 2;
      FUN_006cf320(uVar3);
      local_8._0_1_ = 1;
      ~basic_string<>();
      uVar3 = FUN_0045e1d0(local_5c,0x20,0xffffffff);
      FUN_0045e0f0(uVar3);
      ~basic_string<>();
      local_68 = local_68 + 1;
    }
    local_60 = 0;
    while( true ) {
      uVar4 = FUN_0048a830();
      if (uVar4 <= local_60) break;
      uVar5 = 0;
      uVar4 = local_60;
      FUN_006cf480(local_60);
      uVar3 = FUN_0041f870(uVar4,uVar5);
      FUN_007cabf0(uVar3,uVar4,uVar5);
      local_60 = local_60 + 1;
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_0048a040();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

