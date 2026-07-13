
void FUN_00720180(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  char cVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined4 *puVar3;
  undefined1 auStack_198 [4];
  undefined4 uStack_194;
  undefined1 *puStack_190;
  char *pcStack_188;
  int iVar4;
  undefined1 auStack_16c [160];
  undefined1 local_cc [8];
  char local_c4 [8];
  undefined1 local_bc [8];
  undefined1 local_b4 [24];
  char local_9c [8];
  undefined1 *local_94;
  undefined4 local_90;
  undefined4 local_84;
  undefined1 *local_80;
  undefined1 *local_7c;
  undefined4 local_78;
  code *local_74;
  char *local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 *local_50;
  int *local_4c;
  undefined4 local_48;
  undefined1 *local_44;
  shared_ptr<class___ExceptionPtr> local_3c [11];
  char local_31;
  int local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858b21;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_188 = (char *)0x7201c1;
  cVar2 = FUN_006d4590();
  if (cVar2 != '\0') {
    pcStack_188 = (char *)0x400;
    FUN_006d08b0();
  }
  pcStack_188 = (char *)0x7201f1;
  FUN_006d1110();
  local_8 = 0;
  if (*(int *)(local_30 + 0xa20) != 1) {
    pcStack_188 = (char *)0x3;
    FUN_00574400();
    local_8._0_1_ = 1;
    if (&stack0x00000000 == (undefined1 *)0x17c) {
      local_44 = (undefined1 *)0x0;
    }
    else {
      local_44 = auStack_16c;
    }
    iVar4 = *(int *)(local_30 + 0xa20);
    pcStack_188 = "connection::pong called from invalid state ";
    puStack_190 = (undefined1 *)0x720252;
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    pcStack_188 = (char *)0x72025d;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,iVar4);
    pcStack_188 = (char *)0x72026c;
    local_68 = GetPolicy();
    local_8._0_1_ = 2;
    pcStack_188 = (char *)0x400;
    local_60 = local_68;
    FUN_006d4480();
    local_8._0_1_ = 1;
    ~basic_string<>();
    pcStack_188 = local_c4;
    puVar3 = (undefined4 *)make_error_code();
    uVar1 = puVar3[1];
    *param_2 = *puVar3;
    param_2[1] = uVar1;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
    local_8 = 0xffffffff;
    FUN_006d1140();
    goto LAB_00720507;
  }
  local_8 = 0xffffffff;
  FUN_006d1140();
  pcStack_188 = (char *)0x7202fe;
  FUN_00421ec0();
  pcStack_188 = (char *)0x720305;
  FUN_006e1ae0();
  local_8 = 3;
  cVar2 = FUN_006ab7d0();
  if (cVar2 == '\0') {
    pcStack_188 = local_9c;
    puVar3 = (undefined4 *)make_error_code();
    uVar1 = puVar3[1];
    *param_2 = *puVar3;
    param_2[1] = uVar1;
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_00720507;
  }
  local_4c = (int *)FUN_00421ec0();
  local_7c = (undefined1 *)&pcStack_188;
  puStack_190 = (undefined1 *)0x72036f;
  local_78 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&pcStack_188,local_3c);
  puStack_190 = local_cc;
  uStack_194 = 0x72038a;
  local_50 = (undefined4 *)(**(code **)(*local_4c + 0x50))();
  uVar1 = local_50[1];
  *param_2 = *local_50;
  param_2[1] = uVar1;
  cVar2 = FUN_006ab7d0();
  if (cVar2 != '\0') {
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_00720507;
  }
  local_31 = 0;
  pcStack_188 = (char *)0x7203d6;
  FUN_006d1110();
  local_8 = CONCAT31(local_8._1_3_,4);
  local_80 = (undefined1 *)&pcStack_188;
  puStack_190 = (undefined1 *)0x7203eb;
  local_90 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&pcStack_188,local_3c);
  FUN_006ea380();
  if (*(char *)(local_30 + 0x4ab8) == '\0') {
    cVar2 = FUN_006e1c30();
    if (cVar2 != '\0') goto LAB_00720425;
    local_48 = 1;
  }
  else {
LAB_00720425:
    local_48 = 0;
  }
  local_31 = (char)local_48;
  local_8._0_1_ = 3;
  FUN_006d1140();
  if (local_31 != '\0') {
    local_74 = FUN_006e9190;
    local_70 = (char *)0x0;
    pcStack_188 = (char *)0x720467;
    local_6c = FUN_006e1540();
    local_8._0_1_ = 5;
    pcStack_188 = local_70;
    puStack_190 = local_b4;
    uStack_194 = 0x72048c;
    local_5c = local_6c;
    local_58 = FUN_006eabe0();
    local_8._0_1_ = 6;
    local_94 = auStack_198;
    local_54 = local_58;
    local_84 = FUN_006eac20(local_58);
    FUN_006e1210(local_bc);
    local_8._0_1_ = 5;
    ~<>();
    local_8._0_1_ = 3;
    FUN_006ca8c0();
  }
  puVar3 = (undefined4 *)FUN_006ab750();
  uVar1 = puVar3[1];
  *param_2 = *puVar3;
  param_2[1] = uVar1;
  local_8 = 0xffffffff;
  FUN_006ca8c0();
LAB_00720507:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

