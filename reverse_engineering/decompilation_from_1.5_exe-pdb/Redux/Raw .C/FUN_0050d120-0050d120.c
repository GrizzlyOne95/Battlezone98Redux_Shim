
void FUN_0050d120(void)

{
  char cVar1;
  uint uVar2;
  TextureManager *this;
  HardwarePixelBuffer *pHVar3;
  PixelBox *pPVar4;
  MaterialManager *this_00;
  Material *pMVar5;
  Technique *this_01;
  Pass *this_02;
  TextureUnitState *this_03;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar11;
  code *pcVar12;
  uint uVar13;
  ushort uVar14;
  int iVar15;
  ushort uVar16;
  PixelFormat PVar17;
  undefined1 uVar18;
  ushort uVar19;
  int iVar20;
  ManualResourceLoader *pMVar21;
  LockOptions LVar22;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar23;
  bool bVar24;
  UploadOptions UVar25;
  TextureType TVar26;
  uint uVar27;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar28;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_94 [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [8];
  undefined8 local_84;
  undefined4 local_7c;
  undefined8 local_78;
  undefined4 local_70;
  undefined4 local_6c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [8];
  undefined4 local_60;
  SharedPtr<class_Ogre::HardwarePixelBuffer> local_5c [8];
  int *local_54;
  HardwarePixelBuffer *local_50;
  float local_4c;
  int local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ac07;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>("MapRadar");
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
            (local_2c,"%d",DAT_02cc2bbc);
  DAT_02cc2bbc = DAT_02cc2bbc + 1;
  local_84 = FUN_00689eb0(uVar2);
  DAT_02a13b98 = DAT_0091757c;
  DAT_02a13b9c = DAT_0091755c;
  DAT_02a13ba0 = DAT_00917560;
  DAT_02a13ba4 = DAT_009175b0;
  DAT_02a13ba8 = DAT_0091757c;
  DAT_02a13bac = DAT_00917588;
  local_78 = local_84;
  fVar6 = (float10)FUN_0044fb20(DAT_00917394 - DAT_0091738c,DAT_00917388 - DAT_00917390);
  local_4c = (float)fVar6;
  *(float *)(local_48 + 0xc) = ((float)local_84 * 158.0) / local_4c;
  pbVar28 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0;
  uVar27 = 0;
  bVar24 = false;
  pMVar21 = (ManualResourceLoader *)0x5;
  iVar20 = 0xc;
  PVar17 = 0;
  iVar15 = 0x9e;
  uVar13 = 0x9e;
  uVar2 = 2;
  pbVar11 = local_2c;
  pbVar23 = local_8c;
  pcVar12 = DEFAULT_RESOURCE_GROUP_NAME_exref;
  this = Ogre::TextureManager::getSingleton();
  local_70 = Ogre::TextureManager::createManual
                       (this,pbVar23,pbVar11,(TextureType)pcVar12,uVar2,uVar13,iVar15,PVar17,iVar20,
                        pMVar21,bVar24,uVar27,pbVar28);
  local_8._0_1_ = 1;
  local_6c = local_70;
  FUN_00449910(local_70);
  local_8._0_1_ = 0;
  FUN_004499a0();
  local_54 = (int *)get();
  (**(code **)(*local_54 + 0x15c))(local_5c,0,0);
  local_8._0_1_ = 2;
  UVar25 = 0;
  LVar22 = 1;
  pHVar3 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_5c);
  Ogre::HardwareBuffer::lock((HardwareBuffer *)pHVar3,LVar22,UVar25);
  fVar7 = (DAT_00917388 + DAT_00917390 + local_4c) * 0.5;
  fVar8 = (DAT_00917394 + DAT_0091738c + local_4c) * 0.5;
  fVar9 = ((DAT_00917388 + DAT_00917390) - local_4c) * 0.5;
  fVar10 = ((DAT_00917394 + DAT_0091738c) - local_4c) * 0.5;
  pHVar3 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_5c);
  pPVar4 = Ogre::HardwarePixelBuffer::getCurrentLock(pHVar3);
  FUN_0050f740(pPVar4,fVar10,fVar9,fVar8,fVar7);
  local_50 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_5c);
  (**(code **)(*(int *)local_50 + 0x10))();
  basic_string<>(&DAT_0087908c);
  local_8._0_1_ = 3;
  pbVar11 = local_44;
  pbVar23 = local_68;
  this_00 = Ogre::MaterialManager::getSingleton();
  Ogre::MaterialManager::getByName(this_00,pbVar23,pbVar11);
  local_8._0_1_ = 5;
  ~basic_string<>();
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    pbVar23 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0;
    uVar18 = SUB41(local_2c,0);
    pbVar11 = local_94;
    pMVar5 = (Material *)get();
    local_7c = Ogre::Material::clone(pMVar5,pbVar11,(bool)uVar18,pbVar23);
    local_8._0_1_ = 6;
    local_60 = local_7c;
    FUN_00449910(local_7c);
    local_8._0_1_ = 5;
    FUN_004499a0();
    TVar26 = 2;
    pbVar11 = local_2c;
    uVar19 = 0;
    uVar16 = 0;
    uVar14 = 0;
    pMVar5 = (Material *)get();
    this_01 = Ogre::Material::getTechnique(pMVar5,uVar14);
    this_02 = Ogre::Technique::getPass(this_01,uVar16);
    this_03 = Ogre::Pass::getTextureUnitState(this_02,uVar19);
    Ogre::TextureUnitState::setTextureName(this_03,pbVar11,TVar26);
  }
  local_8._0_1_ = 2;
  FUN_004499a0();
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr
            ((HardwarePixelBufferSharedPtr *)local_5c);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

