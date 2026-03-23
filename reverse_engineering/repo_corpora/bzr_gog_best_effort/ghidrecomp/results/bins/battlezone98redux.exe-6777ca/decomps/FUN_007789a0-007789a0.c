
void FUN_007789a0(undefined4 param_1,int param_2,int param_3)

{
  char cVar1;
  Mesh *this;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  HardwareVertexBuffer *this_00;
  uint uStack_fc;
  SharedPtr<class_Ogre::HardwareVertexBuffer> local_90 [16];
  VertexData *local_80;
  HardwareBufferManager *local_78;
  undefined4 local_74;
  HardwareVertexBuffer *local_6c;
  void *local_68;
  void *local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  int local_4c;
  SubMesh *local_48;
  int local_44;
  int local_3c;
  int *local_38;
  int local_34;
  char local_2e;
  int *local_2c;
  int local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e430;
  local_10 = ExceptionList;
  uStack_fc = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_fc;
  ExceptionList = &local_10;
  local_18 = uStack_fc;
  this = (Mesh *)get();
  local_48 = Ogre::Mesh::createSubMesh(this);
  FUN_00778950(param_2,param_3);
  *(undefined4 *)(local_28 + 0x3a4) = 0;
  FUN_0077c670();
  cVar1 = FUN_0077c010();
  if (cVar1 != '\0') {
    FUN_0077c670();
    uVar2 = FUN_0077bff0();
    *(undefined4 *)(local_28 + 0x3a4) = uVar2;
  }
  local_68 = malloc(*(size_t *)(local_28 + 0x398));
  *(void **)(local_28 + 0x3a8) = local_68;
  local_64 = malloc(*(size_t *)(local_28 + 0x390));
  *(void **)(local_28 + 0x3ac) = local_64;
  *(undefined4 *)(local_28 + 0x39c) = 0;
  *(undefined4 *)(local_28 + 0x3a0) = 0;
  local_50 = 0x43a00000;
  local_24 = (float)param_2 * 320.0 + *(float *)(local_28 + 0x248);
  local_1c = *(float *)(local_28 + 0x24c) - (float)param_3 * 320.0;
  local_20 = 0;
  *(float *)(local_28 + 0x100 + param_2 * 0x30 + param_3 * 0xc) = local_24 + 160.0;
  *(undefined4 *)(local_28 + param_2 * 0x30 + 0x104 + param_3 * 0xc) = 0;
  *(float *)(local_28 + param_2 * 0x30 + 0x108 + param_3 * 0xc) = local_1c - 160.0;
  *(undefined4 *)(local_28 + 0x1c0 + param_2 * 0x10 + param_3 * 4) = 0x7f7fffff;
  *(undefined4 *)(local_28 + 0x200 + param_2 * 0x10 + param_3 * 4) = 0xff7fffff;
  FUN_00779c20(param_2,param_3,0,0,2,6,2,6);
  for (local_58 = 1; local_58 < 0x10; local_58 = local_58 + 1) {
    FUN_00779c20(param_2,param_3,local_58,0,0,6,2,6);
  }
  FUN_00779c20(param_2,param_3,0x10,0,0,3,2,6);
  for (local_44 = 1; local_44 < 0x10; local_44 = local_44 + 1) {
    FUN_00779c20(param_2,param_3,0,local_44,2,6,0,6);
  }
  for (local_4c = 1; local_4c < 0x10; local_4c = local_4c + 1) {
    for (local_3c = 1; local_3c < 0x10; local_3c = local_3c + 1) {
      FUN_00779c20(param_2,param_3,local_4c,local_3c,0,6,0,6);
    }
  }
  FUN_00779c20(param_2,param_3,0,0x10,2,6,0,3);
  for (local_54 = 1; local_54 < 0x10; local_54 = local_54 + 1) {
    FUN_00779c20(param_2,param_3,0x10,local_54,0,3,0,6);
  }
  for (local_5c = 1; local_5c < 0x10; local_5c = local_5c + 1) {
    FUN_00779c20(param_2,param_3,local_5c,0x10,0,6,0,3);
  }
  FUN_00779c20(param_2,param_3,0x10,0x10,0,3,0,3);
  local_80 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<1>_>::operator_new(0x34);
  local_8 = 0;
  if (local_80 == (VertexData *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = Ogre::VertexData::VertexData(local_80,(HardwareBufferManagerBase *)0x0);
  }
  uVar2 = local_74;
  local_8 = 0xffffffff;
  iVar3 = get();
  *(undefined4 *)(iVar3 + 0x1b4) = uVar2;
  iVar3 = get();
  *(undefined4 *)(*(int *)(iVar3 + 0x1b4) + 0x14) = *(undefined4 *)(local_28 + 0x39c);
  FUN_0077c670();
  cVar1 = FUN_0077c010();
  if (cVar1 != '\0') {
    FUN_0077c670();
    FUN_0041c1d0();
  }
  iVar3 = get();
  local_2c = *(int **)(*(int *)(iVar3 + 0x1b4) + 4);
  local_34 = 0;
  local_60 = 0;
  (**(code **)(*local_2c + 4))(0,0,2,1,0);
  uVar4 = Ogre::VertexElement::getTypeSize(2);
  local_34 = uVar4 + local_34;
  (**(code **)(*local_2c + 4))(0,local_34,4,5,0);
  uVar4 = Ogre::VertexElement::getTypeSize(4);
  local_34 = uVar4 + local_34;
  (**(code **)(*local_2c + 4))(1,local_60,9,3,0);
  uVar4 = Ogre::VertexElement::getTypeSize(9);
  local_60 = uVar4 + local_60;
  iVar3 = get();
  local_38 = *(int **)(*(int *)(iVar3 + 0x1b4) + 8);
  FUN_0077c670();
  cVar1 = FUN_0077c110();
  if (cVar1 != '\0') {
    FUN_0077c670();
    FUN_0077c130();
  }
  iVar3 = FUN_0077c670();
  (**(code **)(*local_38 + 4))(0,iVar3 + 4);
  local_78 = Ogre::HardwareBufferManager::getSingleton();
  iVar3 = get(5,0);
  (**(code **)(*(int *)local_78 + 0x20))(local_90,4,*(undefined4 *)(*(int *)(iVar3 + 0x1b4) + 0x14))
  ;
  local_8 = 2;
  FUN_0077c670();
  local_2e = FUN_00777710();
  if (local_2e == '\0') {
    *(undefined1 *)(local_28 + 0x270 + param_2 * 4 + param_3) = 1;
  }
  else {
    local_6c = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->(local_90);
    this_00 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->(local_90);
    uVar4 = Ogre::HardwareBuffer::getSizeInBytes((HardwareBuffer *)this_00);
    (**(code **)(*(int *)local_6c + 0x18))(0,uVar4,local_68,1);
  }
  FUN_00779058();
  return;
}

