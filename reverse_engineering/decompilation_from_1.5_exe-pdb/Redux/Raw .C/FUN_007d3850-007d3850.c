
void FUN_007d3850(undefined4 param_1,int param_2)

{
  char cVar1;
  ExternalTextureSourceManager *this;
  ExternalTextureSource *pEVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  MaterialManager *this_00;
  Material *pMVar4;
  Technique *this_01;
  Matrix4 *pMVar5;
  VideoClip *pVVar6;
  undefined1 uVar7;
  TypeDescriptor *pTVar8;
  ushort uVar9;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar10;
  ushort uVar11;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_f0 [8];
  undefined4 local_e8;
  undefined4 *local_e4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_e0 [8];
  Pass *local_d8;
  SharedPtr<class_Ogre::Texture> *local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  SharedPtr<class_Ogre::Texture> *local_c4;
  int *local_c0;
  MaterialManager *local_bc;
  TextureUnitState *local_b8;
  OgreTheoraVideoManager *local_b4;
  undefined4 *local_b0;
  OgreTheoraVideoClip *local_ac;
  int local_a8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a4 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862c37;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>();
  local_8 = 0;
  pTVar8 = &Ogre::ExternalTextureSource::RTTI_Type_Descriptor;
  pbVar3 = local_44;
  this = Ogre::ExternalTextureSourceManager::getSingleton();
  pEVar2 = Ogre::ExternalTextureSourceManager::getExternalTextureSource(this,pbVar3);
  local_b4 = (OgreTheoraVideoManager *)__RTDynamicCast(pEVar2,0,pTVar8);
  local_8 = 0xffffffff;
  ~basic_string<>();
  if (local_b4 != (OgreTheoraVideoManager *)0x0) {
    if (*(int *)(local_a8 + 0x140) != 0) {
      local_e4 = *(undefined4 **)(local_a8 + 0x140);
      local_b0 = local_e4;
      if (local_e4 == (undefined4 *)0x0) {
        local_c8 = 0;
      }
      else {
        local_c8 = (**(code **)*local_e4)();
      }
      *(undefined4 *)(local_a8 + 0x140) = 0;
      cVar1 = FUN_004c85a0();
      if (cVar1 == '\0') {
        local_c0 = (int *)get();
        pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (**(code **)(*local_c0 + 0x58))();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (local_74,pbVar3);
        local_8 = 1;
        FUN_004c85d0();
        local_bc = Ogre::MaterialManager::getSingleton();
        (**(code **)(*(int *)local_bc + 0x38))();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
    if (param_2 != 0) {
      basic_string<>();
      local_8 = 2;
      Ogre::OgreTheoraVideoManager::setPreferredLanguage(local_b4,local_a4);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    basic_string<>();
    local_8 = 3;
    local_ac = Ogre::OgreTheoraVideoManager::createClip
                         (local_b4,local_5c,
                          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)DEFAULT_RESOURCE_GROUP_NAME_exref);
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (local_ac != (OgreTheoraVideoClip *)0x0) {
      *(OgreTheoraVideoClip **)(local_a8 + 0x140) = local_ac;
      basic_string<>();
      local_8 = 4;
      pbVar3 = local_8c;
      pbVar10 = local_e0;
      this_00 = Ogre::MaterialManager::getSingleton();
      Ogre::MaterialManager::getByName(this_00,pbVar10,pbVar3);
      local_8._0_1_ = 6;
      ~basic_string<>();
      cVar1 = FUN_004c85a0();
      if (cVar1 == '\0') {
        basic_string<>();
        local_8._0_1_ = 7;
        pbVar10 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x0;
        uVar7 = SUB41(local_2c,0);
        pbVar3 = local_f0;
        pMVar4 = (Material *)get();
        local_d0 = Ogre::Material::clone(pMVar4,pbVar3,(bool)uVar7,pbVar10);
        local_8._0_1_ = 8;
        local_cc = local_d0;
        FUN_00449910();
        local_8._0_1_ = 7;
        FUN_004499a0();
        local_8._0_1_ = 6;
        ~basic_string<>();
        uVar11 = 0;
        uVar9 = 0;
        pMVar4 = (Material *)get();
        this_01 = Ogre::Material::getTechnique(pMVar4,uVar9);
        local_d8 = Ogre::Technique::getPass(this_01,uVar11);
        local_b8 = Ogre::Pass::getTextureUnitState(local_d8,0);
        local_d4 = (SharedPtr<class_Ogre::Texture> *)
                   Ogre::OgreTheoraVideoClip::getVideoTexture(local_ac);
        local_8._0_1_ = 9;
        local_c4 = local_d4;
        Ogre::TextureUnitState::setTexture(local_b8,local_d4);
        local_8._0_1_ = 6;
        FUN_004499a0();
        pMVar5 = (Matrix4 *)Ogre::OgreTheoraVideoClip::getScaleMatrix(local_ac);
        Ogre::TextureUnitState::setTextureTransform(local_b8,pMVar5);
      }
      if (((*(uint *)(local_a8 + 0x14) & 1) != 0) && ((*(uint *)(local_a8 + 0x14) & 0x100) != 0)) {
        pVVar6 = Ogre::OgreTheoraVideoClip::getClip(local_ac);
        theoraplayer::VideoClip::getHeight(pVVar6);
        pVVar6 = Ogre::OgreTheoraVideoClip::getClip(local_ac);
        theoraplayer::VideoClip::getWidth(pVVar6);
        FUN_007d14b0(0,0);
      }
      if (*(int *)(local_a8 + 0x120) != 0) {
        (**(code **)(**(int **)(local_a8 + 0x120) + 0x118))();
        FUN_007d2e20();
        (**(code **)(**(int **)(local_a8 + 0x120) + 0x16c))();
      }
      local_e8 = FUN_004498d0(local_a8 + 0x114);
      FUN_007d2b70();
      *(uint *)(local_a8 + 0x14) = *(uint *)(local_a8 + 0x14) | 0x10;
      local_8 = 0xffffffff;
      FUN_004499a0();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

