
void __fastcall FUN_006658b0(int param_1)

{
  undefined4 uVar1;
  ColourValue *pCVar2;
  ResourceGroupManager *this;
  MaterialManager *pMVar3;
  TextureManager *this_00;
  SharedPtr<class_Ogre::Texture> *pSVar4;
  Material *this_01;
  Technique *this_02;
  Pass *this_03;
  TextureUnitState *this_04;
  uint uVar5;
  ushort uVar6;
  ushort uVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar8;
  ushort uVar9;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar10;
  ColourValue local_ac [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_9c [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_94 [8];
  uint local_8c;
  SharedPtr<class_Ogre::Texture> *local_88;
  undefined4 local_84;
  undefined4 local_80;
  SharedPtr<class_Ogre::Texture> *local_7c;
  undefined4 local_78;
  undefined4 local_74;
  MaterialManager *local_70;
  TextureManager *local_6c;
  Timer *local_68;
  char local_61;
  int local_60;
  undefined1 local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e0ca;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_60 = param_1;
  uVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x2c))
                    (*(undefined4 *)(param_1 + 0x10),0,0,0,0x3f800000,0x3f800000,local_14);
  *(undefined4 *)(local_60 + 0x1c) = uVar1;
  Ogre::Viewport::setVisibilityMask(*(Viewport **)(local_60 + 0x1c),1);
  pCVar2 = (ColourValue *)Ogre::ColourValue::ColourValue(local_ac,0.0,0.0,0.0,1.0);
  Ogre::Viewport::setBackgroundColour(*(Viewport **)(local_60 + 0x1c),pCVar2);
  Ogre::Viewport::setOverlaysEnabled(*(Viewport **)(local_60 + 0x1c),true);
  Ogre::Viewport::setAutoUpdated(*(Viewport **)(local_60 + 0x1c),true);
  *(undefined4 *)(local_60 + 0x20) = 0;
  *(undefined4 *)(local_60 + 0x24) = 0;
  local_6c = Ogre::TextureManager::getSingleton();
  (**(code **)(*(int *)local_6c + 0xc0))(0x7fffffff);
  this = Ogre::ResourceGroupManager::getSingleton();
  Ogre::ResourceGroupManager::initialiseAllResourceGroups(this);
  local_70 = Ogre::MaterialManager::getSingleton();
  (**(code **)(*(int *)local_70 + 0x8c))(3);
  FUN_0067dd00();
  local_61 = *(char *)(DAT_0094672c + 0x24);
  if (local_61 == '\0') {
    uVar5 = 1;
    pMVar3 = Ogre::MaterialManager::getSingleton();
    Ogre::MaterialManager::setDefaultAnisotropy(pMVar3,uVar5);
  }
  else {
    uVar5 = 1 << (local_61 - 1U & 0x1f);
    local_8c = uVar5;
    pMVar3 = Ogre::MaterialManager::getSingleton();
    Ogre::MaterialManager::setDefaultAnisotropy(pMVar3,uVar5);
  }
  (**(code **)(**(int **)(local_60 + 8) + 0x3d8))(1);
  basic_string<>("Ogre/DepthShadowmap/Caster/Float");
  local_8 = 0;
  (**(code **)(**(int **)(local_60 + 8) + 0x3e0))(local_5c);
  local_8 = 0xffffffff;
  ~basic_string<>();
  (**(code **)(**(int **)(local_60 + 8) + 0x374))(0x25);
  FUN_00680fe0();
  local_68 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_new(0x20);
  local_8 = 1;
  if (local_68 == (Timer *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = Ogre::Timer::Timer(local_68);
  }
  local_84 = local_74;
  local_8 = 0xffffffff;
  *(undefined4 *)(local_60 + 0x2c) = local_74;
  Ogre::Timer::reset(*(Timer **)(local_60 + 0x2c));
  FUN_00435ef0(1);
  FUN_00663aa0();
  basic_string<>("scope");
  local_8 = 2;
  pbVar10 = local_44;
  pbVar8 = local_9c;
  pMVar3 = Ogre::MaterialManager::getSingleton();
  local_80 = Ogre::MaterialManager::getByName(pMVar3,pbVar8,pbVar10);
  local_8._0_1_ = 3;
  local_78 = local_80;
  FUN_00449910(local_80);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_004499a0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>("SniperTex");
  local_8 = 4;
  pbVar10 = local_2c;
  pbVar8 = local_94;
  this_00 = Ogre::TextureManager::getSingleton();
  pSVar4 = (SharedPtr<class_Ogre::Texture> *)Ogre::TextureManager::getByName(this_00,pbVar8,pbVar10)
  ;
  local_8._0_1_ = 5;
  uVar9 = 0;
  uVar7 = 0;
  uVar6 = 0;
  local_88 = pSVar4;
  local_7c = pSVar4;
  this_01 = (Material *)get();
  this_02 = Ogre::Material::getTechnique(this_01,uVar6);
  this_03 = Ogre::Technique::getPass(this_02,uVar7);
  this_04 = Ogre::Pass::getTextureUnitState(this_03,uVar9);
  Ogre::TextureUnitState::setTexture(this_04,pSVar4);
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_004499a0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

