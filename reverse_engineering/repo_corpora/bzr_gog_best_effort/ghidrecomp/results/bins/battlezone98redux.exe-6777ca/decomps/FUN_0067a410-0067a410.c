
void __fastcall FUN_0067a410(Renderable *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084f43c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = DynamicGeometryBatch::vftable;
  local_8 = 3;
  Ogre::IndexData::~IndexData((IndexData *)(param_1 + 0x7c));
  local_8._0_1_ = 2;
  Ogre::VertexData::~VertexData((VertexData *)(param_1 + 0x44));
  local_8._0_1_ = 1;
  FUN_004499a0(uVar1);
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::
  ~AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>
            ((AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_> *)(param_1 + 0x24));
  local_8 = 0xffffffff;
  Ogre::Renderable::~Renderable(param_1);
  ExceptionList = local_10;
  return;
}

