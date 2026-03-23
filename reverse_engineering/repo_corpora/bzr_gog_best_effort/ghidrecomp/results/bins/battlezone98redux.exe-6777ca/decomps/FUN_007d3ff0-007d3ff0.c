
void FUN_007d3ff0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  MaterialManager *this;
  Material *pMVar3;
  Technique *this_00;
  Pass *this_01;
  TextureUnitState *this_02;
  ushort uVar4;
  ushort uVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  undefined1 uVar7;
  ushort uVar8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar9;
  TextureType TVar10;
  undefined4 extraout_var;
  undefined4 uVar11;
  undefined1 local_e0 [8];
  undefined1 local_d8 [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_d0 [8];
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_bc [8];
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  MaterialManager *local_a8;
  MaterialManager *local_a4;
  uint local_a0;
  int *local_9c;
  QuickBitSet local_98 [11];
  char local_8d;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862ce1;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_a0 = 0;
  local_14 = uVar2;
  Concurrency::details::QuickBitSet::QuickBitSet(local_98);
  local_8 = 1;
  uVar11 = extraout_var;
  basic_string<>(param_2);
  local_8._0_1_ = 2;
  local_a8 = Ogre::MaterialManager::getSingleton();
  local_8d = (**(code **)(*(int *)local_a8 + 0x54))(local_2c,uVar2,uVar11);
  local_8._0_1_ = 1;
  ~basic_string<>();
  if (local_8d == '\0') {
    basic_string<>(&DAT_0087908c);
    local_8._0_1_ = 6;
    pbVar6 = local_8c;
    pbVar9 = local_bc;
    this = Ogre::MaterialManager::getSingleton();
    Ogre::MaterialManager::getByName(this,pbVar9,pbVar6);
    local_8._0_1_ = 8;
    ~basic_string<>();
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      basic_string<>(param_2);
      local_8._0_1_ = 9;
      pbVar9 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0;
      uVar7 = SUB41(local_44,0);
      pbVar6 = local_d0;
      pMVar3 = (Material *)get();
      local_c8 = Ogre::Material::clone(pMVar3,pbVar6,(bool)uVar7,pbVar9);
      local_8._0_1_ = 10;
      local_ac = local_c8;
      FUN_00449910(local_c8);
      local_8._0_1_ = 9;
      FUN_004499a0();
      local_8._0_1_ = 8;
      ~basic_string<>();
      basic_string<>(param_2);
      local_8._0_1_ = 0xb;
      TVar10 = 2;
      pbVar6 = local_74;
      uVar8 = 0;
      uVar5 = 0;
      uVar4 = 0;
      pMVar3 = (Material *)get();
      this_00 = Ogre::Material::getTechnique(pMVar3,uVar4);
      this_01 = Ogre::Technique::getPass(this_00,uVar5);
      this_02 = Ogre::Pass::getTextureUnitState(this_01,uVar8);
      Ogre::TextureUnitState::setTextureName(this_02,pbVar6,TVar10);
      local_8._0_1_ = 8;
      ~basic_string<>();
    }
    local_9c = (int *)get();
    (**(code **)(*local_9c + 0x38))(0);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_004499a0();
  }
  else {
    basic_string<>(param_2);
    local_8._0_1_ = 3;
    local_a4 = Ogre::MaterialManager::getSingleton();
    local_c4 = (**(code **)(*(int *)local_a4 + 0x48))
                         (local_e0,local_5c,AUTODETECT_RESOURCE_GROUP_NAME_exref);
    local_8._0_1_ = 4;
    local_b0 = local_c4;
    local_c0 = FUN_007d4480(local_d8);
    local_8._0_1_ = 5;
    local_b4 = local_c0;
    FUN_00449910(local_c0);
    local_8._0_1_ = 4;
    FUN_004499a0();
    local_8._0_1_ = 3;
    FUN_004499a0();
    local_8 = CONCAT31(local_8._1_3_,1);
    ~basic_string<>();
  }
  FUN_004498d0(local_98);
  local_a0 = local_a0 | 1;
  local_8 = local_8 & 0xffffff00;
  FUN_004499a0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

