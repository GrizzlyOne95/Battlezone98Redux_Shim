
void FUN_007472d0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  undefined4 *puVar5;
  code *pcVar6;
  undefined1 auStack_120 [160];
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined4 local_78;
  undefined1 local_74 [4];
  undefined4 local_70;
  undefined4 local_6c;
  undefined1 *local_68;
  undefined1 *local_64;
  undefined1 *local_60;
  undefined1 *local_5c;
  undefined1 *local_58;
  int local_54;
  undefined1 *local_50;
  undefined1 *local_4c;
  undefined1 *local_48;
  undefined1 *local_44;
  undefined1 local_40 [8];
  int local_38;
  undefined4 local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b8a3;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0x130) {
    local_4c = (undefined1 *)0x0;
  }
  else {
    local_4c = auStack_120;
  }
  FUN_004bc590(local_4c,"**********  Lobby Data  **************\n",uVar2);
  if (&stack0x00000000 == (undefined1 *)0x130) {
    local_5c = (undefined1 *)0x0;
  }
  else {
    local_5c = auStack_120;
  }
  pcVar6 = FUN_004bc8c0;
  uVar3 = FUN_0041f870();
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(local_5c,uVar3);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
  puVar5 = (undefined4 *)FUN_0042d8c0(local_7c);
  local_34 = *puVar5;
  puVar5 = (undefined4 *)FID_conflict_begin(local_80);
  local_6c = *puVar5;
  cVar1 = FUN_00420f10(&local_6c);
  if (cVar1 != '\0') {
    local_30 = FUN_00422e80();
    if (&stack0x00000000 == (undefined1 *)0x130) {
      local_60 = (undefined1 *)0x0;
    }
    else {
      local_60 = auStack_120;
    }
    uVar3 = FUN_004bc590(local_60,"Lobby: ",local_30 + 0x10);
    FUN_0073ba70(uVar3);
    if (&stack0x00000000 == (undefined1 *)0x130) {
      local_68 = (undefined1 *)0x0;
    }
    else {
      local_68 = auStack_120;
    }
    pcVar6 = FUN_004bc8c0;
    uVar3 = FUN_0041f870();
    uVar3 = FUN_004bc590(local_68,"  :  ",uVar3);
    pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar3);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
    FUN_00438c40(local_40);
    FID_conflict_begin(local_74);
    cVar1 = FUN_00420f10(local_74);
    if (cVar1 != '\0') {
      local_54 = FUN_00422e80();
      if (&stack0x00000000 == (undefined1 *)0x130) {
        local_64 = (undefined1 *)0x0;
      }
      else {
        local_64 = auStack_120;
      }
      pcVar6 = FUN_004bc8c0;
      uVar3 = FUN_004bc590(local_64,"   User: ",local_54 + 8,&DAT_0089a17c,local_54 + 0x2c);
      uVar3 = FUN_0073ba70(uVar3);
      uVar3 = FUN_004bc590(uVar3);
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar3);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  if (&stack0x00000000 == (undefined1 *)0x130) {
    local_44 = (undefined1 *)0x0;
  }
  else {
    local_44 = auStack_120;
  }
  FUN_004bc590(local_44,"Current Lobby : ");
  local_38 = FUN_0056f900();
  if (local_38 == 0) {
    if (&stack0x00000000 == (undefined1 *)0x130) {
      local_50 = (undefined1 *)0x0;
    }
    else {
      local_50 = auStack_120;
    }
    FUN_004bc590(local_50,"NULL\n");
  }
  else {
    if (&stack0x00000000 == (undefined1 *)0x130) {
      local_58 = (undefined1 *)0x0;
    }
    else {
      local_58 = auStack_120;
    }
    pcVar6 = FUN_004bc8c0;
    uVar3 = FUN_0073ba70(local_58,local_38 + 0x10,"  :  ",local_38 + 0x68);
    uVar3 = FUN_004bc590(uVar3);
    pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar3);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
  }
  if (&stack0x00000000 == (undefined1 *)0x130) {
    local_48 = (undefined1 *)0x0;
  }
  else {
    local_48 = auStack_120;
  }
  FUN_004bc590(local_48,"**************************************\n");
  local_78 = GetPolicy(local_2c);
  local_8._0_1_ = 1;
  local_70 = local_78;
  uVar3 = FUN_0041f870();
  FUN_007d6a70(uVar3);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

