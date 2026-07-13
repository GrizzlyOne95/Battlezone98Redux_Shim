
void FUN_00705fc0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 local_94 [4];
  undefined1 local_90 [4];
  undefined1 local_8c [4];
  undefined1 local_88 [4];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  uint local_70;
  int local_6c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_68;
  undefined1 local_64 [7];
  char local_5d;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [12];
  undefined1 local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00856ed8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_006ab7d0(local_14);
  if (cVar1 == '\0') {
    make_error_code(param_1,6);
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else {
    cVar1 = FUN_006ba0d0(param_2);
    if (cVar1 == '\0') {
      make_error_code(param_1,7);
      local_8 = 0xffffffff;
      FUN_006ca8c0();
    }
    else {
      uVar2 = FUN_004170c0();
      if (uVar2 < 0x7e) {
        local_5d = *(char *)(local_6c + 5) == '\0';
        local_70 = (uint)(byte)local_5d;
        uVar8 = 0;
        uVar7 = 0;
        uVar6 = 0;
        uVar5 = 1;
        uVar2 = local_70;
        uVar3 = FUN_004170c0(1,local_70,0,0,0);
        FUN_006ba120(param_2,uVar3,0,uVar5,uVar2,uVar6,uVar7,uVar8);
        FUN_00421ec0();
        local_68 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   FUN_006cc070();
        uVar2 = FUN_004170c0();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
                  (local_68,uVar2);
        if (local_5d == '\0') {
          uVar3 = FUN_004170c0();
          FUN_006ba240(uVar3,0);
          uVar3 = FUN_006ba510(local_5c,local_64,local_2c);
          local_8._0_1_ = 2;
          local_80 = uVar3;
          local_78 = uVar3;
          FUN_00421ec0(uVar3);
          FUN_007051e0(uVar3);
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          puVar4 = (undefined4 *)FID_conflict_begin(local_94);
          uVar3 = *puVar4;
          puVar4 = (undefined4 *)FUN_004fee40(local_88);
          uVar5 = *puVar4;
          puVar4 = (undefined4 *)FID_conflict_begin(local_8c);
          FUN_006da1d0(local_90,*puVar4,uVar5,uVar3);
        }
        else {
          uVar3 = FUN_00705380();
          local_74 = uVar3;
          uVar5 = FUN_004170c0(uVar3);
          FUN_006ba280(uVar5,0,uVar3);
          uVar3 = FUN_006ba510(local_44,local_64,local_20);
          local_8._0_1_ = 1;
          local_84 = uVar3;
          local_7c = uVar3;
          FUN_00421ec0(uVar3);
          FUN_007051e0(uVar3);
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          FUN_00705f70(param_3,local_68,local_74);
        }
        FUN_00421ec0(param_2);
        FUN_007051c0(param_2);
        uVar3 = 1;
        FUN_00421ec0(1);
        FUN_00705160(uVar3);
        FUN_006ab750();
        local_8 = 0xffffffff;
        FUN_006ca8c0();
      }
      else {
        make_error_code(param_1,8);
        local_8 = 0xffffffff;
        FUN_006ca8c0();
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

