
void __fastcall FUN_00778450(int param_1)

{
  uint uVar1;
  int iVar2;
  HardwareVertexBufferSharedPtr *pHVar3;
  HardwareVertexBuffer *this;
  void *pvVar4;
  LockOptions LVar5;
  UploadOptions UVar6;
  HardwareVertexBufferSharedPtr local_44 [8];
  HardwareVertexBuffer *local_3c;
  int *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e3d9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = param_1;
  for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
    for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
      if (*(char *)(local_1c + 0x270 + local_14 * 4 + local_18) != '\0') {
        FUN_007794f0(local_14 * 0x20 + local_1c + local_18 * 8,local_14,local_18,uVar1);
      }
      if ((*(char *)(local_1c + 0x250 + local_14 * 4 + local_18) != '\0') ||
         (*(char *)(local_1c + 0x260 + local_14 * 4 + local_18) != '\0')) {
        iVar2 = get();
        local_38 = *(int **)(*(int *)(iVar2 + 0x1b4) + 8);
        pHVar3 = (HardwareVertexBufferSharedPtr *)(**(code **)(*local_38 + 0x14))(2);
        Ogre::HardwareVertexBufferSharedPtr::HardwareVertexBufferSharedPtr(local_44,pHVar3);
        local_8 = 0;
        UVar6 = 0;
        LVar5 = 1;
        this = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                         ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)local_44);
        pvVar4 = Ogre::HardwareBuffer::lock((HardwareBuffer *)this,LVar5,UVar6);
        *(void **)(local_1c + 0x3ac) = pvVar4;
        FUN_0077a580(local_14,local_18,0,0,2,6,2,6);
        for (local_20 = 1; local_20 < 0x10; local_20 = local_20 + 1) {
          FUN_0077a580(local_14,local_18,local_20,0,0,6,2,6);
        }
        FUN_0077a580(local_14,local_18,0x10,0,0,3,2,6);
        for (local_24 = 1; local_24 < 0x10; local_24 = local_24 + 1) {
          FUN_0077a580(local_14,local_18,0,local_24,2,6,0,6);
        }
        for (local_2c = 1; local_2c < 0x10; local_2c = local_2c + 1) {
          for (local_28 = 1; local_28 < 0x10; local_28 = local_28 + 1) {
            FUN_0077a580(local_14,local_18,local_2c,local_28,0,6,0,6);
          }
        }
        FUN_0077a580(local_14,local_18,0,0x10,2,6,0,3);
        for (local_30 = 1; local_30 < 0x10; local_30 = local_30 + 1) {
          FUN_0077a580(local_14,local_18,0x10,local_30,0,3,0,6);
        }
        for (local_34 = 1; local_34 < 0x10; local_34 = local_34 + 1) {
          FUN_0077a580(local_14,local_18,local_34,0x10,0,6,0,3);
        }
        FUN_0077a580(local_14,local_18,0x10,0x10,0,3,0,3);
        local_3c = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                             ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)local_44);
        (**(code **)(*(int *)local_3c + 0x10))();
        *(undefined4 *)(local_1c + 0x3ac) = 0;
        local_8 = 0xffffffff;
        Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr(local_44);
      }
      if (*(char *)(local_1c + 0x250 + local_14 * 4 + local_18) == '\0') {
        *(undefined1 *)(local_1c + 0x260 + local_14 * 4 + local_18) = 0;
      }
      else {
        *(undefined1 *)(local_1c + 0x250 + local_14 * 4 + local_18) = 0;
        *(undefined1 *)(local_1c + 0x260 + local_14 * 4 + local_18) = 1;
      }
    }
  }
  ExceptionList = local_10;
  return;
}

