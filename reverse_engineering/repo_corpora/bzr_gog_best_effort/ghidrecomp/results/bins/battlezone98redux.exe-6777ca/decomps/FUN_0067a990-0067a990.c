
void __fastcall FUN_0067a990(undefined4 *param_1)

{
  uint uVar1;
  Root *this;
  RenderSystem *pRVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084f498;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = DynamicGeometryOcclusionQueryBatch::vftable;
  local_8 = 0;
  this = Ogre::Root::getSingleton();
  pRVar2 = Ogre::Root::getRenderSystem(this);
  (**(code **)(*(int *)pRVar2 + 0x18))(param_1[0x2d],uVar1);
  local_8 = 0xffffffff;
  FUN_0067a410();
  ExceptionList = local_10;
  return;
}

