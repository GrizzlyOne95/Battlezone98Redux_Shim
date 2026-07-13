
undefined4 * __thiscall FUN_0067a8c0(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  Root *this;
  RenderSystem *pRVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f498;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0067a270(param_2,1);
  local_8 = 0;
  *param_1 = DynamicGeometryOcclusionQueryBatch::vftable;
  *(undefined1 *)(param_1 + 0xc) = 0;
  this = Ogre::Root::getSingleton();
  pRVar2 = Ogre::Root::getRenderSystem(this);
  uVar3 = (**(code **)(*(int *)pRVar2 + 0x14))(uVar1);
  param_1[0x2d] = uVar3;
  *(undefined1 *)(param_1 + 0x2e) = 0;
  ExceptionList = local_10;
  return param_1;
}

