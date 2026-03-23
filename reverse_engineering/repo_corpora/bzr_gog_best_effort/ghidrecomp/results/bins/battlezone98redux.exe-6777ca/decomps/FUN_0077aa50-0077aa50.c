
void __fastcall FUN_0077aa50(int param_1)

{
  bool bVar1;
  char cVar2;
  ResourceGroupManager *pRVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  uint uVar8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar9;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar10;
  code *pcVar11;
  Resource *pRVar12;
  undefined1 local_2e0 [4];
  undefined4 *local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2d0 [8];
  undefined4 *local_2c8;
  undefined4 local_2c4;
  int *local_2c0;
  undefined4 local_2bc;
  int *local_2b8;
  int *local_2b4;
  undefined1 local_2b0 [4];
  undefined4 local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  char *local_29c;
  char *local_298;
  int local_294;
  uint local_290;
  int local_28c;
  char local_285;
  undefined1 local_284 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_26c [24];
  char local_254 [256];
  char local_154 [256];
  undefined1 local_54;
  undefined1 local_53 [63];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e53c;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_28c = param_1;
  FUN_0048b7d0(local_26c,param_1 + 0x18,&DAT_0089d26c,local_14);
  local_8 = 0;
  pbVar10 = local_26c;
  pRVar3 = Ogre::ResourceGroupManager::getSingleton();
  bVar1 = Ogre::ResourceGroupManager::resourceExistsInAnyGroup(pRVar3,pbVar10);
  if (bVar1) {
    local_29c = setlocale(4,(char *)0x0);
    local_298 = local_254;
    do {
      local_285 = *local_29c;
      *local_298 = local_285;
      local_29c = local_29c + 1;
      local_298 = local_298 + 1;
    } while (local_285 != '\0');
    setlocale(4,"C");
    FUN_0077c9c0();
    local_8._0_1_ = 1;
    pRVar12 = (Resource *)0x1;
    pbVar10 = local_26c;
    pbVar9 = local_2d0;
    pcVar11 = DEFAULT_RESOURCE_GROUP_NAME_exref;
    pRVar3 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::openResource(pRVar3,pbVar9,pbVar10,SUB41(pcVar11,0),pRVar12);
    local_8._0_1_ = 2;
    while( true ) {
      local_2b4 = (int *)get();
      cVar2 = (**(code **)(*local_2b4 + 0x30))();
      if (cVar2 != '\0') break;
      basic_string<>(&DAT_0087a44c);
      local_8._0_1_ = 3;
      local_2b8 = (int *)get();
      (**(code **)(*local_2b8 + 0x14))(local_154,0x100,local_284);
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_54 = 0;
      memset(local_53,0,0x3f);
      FUN_00777670();
      iVar4 = sscanf(local_154,",%f,%f,%f,%f",&local_2ac,&local_2a8,&local_2a4,&local_2a0);
      if ((iVar4 == 4) ||
         (iVar4 = sscanf(local_154,"%[^, \t],%f,%f,%f,%f",&local_54,&local_2ac,&local_2a8,&local_2a4
                         ,&local_2a0), iVar4 == 5)) {
        local_2d4 = FUN_00446460(&local_54,0x811c9dc5);
        puVar5 = (undefined4 *)FUN_0077ca00(&local_2d4);
        *puVar5 = local_2ac;
        puVar5[1] = local_2a8;
        puVar5[2] = local_2a4;
        puVar5[3] = local_2a0;
      }
    }
    local_2c0 = (int *)get();
    (**(code **)(*local_2c0 + 0x34))();
    local_2d8 = FUN_00446460(&DAT_008a1ad8,0x811c9dc5);
    local_2dc = (undefined4 *)FUN_0077ca00(&local_2d8);
    FUN_0077c8b0(0x100);
    for (local_294 = 0; local_294 < 0x100; local_294 = local_294 + 1) {
      local_2bc = FUN_00780db0(local_294);
      local_2c4 = FUN_00446460(local_2bc,0x811c9dc5);
      FUN_0044eb20(local_2b0,&local_2c4);
      uVar6 = FUN_0044eaa0(local_2e0);
      cVar2 = FUN_00420f10(uVar6);
      if (cVar2 == '\0') {
        uVar6 = FUN_0041f870();
        FUN_007d6c70("Terrain tile \"%s\" not found in %s\n",local_2bc,uVar6);
        puVar5 = (undefined4 *)FUN_0077ca80(&local_2c4);
        *puVar5 = *local_2dc;
        puVar5[1] = local_2dc[1];
        puVar5[2] = local_2dc[2];
        puVar5[3] = local_2dc[3];
        local_2c8 = puVar5;
        puVar7 = (undefined4 *)FUN_005111d0(local_294);
        *puVar7 = *puVar5;
        puVar7[1] = puVar5[1];
        puVar7[2] = puVar5[2];
        puVar7[3] = puVar5[3];
      }
      else {
        iVar4 = FUN_0042da60();
        puVar5 = (undefined4 *)FUN_005111d0(local_294);
        *puVar5 = *(undefined4 *)(iVar4 + 4);
        puVar5[1] = *(undefined4 *)(iVar4 + 8);
        puVar5[2] = *(undefined4 *)(iVar4 + 0xc);
        puVar5[3] = *(undefined4 *)(iVar4 + 0x10);
      }
    }
    setlocale(4,local_254);
    local_8._0_1_ = 1;
    FUN_004499a0();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00452200();
  }
  else {
    FUN_0077c8b0(0x40);
    for (local_290 = 0; (int)local_290 < 0x40; local_290 = local_290 + 1) {
      uVar8 = local_290 & 0x80000007;
      if ((int)uVar8 < 0) {
        uVar8 = (uVar8 - 1 | 0xfffffff8) + 1;
      }
      puVar5 = (undefined4 *)
               FUN_007776c0((float)(int)uVar8 * 0.125,
                            (float)((int)(local_290 + ((int)local_290 >> 0x1f & 7U)) >> 3) * 0.125,
                            0x3e000000,0x3e000000);
      puVar7 = (undefined4 *)FUN_005111d0(local_290);
      *puVar7 = *puVar5;
      puVar7[1] = puVar5[1];
      puVar7[2] = puVar5[2];
      puVar7[3] = puVar5[3];
    }
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

