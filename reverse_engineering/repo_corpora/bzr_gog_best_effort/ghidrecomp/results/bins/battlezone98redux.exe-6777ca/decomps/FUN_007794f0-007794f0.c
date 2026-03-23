
void __thiscall FUN_007794f0(int param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uStack_e0;
  AxisAlignedBox local_d0 [32];
  undefined4 local_b0;
  undefined4 local_ac;
  HardwareVertexBufferSharedPtr local_a8 [8];
  HardwareVertexBufferSharedPtr *local_a0;
  HardwareVertexBufferSharedPtr local_9c [8];
  undefined4 local_94;
  HardwareVertexBufferSharedPtr *local_90;
  void *local_8c;
  HardwareVertexBuffer *local_88;
  void *local_84;
  HardwareVertexBuffer *local_80;
  HardwareVertexBuffer *local_78;
  undefined4 local_70;
  Mesh *local_6c;
  int local_68;
  AxisAlignedBox *local_64;
  AxisAlignedBox *local_60;
  HardwareVertexBuffer *local_5c;
  HardwareVertexBuffer *local_58;
  HardwareVertexBuffer *local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined4 local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085e484;
  local_10 = ExceptionList;
  uStack_e0 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_e0;
  ExceptionList = &local_10;
  local_8 = 0;
  *(undefined4 *)(param_1 + 0x3a4) = 0;
  local_28 = param_1;
  local_18 = uStack_e0;
  local_68 = get();
  local_38 = *(int **)(*(int *)(local_68 + 0x1b4) + 8);
  local_4e = 1;
  local_94 = (**(code **)(*local_38 + 0x10))();
  local_90 = (HardwareVertexBufferSharedPtr *)FUN_0077c820(&local_4e);
  local_ac = Ogre::HardwareVertexBufferSharedPtr::HardwareVertexBufferSharedPtr(local_a8,local_90);
  local_8._0_1_ = 1;
  local_5c = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                       ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)local_a8);
  local_8c = Ogre::HardwareBuffer::lock((HardwareBuffer *)local_5c,1,0);
  *(void **)(local_28 + 0x3a8) = local_8c;
  local_50 = 2;
  local_70 = (**(code **)(*local_38 + 0x10))();
  local_a0 = (HardwareVertexBufferSharedPtr *)FUN_0077c820(&local_50);
  local_b0 = Ogre::HardwareVertexBufferSharedPtr::HardwareVertexBufferSharedPtr(local_9c,local_a0);
  local_8 = CONCAT31(local_8._1_3_,2);
  local_78 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                       ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)local_9c);
  local_84 = Ogre::HardwareBuffer::lock((HardwareBuffer *)local_78,1,0);
  *(void **)(local_28 + 0x3ac) = local_84;
  *(undefined4 *)(local_28 + 0x39c) = 0;
  *(undefined4 *)(local_28 + 0x3a0) = 0;
  local_4c = 0x43a00000;
  local_24 = (float)param_3 * 320.0 + *(float *)(local_28 + 0x248);
  local_1c = *(float *)(local_28 + 0x24c) - (float)param_4 * 320.0;
  local_20 = 0;
  *(float *)(local_28 + 0x100 + param_3 * 0x30 + param_4 * 0xc) = local_24 + 160.0;
  *(undefined4 *)(local_28 + param_3 * 0x30 + 0x104 + param_4 * 0xc) = 0;
  *(float *)(local_28 + param_3 * 0x30 + 0x108 + param_4 * 0xc) = local_1c - 160.0;
  local_2c = 2;
  *(undefined4 *)(local_28 + 0x1c0 + param_3 * 0x10 + param_4 * 4) = 0x7f7fffff;
  *(undefined4 *)(local_28 + 0x200 + param_3 * 0x10 + param_4 * 4) = 0xff7fffff;
  FUN_00779c20(param_3,param_4,0,0,2,6,2,6);
  for (local_40 = 1; local_40 < 0x10; local_40 = local_40 + 1) {
    FUN_00779c20(param_3,param_4,local_40,0,0,6,local_2c,6);
  }
  FUN_00779c20(param_3,param_4,0x10,0,0,local_2c + 1,local_2c,6);
  for (local_30 = 1; local_30 < 0x10; local_30 = local_30 + 1) {
    FUN_00779c20(param_3,param_4,0,local_30,local_2c,6,0,6);
  }
  for (local_34 = 1; local_34 < 0x10; local_34 = local_34 + 1) {
    for (local_48 = 1; local_48 < 0x10; local_48 = local_48 + 1) {
      FUN_00779c20(param_3,param_4,local_34,local_48,0,6,0,6);
    }
  }
  FUN_00779c20(param_3,param_4,0,0x10,local_2c,6,0,local_2c + 1);
  for (local_3c = 1; local_3c < 0x10; local_3c = local_3c + 1) {
    FUN_00779c20(param_3,param_4,0x10,local_3c,0,local_2c + 1,0,6);
  }
  for (local_44 = 1; local_44 < 0x10; local_44 = local_44 + 1) {
    FUN_00779c20(param_3,param_4,local_44,0x10,0,6,0,local_2c + 1);
  }
  FUN_00779c20(param_3,param_4,0x10,0x10,0,local_2c + 1,0,local_2c + 1);
  local_80 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                       ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)local_a8);
  local_54 = local_80;
  (**(code **)(*(int *)local_80 + 0x10))();
  local_88 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                       ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)local_9c);
  local_58 = local_88;
  (**(code **)(*(int *)local_88 + 0x10))();
  local_64 = (AxisAlignedBox *)
             Ogre::AxisAlignedBox::AxisAlignedBox
                       (local_d0,*(float *)(local_28 + 0x280 + param_3 * 0x40 + param_4 * 0x10) -
                                 *(float *)(local_28 + 0x100 + param_3 * 0x30 + param_4 * 0xc),
                        *(float *)(local_28 + 0x1c0 + param_3 * 0x10 + param_4 * 4) -
                        *(float *)(local_28 + param_3 * 0x30 + 0x104 + param_4 * 0xc),
                        *(float *)(local_28 + param_3 * 0x40 + 0x284 + param_4 * 0x10) -
                        *(float *)(local_28 + param_3 * 0x30 + 0x108 + param_4 * 0xc),
                        *(float *)(local_28 + param_3 * 0x40 + 0x288 + param_4 * 0x10) -
                        *(float *)(local_28 + 0x100 + param_3 * 0x30 + param_4 * 0xc),
                        *(float *)(local_28 + 0x200 + param_3 * 0x10 + param_4 * 4) -
                        *(float *)(local_28 + param_3 * 0x30 + 0x104 + param_4 * 0xc),
                        *(float *)(local_28 + param_3 * 0x40 + 0x28c + param_4 * 0x10) -
                        *(float *)(local_28 + param_3 * 0x30 + 0x108 + param_4 * 0xc));
  local_8._0_1_ = 3;
  local_60 = local_64;
  local_6c = (Mesh *)get();
  Ogre::Mesh::_setBounds(local_6c,local_64,false);
  local_8._0_1_ = 2;
  Ogre::AxisAlignedBox::~AxisAlignedBox(local_d0);
  *(undefined1 *)(local_28 + 0x270 + param_3 * 4 + param_4) = 0;
  local_8._0_1_ = 1;
  Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr(local_9c);
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr(local_a8);
  FUN_00779bdc();
  return;
}

