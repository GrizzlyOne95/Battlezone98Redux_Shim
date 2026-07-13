
void FUN_004c1a00(void)

{
  char cVar1;
  uint uVar2;
  TextureManager *this;
  MaterialManager *this_00;
  Material *pMVar3;
  Technique *this_01;
  Pass *this_02;
  TextureUnitState *this_03;
  SharedPtr<class_Ogre::Texture> *pSVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  code *pcVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  PixelFormat PVar10;
  int iVar11;
  ManualResourceLoader *pMVar12;
  bool bVar13;
  ushort uVar14;
  undefined1 uVar15;
  ushort uVar16;
  uint uVar17;
  ushort uVar18;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar19;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar20;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_88 [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_80 [8];
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [8];
  int local_60;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849da3;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>("EditTerrain");
  local_8 = 0;
  pbVar19 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0;
  uVar17 = 0;
  bVar13 = false;
  pMVar12 = (ManualResourceLoader *)0xe;
  iVar11 = 0xc;
  PVar10 = 0;
  iVar9 = *(int *)(local_60 + 0x84);
  uVar8 = *(uint *)(local_60 + 0x80);
  uVar7 = 2;
  pbVar5 = local_5c;
  pbVar20 = local_88;
  pcVar6 = DEFAULT_RESOURCE_GROUP_NAME_exref;
  this = Ogre::TextureManager::getSingleton();
  local_70 = Ogre::TextureManager::createManual
                       (this,pbVar20,pbVar5,(TextureType)pcVar6,uVar7,uVar8,iVar9,PVar10,iVar11,
                        pMVar12,bVar13,uVar17,pbVar19);
  local_8._0_1_ = 1;
  local_6c = local_70;
  FUN_00449910(local_70);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0(uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>(&DAT_0087908c);
  local_8 = 2;
  pbVar5 = local_44;
  pbVar20 = local_68;
  this_00 = Ogre::MaterialManager::getSingleton();
  Ogre::MaterialManager::getByName(this_00,pbVar20,pbVar5);
  local_8._0_1_ = 4;
  ~basic_string<>();
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    basic_string<>("EditTerrain");
    local_8._0_1_ = 5;
    pbVar20 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0;
    uVar15 = SUB41(local_2c,0);
    pbVar5 = local_80;
    pMVar3 = (Material *)get();
    local_78 = Ogre::Material::clone(pMVar3,pbVar5,(bool)uVar15,pbVar20);
    local_8._0_1_ = 6;
    local_74 = local_78;
    FUN_00449910(local_78);
    local_8._0_1_ = 5;
    FUN_004499a0();
    local_8 = CONCAT31(local_8._1_3_,4);
    ~basic_string<>();
    pSVar4 = (SharedPtr<class_Ogre::Texture> *)(local_60 + 0xbc);
    uVar18 = 0;
    uVar16 = 0;
    uVar14 = 0;
    pMVar3 = (Material *)get();
    this_01 = Ogre::Material::getTechnique(pMVar3,uVar14);
    this_02 = Ogre::Technique::getPass(this_01,uVar16);
    this_03 = Ogre::Pass::getTextureUnitState(this_02,uVar18);
    Ogre::TextureUnitState::setTexture(this_03,pSVar4);
  }
  local_8 = 0xffffffff;
  FUN_004499a0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

