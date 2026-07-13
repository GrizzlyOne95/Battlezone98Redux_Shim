
void FUN_007146b0(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int iVar6;
  undefined1 auStack_12c [160];
  undefined1 local_8c [4];
  undefined1 local_88 [8];
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  int local_6c;
  undefined1 *local_68;
  undefined4 local_64;
  int local_60;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857f33;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_006d08b0(0x400,"initialize_processor");
  cVar1 = FUN_00720f90(local_60 + 0x4abc,uVar2);
  if (cVar1 == '\0') {
    FUN_006ab750();
  }
  else {
    local_6c = FUN_006f91f0(local_60 + 0x4abc);
    if (local_6c < 0) {
      FUN_006d08b0(0x400,"BAD REQUEST: can\'t determine version");
      FUN_006b9910(400);
      make_error_code(param_1,0x1d);
    }
    else {
      local_70 = FUN_006f88c0(local_88,local_6c);
      FID_conflict_operator_(local_70);
      FUN_006ca8c0();
      cVar1 = FUN_006ab7d0();
      if (cVar1 == '\0') {
        FUN_006d08b0(0x400,"BAD REQUEST: no processor for version");
        FUN_006b9910(400);
        FUN_00574400(3,1);
        local_8 = 0;
        basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,1);
        FUN_00423890();
        puVar3 = (undefined4 *)FUN_0041fc00(local_7c);
        local_64 = *puVar3;
        while( true ) {
          uVar4 = FUN_0041fc60(local_80);
          cVar1 = FID_conflict_operator__(uVar4);
          if (cVar1 == '\0') break;
          if (&stack0x00000000 == (undefined1 *)0x13c) {
            local_68 = (undefined1 *)0x0;
          }
          else {
            local_68 = auStack_12c;
          }
          piVar5 = (int *)get();
          iVar6 = *piVar5;
          this = (basic_ostream<char,struct_std::char_traits<char>_> *)
                 FUN_00574730(local_68,local_2c);
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,iVar6);
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=(local_2c,",");
          FUN_00666840(local_8c,0);
        }
        basic_string<>("Sec-WebSocket-Version");
        local_8._0_1_ = 2;
        local_78 = GetPolicy(local_5c);
        local_8._0_1_ = 3;
        local_74 = local_78;
        FUN_006b7810(local_44,local_78);
        local_8._0_1_ = 2;
        ~basic_string<>();
        local_8._0_1_ = 1;
        ~basic_string<>();
        make_error_code(param_1,0x1e);
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      else {
        FUN_006ab750();
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

