
void FUN_00661f20(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  Material *pMVar4;
  Pass *pPVar5;
  float fVar6;
  ushort uVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar8;
  undefined1 uVar9;
  int iVar10;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar11;
  bool bVar12;
  SceneBlendType SVar13;
  undefined1 local_c0 [12];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_b4 [20];
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  Technique *local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  MaterialManager *local_80;
  int *local_7c;
  int local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084dad1;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if ((DAT_02cc32e4 & 1) == 0) {
    DAT_02cc32e4 = DAT_02cc32e4 | 1;
    local_8 = 0;
    basic_string<>("EntityTransparencyMaterial_");
    FUN_0083e979(FUN_008677c0);
  }
  local_8 = 0xffffffff;
  basic_string<>(uVar2);
  local_8._0_1_ = 1;
  local_8._1_3_ = 0;
  do {
    local_7c = (int *)get();
    iVar10 = 0x20;
    cVar1 = '\0';
    uVar7 = 6;
    fVar6 = Ogre::Math::UnitRandom();
    local_98 = Ogre::StringConverter::toString((float)local_44,SUB42(fVar6,0),uVar7,cVar1,iVar10);
    local_8._0_1_ = 2;
    local_88 = local_98;
    uVar3 = (**(code **)(*local_7c + 0x58))();
    local_a0 = FUN_00662500(local_5c,&DAT_02cc32e8,uVar3);
    local_8._0_1_ = 3;
    local_90 = local_a0;
    local_8c = FUN_006625c0(local_74,local_a0,local_98);
    FUN_0045e0f0(local_8c);
    ~basic_string<>();
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_80 = Ogre::MaterialManager::getSingleton();
    cVar1 = (**(code **)(*(int *)local_80 + 0x54))(local_2c);
  } while (cVar1 != '\0');
  pbVar11 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0;
  uVar9 = SUB41(local_2c,0);
  pbVar8 = local_b4;
  pMVar4 = (Material *)get();
  local_9c = Ogre::Material::clone(pMVar4,pbVar8,(bool)uVar9,pbVar11);
  local_8._0_1_ = 4;
  local_84 = local_9c;
  FUN_00449910(local_9c);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_004499a0();
  pMVar4 = (Material *)get(local_c0);
  Ogre::Material::getTechniqueIterator(pMVar4);
  while (cVar1 = FUN_006624a0(), cVar1 != '\0') {
    local_94 = (Technique *)FUN_00662470();
    Ogre::Technique::getPassIterator(local_94);
    while (cVar1 = FUN_006624a0(), cVar1 != '\0') {
      bVar12 = false;
      pPVar5 = (Pass *)FUN_006624c0();
      Ogre::Pass::setDepthWriteEnabled(pPVar5,bVar12);
      SVar13 = *(SceneBlendType *)(local_78 + 0x18);
      pPVar5 = (Pass *)FUN_006624c0();
      Ogre::Pass::setSceneBlending(pPVar5,SVar13);
      FUN_006624e0();
    }
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

