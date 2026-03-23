
void FUN_006879a0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  char cVar1;
  MaterialManager *this;
  Material *this_00;
  Technique *this_01;
  Pass *this_02;
  TextureUnitState *this_03;
  undefined4 uVar2;
  ushort uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  ushort uVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  ushort uVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_3c [8];
  undefined4 local_34;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_30;
  int *local_2c;
  int *local_28;
  SharedPtr<class_Ogre::Texture> *local_24;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  basic_string<>(param_3);
  pbVar6 = local_20;
  pbVar4 = local_3c;
  this = Ogre::MaterialManager::getSingleton();
  Ogre::MaterialManager::getByName(this,pbVar4,pbVar6);
  local_30 = local_3c;
  ~basic_string<>();
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    uVar7 = 0;
    uVar5 = 0;
    uVar3 = 0;
    this_00 = (Material *)get();
    this_01 = Ogre::Material::getTechnique(this_00,uVar3);
    this_02 = Ogre::Technique::getPass(this_01,uVar5);
    this_03 = Ogre::Pass::getTextureUnitState(this_02,uVar7);
    local_24 = Ogre::TextureUnitState::_getTexturePtr(this_03);
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      if (param_1 != (undefined4 *)0x0) {
        local_2c = (int *)get();
        uVar2 = (**(code **)(*local_2c + 0xe8))();
        *param_1 = uVar2;
      }
      if (param_2 != (undefined4 *)0x0) {
        local_28 = (int *)get();
        uVar2 = (**(code **)(*local_28 + 0xe4))();
        *param_2 = uVar2;
      }
      FUN_004499a0(1);
      goto LAB_00687aac;
    }
  }
  local_34 = 0;
  FUN_004499a0();
LAB_00687aac:
  FUN_0083e885();
  return;
}

