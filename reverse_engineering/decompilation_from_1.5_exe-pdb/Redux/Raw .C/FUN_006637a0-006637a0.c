
void FUN_006637a0(undefined4 *param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 extraout_var;
  
  puVar4 = &DAT_00892124;
  pbVar2 = Ogre::Viewport::getMaterialScheme((Viewport *)*param_1);
  cVar1 = FUN_00427270(pbVar2,puVar4,extraout_var);
  if (cVar1 != '\0') {
    uVar3 = FUN_00666700(param_1);
    Ogre::Viewport::setShadowsEnabled((Viewport *)*param_1,*(bool *)uVar3);
    FUN_004badc0(param_1);
  }
  return;
}

