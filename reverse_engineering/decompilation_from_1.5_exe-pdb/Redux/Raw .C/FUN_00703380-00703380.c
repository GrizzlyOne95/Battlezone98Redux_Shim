
void FUN_00703380(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined1 local_ac [8];
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  undefined1 local_9c [8];
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  uint local_84;
  undefined4 local_80;
  int local_7c;
  undefined4 local_78;
  undefined1 local_74 [4];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_70;
  int local_6c;
  byte local_66;
  byte local_65;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_64;
  byte local_5d;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [12];
  undefined1 local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00856ac0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  local_14 = uVar2;
  cVar1 = FUN_006ab7d0(uVar2);
  if ((cVar1 == '\0') || (cVar1 = FUN_006ab7d0(uVar2), cVar1 == '\0')) {
    make_error_code(param_1,6);
    local_8 = local_8 & 0xffffff00;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_007037a5;
  }
  FUN_00421ec0();
  local_7c = FUN_006cc050();
  cVar1 = FUN_006ba0d0(local_7c);
  if (cVar1 != '\0') {
    make_error_code(param_1,7);
    local_8 = local_8 & 0xffffff00;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_007037a5;
  }
  FUN_00421ec0();
  local_70 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_006cc070();
  FUN_00421ec0();
  local_64 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_006cc070();
  if ((local_7c == 1) && (cVar1 = FUN_006bb9a0(local_70), cVar1 == '\0')) {
    make_error_code(param_1,5);
    local_8 = local_8 & 0xffffff00;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_007037a5;
  }
  local_5d = *(char *)(local_6c + 5) == '\0';
  local_84 = (uint)local_5d;
  cVar1 = FUN_0044bb90();
  if (cVar1 == '\0') {
LAB_0070351a:
    local_80 = 0;
  }
  else {
    FUN_00421ec0();
    cVar1 = FUN_00705180();
    if (cVar1 == '\0') goto LAB_0070351a;
    local_80 = 1;
  }
  local_65 = (byte)local_80;
  FUN_00421ec0();
  local_66 = FUN_007051a0();
  if (local_5d == 0) {
    local_78 = 0;
  }
  else {
    local_78 = FUN_00705380();
  }
  if (local_65 == 0) {
    uVar2 = FUN_004170c0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
              (local_64,uVar2);
    if (local_5d == 0) {
      puVar4 = (undefined4 *)FID_conflict_begin(local_a4);
      uVar5 = *puVar4;
      puVar4 = (undefined4 *)
               std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               end(local_70);
      uVar8 = *puVar4;
      puVar4 = (undefined4 *)FID_conflict_begin(local_a0);
      FUN_006da1d0(local_9c,*puVar4,uVar8,uVar5);
    }
    else {
      FUN_00705f70(local_70,local_64,local_78);
    }
  }
  else {
    FUN_00706330(local_ac,local_70,local_64);
    uVar2 = FUN_004170c0();
    if (uVar2 < 4) {
      make_error_code(param_1,1);
      local_8 = local_8 & 0xffffff00;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      FUN_006ca8c0();
      goto LAB_007037a5;
    }
    iVar3 = FUN_004170c0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
              (local_64,iVar3 - 4);
    if (local_5d != 0) {
      FUN_00705f70(local_64,local_64,local_78);
    }
  }
  uVar9 = 0;
  uVar8 = 0;
  uVar6 = (uint)local_65;
  uVar7 = (uint)local_5d;
  uVar2 = (uint)local_66;
  uVar5 = FUN_004170c0(uVar2,uVar7,uVar6,0,0);
  FUN_006ba120(local_7c,uVar5,0,uVar2,uVar7,uVar6,uVar8,uVar9);
  if (local_5d == 0) {
    uVar5 = FUN_004170c0();
    FUN_006ba240(uVar5,0);
    uVar5 = FUN_006ba510(local_5c,local_74,local_2c);
    local_8._0_1_ = 3;
    local_94 = uVar5;
    local_90 = uVar5;
    FUN_00421ec0(uVar5);
    FUN_007051e0(uVar5);
    local_8 = CONCAT31(local_8._1_3_,1);
    ~basic_string<>();
  }
  else {
    uVar5 = local_78;
    uVar8 = FUN_004170c0(local_78);
    FUN_006ba280(uVar8,0,uVar5);
    uVar5 = FUN_006ba510(local_44,local_74,local_20);
    local_8._0_1_ = 2;
    local_8c = uVar5;
    local_88 = uVar5;
    FUN_00421ec0(uVar5);
    FUN_007051e0(uVar5);
    local_8 = CONCAT31(local_8._1_3_,1);
    ~basic_string<>();
  }
  uVar5 = 1;
  FUN_00421ec0(1);
  FUN_00705160(uVar5);
  iVar3 = local_7c;
  FUN_00421ec0(local_7c);
  FUN_007051c0(iVar3);
  FUN_006ab750();
  local_8 = local_8 & 0xffffff00;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
LAB_007037a5:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

