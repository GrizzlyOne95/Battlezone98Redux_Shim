
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __thiscall FUN_0044c840(undefined4 *param_1,int param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  Radian *pRVar4;
  Radian *pRVar5;
  float fVar6;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846618;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00448f10(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = LightRender::vftable;
  iVar2 = FUN_0044d2a0(uVar1);
  uVar3 = (**(code **)(**(int **)(iVar2 + 8) + 0x11c))();
  param_1[0x1c] = uVar3;
  Ogre::Light::setType((Light *)param_1[0x1c],*(LightTypes *)(param_2 + 0x17c));
  Ogre::Light::setPosition
            ((Light *)param_1[0x1c],(float)(*(double *)(param_4 + 0x28) - (double)_DAT_025f8e4c),
             (float)(*(double *)(param_4 + 0x30) - (double)_DAT_025f8e50),
             (float)(-*(double *)(param_4 + 0x38) - (double)_DAT_025f8e54));
  Ogre::Light::setDirection
            ((Light *)param_1[0x1c],*(float *)(param_4 + 0x18),*(float *)(param_4 + 0x1c),
             -*(float *)(param_4 + 0x20));
  Ogre::Light::setAttenuation
            ((Light *)param_1[0x1c],*(float *)(param_2 + 0x16c),1.0,0.0,
             15.0 / (*(float *)(param_2 + 0x16c) * *(float *)(param_2 + 0x16c)));
  fVar6 = 1.0;
  pRVar4 = (Radian *)FUN_0044c7a0(*(undefined4 *)(param_2 + 0x184));
  pRVar5 = (Radian *)FUN_0044c7a0(*(undefined4 *)(param_2 + 0x180));
  Ogre::Light::setSpotlightRange((Light *)param_1[0x1c],pRVar5,pRVar4,fVar6);
  Ogre::Light::setDiffuseColour
            ((Light *)param_1[0x1c],*(float *)(param_2 + 0x14c),*(float *)(param_2 + 0x150),
             *(float *)(param_2 + 0x154));
  Ogre::Light::setSpecularColour
            ((Light *)param_1[0x1c],*(float *)(param_2 + 0x14c),*(float *)(param_2 + 0x150),
             *(float *)(param_2 + 0x154));
  ExceptionList = local_10;
  return param_1;
}

