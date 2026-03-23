
void FUN_00669800(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  int local_70;
  undefined4 local_6c;
  int local_68;
  undefined1 local_64 [8];
  int local_5c;
  undefined4 local_58;
  undefined1 local_54 [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e7a0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>(local_14);
  local_8 = 0;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  Ogre::StringUtil::splitFilename(param_1,local_2c,local_44);
  Ogre::StringUtil::toLowerCase(local_2c);
  uVar2 = FUN_004170c0(0x3a8efa67,local_54);
  uVar2 = FUN_0041f870(uVar2);
  FUN_00662830(uVar2);
  FUN_0066a310(&local_6c);
  FUN_0044ef90(local_74);
  local_68 = -1000;
  local_5c = 0;
  local_58 = local_6c;
  while (cVar1 = FUN_00420f10(local_74), cVar1 != '\0') {
    if ((local_5c == 0) || (piVar3 = (int *)FUN_00421ea0(), local_68 < *piVar3)) {
      puVar6 = local_54;
      puVar5 = local_64;
      FUN_00421ea0(puVar5,puVar6);
      FUN_0066a330(puVar5,puVar6);
      puVar6 = local_78;
      FUN_00421ea0(puVar6);
      uVar2 = FUN_0044ef90(puVar6);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 != '\0') {
        local_5c = FUN_00421ea0();
        local_5c = local_5c + 0x10;
        piVar3 = (int *)FUN_00421ea0();
        local_68 = *piVar3;
        iVar4 = FUN_00421ea0();
        FID_conflict_operator_(iVar4 + 4);
      }
    }
    FUN_00422190();
  }
  local_70 = local_5c;
  local_8 = local_8 & 0xffffff00;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

