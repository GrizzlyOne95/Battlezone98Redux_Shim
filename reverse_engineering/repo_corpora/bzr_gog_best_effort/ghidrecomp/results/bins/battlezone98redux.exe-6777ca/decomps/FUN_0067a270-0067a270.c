
Renderable * __thiscall FUN_0067a270(Renderable *param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f3e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  Ogre::Renderable::Renderable(param_1);
  local_8 = 0;
  Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::
  AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>
            ((AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_> *)(param_1 + 0x24));
  local_8._0_1_ = 1;
  *(undefined ***)param_1 = DynamicGeometryBatch::vftable;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = param_3;
  *(int *)(param_1 + 0x38) = param_2;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x3c));
  local_8._0_1_ = 2;
  Ogre::VertexData::VertexData
            ((VertexData *)(param_1 + 0x44),*(VertexDeclaration **)(param_2 + 0x148),
             (VertexBufferBinding *)0x0);
  local_8._0_1_ = 3;
  Ogre::IndexData::IndexData((IndexData *)(param_1 + 0x7c));
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_00677a00();
  *(undefined4 *)(param_1 + 0xb0) = 0;
  uVar1 = size();
  *(undefined4 *)(param_1 + 0x2c) = uVar1;
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_2 + 400);
  *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_2 + 0x194);
  param_1[0x30] = (Renderable)0x1;
  param_1[0x31] = (Renderable)0x1;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(Renderable **)(param_1 + 0xa0) = param_1;
  *(undefined4 *)(param_1 + 0x94) = 4;
  *(Renderable **)(param_1 + 0x90) = param_1 + 0x44;
  *(Renderable **)(param_1 + 0x9c) = param_1 + 0x7c;
  ExceptionList = local_10;
  return param_1;
}

