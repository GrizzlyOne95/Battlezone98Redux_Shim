
void FUN_00663740(undefined4 *param_1)

{
  char cVar1;
  bool bVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  undefined4 uVar4;
  undefined *puVar5;
  
  puVar5 = &DAT_00892124;
  pbVar3 = Ogre::Viewport::getMaterialScheme((Viewport *)*param_1);
  cVar1 = FUN_00427270(pbVar3,puVar5);
  if (cVar1 != '\0') {
    bVar2 = Ogre::Viewport::getShadowsEnabled((Viewport *)*param_1);
    uVar4 = FUN_00666700(param_1);
    *(bool *)uVar4 = bVar2;
    Ogre::Viewport::setShadowsEnabled((Viewport *)*param_1,false);
  }
  return;
}

