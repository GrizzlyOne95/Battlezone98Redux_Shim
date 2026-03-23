
QuickBitSet * __thiscall FUN_007d4480(undefined4 *param_1,QuickBitSet *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = __RTDynamicCast(*param_1,0,&Ogre::Resource::RTTI_Type_Descriptor,
                          &Ogre::Material::RTTI_Type_Descriptor,0);
  if (iVar1 == 0) {
    Concurrency::details::QuickBitSet::QuickBitSet(param_2);
  }
  else {
    FUN_00449b50(iVar1,param_1,uVar2);
    FUN_00416430(iVar1,param_1[1]);
  }
  return param_2;
}

