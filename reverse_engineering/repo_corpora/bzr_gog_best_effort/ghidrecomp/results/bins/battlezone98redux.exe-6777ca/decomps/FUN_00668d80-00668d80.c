
void FUN_00668d80(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar8;
  undefined1 *puVar9;
  __ExceptionPtr *p_Var10;
  undefined1 local_cc [4];
  undefined1 local_c8 [4];
  undefined1 local_c4 [4];
  undefined1 local_c0 [4];
  undefined1 local_bc [4];
  undefined1 local_b8 [4];
  undefined1 local_b4 [4];
  undefined1 local_b0 [4];
  undefined1 local_ac [4];
  undefined1 local_a8 [4];
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  undefined1 local_9c [4];
  undefined1 local_98 [32];
  undefined4 local_78;
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined4 local_6c;
  undefined4 local_68;
  uint local_64;
  undefined1 local_60 [4];
  undefined1 local_5c [15];
  byte local_4d;
  int local_4c;
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  uint local_40;
  char local_35;
  undefined1 local_34 [7];
  char local_2d;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e676;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  basic_string<>(&DAT_008922f0);
  local_8 = 0;
  local_35 = Ogre::StringUtil::startsWith(param_1,local_2c,true);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar3);
  if (local_35 == '\0') {
    local_4c = FUN_00669800(param_1);
    if (local_4c != 0) {
      if (param_4 == 0) {
        FUN_00669fe0(local_4c);
      }
      else {
        FUN_00669cc0(local_4c + 0x34);
      }
    }
  }
  else {
    iVar4 = FUN_004170c0();
    local_2d = iVar4 == 1;
    local_64 = (uint)(byte)local_2d;
    if (param_4 == 0) {
      FUN_0066b0b0();
      local_8 = 1;
      FUN_0066a310(local_5c);
      while( true ) {
        uVar5 = FUN_0044ef90(local_a8);
        cVar1 = FUN_00420f10(uVar5);
        if (cVar1 == '\0') break;
        uVar5 = FUN_00421ea0();
        FUN_0066b190(uVar5);
        FUN_00422190();
      }
      uVar3 = (uint)local_4d;
      puVar6 = (undefined4 *)FID_conflict_end(local_c8);
      uVar5 = *puVar6;
      puVar6 = (undefined4 *)FID_conflict_begin(local_b0);
      FUN_0066e9d0(*puVar6,uVar5,uVar3);
      FUN_0066b2b0();
      local_8._0_1_ = 2;
      local_40 = 0;
      while (uVar3 = FUN_0066b150(), local_40 < uVar3) {
        uVar5 = FUN_0066b170(local_40);
        FUN_0066acd0(local_c0,uVar5);
        iVar4 = FUN_00422150();
        FUN_0066a180(iVar4 + 0x1c);
        local_8 = CONCAT31(local_8._1_3_,3);
        FUN_0044ef90(local_74);
        FUN_0066a310(local_34);
        while (cVar1 = FUN_00420f10(local_74), cVar1 != '\0') {
          if (local_2d == '\0') {
            bVar2 = true;
            pbVar8 = param_1;
            iVar4 = FUN_00421ea0();
            bVar2 = Ogre::StringUtil::match
                              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(iVar4 + 0x44),pbVar8,bVar2);
            if (bVar2) goto LAB_006690f4;
          }
          else {
LAB_006690f4:
            if (local_40 != 0) {
              uVar5 = FUN_0044ef90(local_9c);
              iVar4 = FUN_00421ea0(uVar5);
              FUN_00420350(local_a4,iVar4 + 0x44);
              cVar1 = FUN_004221b0(uVar5);
              if (cVar1 != '\0') {
                iVar4 = FUN_00421ea0();
                iVar4 = iVar4 + 0x10;
                iVar7 = FUN_00421ea0(iVar4);
                FUN_0066b2e0(iVar7 + 0x44);
                FUN_00667dd0(iVar4);
                goto LAB_006690a7;
              }
            }
            iVar4 = FUN_00421ea0();
            iVar4 = iVar4 + 0x10;
            iVar7 = FUN_00421ea0(iVar4);
            FUN_0066b2e0(iVar7 + 0x44);
            FUN_00667dd0(iVar4);
          }
LAB_006690a7:
          FUN_00422190();
        }
        local_8._0_1_ = 2;
        FUN_00667cd0();
        local_40 = local_40 + 1;
      }
      FUN_0066a310(local_60);
      while( true ) {
        uVar5 = FUN_0044ef90(local_ac);
        cVar1 = FUN_00420f10(uVar5);
        if (cVar1 == '\0') break;
        iVar4 = FUN_00421ea0();
        FUN_00669fe0(iVar4 + 0x18);
        FUN_00422190();
      }
      local_8 = CONCAT31(local_8._1_3_,1);
      FUN_00669290();
      local_8 = 0xffffffff;
      FUN_0066b130();
    }
    else {
      FUN_0066a310(local_48);
      while( true ) {
        uVar5 = FUN_0044ef90(local_98);
        cVar1 = FUN_00420f10(uVar5);
        if (cVar1 == '\0') break;
        puVar9 = local_70;
        FUN_00421ea0(puVar9);
        FUN_0044ef90(puVar9);
        puVar9 = local_44;
        FUN_00421ea0(puVar9);
        FUN_0066a310(puVar9);
        while (cVar1 = FUN_00420f10(local_70), cVar1 != '\0') {
          if (local_2d == '\0') {
            bVar2 = true;
            pbVar8 = param_1;
            iVar4 = FUN_00421ea0();
            bVar2 = Ogre::StringUtil::match
                              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(iVar4 + 0x44),pbVar8,bVar2);
            if (bVar2) goto LAB_00668ed2;
          }
          else {
LAB_00668ed2:
            iVar4 = FUN_00421ea0();
            FUN_00669cc0(iVar4 + 0x44);
          }
          FUN_00422190();
        }
        FUN_00422190();
      }
      puVar6 = (undefined4 *)FID_conflict_end(local_b4);
      p_Var10 = (__ExceptionPtr *)*puVar6;
      puVar6 = (undefined4 *)FID_conflict_begin(local_bc);
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                ((shared_ptr<class___ExceptionPtr> *)*puVar6,p_Var10);
      puVar6 = (undefined4 *)FID_conflict_end(local_c4);
      uVar5 = *puVar6;
      puVar6 = (undefined4 *)FID_conflict_begin(local_cc);
      FUN_0066e9a0(&local_6c,*puVar6,uVar5);
      puVar6 = (undefined4 *)FID_conflict_end(local_a0);
      local_68 = *puVar6;
      local_78 = local_6c;
      FID_conflict_erase(local_b8,local_6c,local_68);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

