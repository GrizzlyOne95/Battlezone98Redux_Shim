
void FUN_007038c0(undefined1 *param_1,u_short param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  undefined4 *puVar5;
  undefined1 *puStack_60;
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined4 local_48;
  undefined1 local_44 [4];
  undefined1 *local_40;
  undefined1 local_3c [4];
  undefined1 local_38 [8];
  undefined2 local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00856b30;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_60 = (undefined1 *)0x7038fd;
  cVar1 = FUN_006bb9f0();
  if (cVar1 == '\0') {
    puStack_60 = (undefined1 *)0x703936;
    cVar1 = FUN_006bba40();
    if ((cVar1 == '\0') || (param_2 == 0x3ed)) {
      if (param_2 == 0x3ed) {
        iVar2 = FUN_004170c0();
        if (iVar2 != 0) {
          puStack_60 = param_1;
          make_error_code();
          local_8 = 0xffffffff;
          FUN_006ca8c0();
          goto LAB_00703ad9;
        }
      }
      uVar3 = FUN_004170c0();
      if (uVar3 < 0x7c) {
        basic_string<>();
        local_8._0_1_ = 1;
        if (param_2 != 0x3ed) {
          puStack_60 = (undefined1 *)0x703a07;
          local_30 = htons(param_2);
          iVar2 = FUN_004170c0();
          puStack_60 = (undefined1 *)0x703a1f;
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
                    (local_2c,iVar2 + 2);
          puStack_60 = (undefined1 *)0x703a31;
          pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::operator[](local_2c,0);
          *pcVar4 = (char)local_30;
          puStack_60 = (undefined1 *)0x703a49;
          pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::operator[](local_2c,1);
          *pcVar4 = local_30._1_1_;
          puStack_60 = local_4c;
          FID_conflict_begin(local_50);
          FID_conflict_operator_();
          puStack_60 = local_38;
          puVar5 = (undefined4 *)FUN_004fee40();
          puStack_60 = (undefined1 *)*puVar5;
          puVar5 = (undefined4 *)FID_conflict_begin(local_44);
          FUN_006da1d0(local_3c,*puVar5);
        }
        local_40 = (undefined1 *)&puStack_60;
        local_48 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                             ((shared_ptr<class___ExceptionPtr> *)&puStack_60,
                              (shared_ptr<class___ExceptionPtr> *)&stack0x00000010);
        FUN_00705fc0(param_1,8,local_2c);
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_006ca8c0();
      }
      else {
        puStack_60 = param_1;
        make_error_code();
        local_8 = 0xffffffff;
        FUN_006ca8c0();
      }
    }
    else {
      puStack_60 = param_1;
      make_error_code();
      local_8 = 0xffffffff;
      FUN_006ca8c0();
    }
  }
  else {
    puStack_60 = param_1;
    make_error_code();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
LAB_00703ad9:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

