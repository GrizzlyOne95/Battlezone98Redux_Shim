
void FUN_004c1c50(void)

{
  HardwarePixelBuffer *pHVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  ushort *puVar4;
  uint uVar5;
  LockOptions LVar6;
  UploadOptions UVar7;
  undefined1 local_8c [4];
  SharedPtr<class_Ogre::HardwarePixelBuffer> local_88 [8];
  float local_80;
  int *local_7c;
  float local_78;
  float local_74;
  PixelBox *local_70;
  HardwarePixelBuffer *local_6c;
  float local_68;
  float local_64;
  undefined2 local_5f;
  byte local_5d;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined2 local_44;
  byte local_42;
  uint local_40;
  int local_3c;
  int local_38;
  undefined1 *local_34;
  int local_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849ddc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_7c = (int *)get(local_14);
  (**(code **)(*local_7c + 0x15c))(local_88,0,0);
  local_8 = 0;
  UVar7 = 0;
  LVar6 = 1;
  pHVar1 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_88);
  Ogre::HardwareBuffer::lock((HardwareBuffer *)pHVar1,LVar6,UVar7);
  pHVar1 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_88);
  local_70 = Ogre::HardwarePixelBuffer::getCurrentLock(pHVar1);
  local_34 = *(undefined1 **)(local_70 + 0x18);
  FUN_00783590(local_30 + 0x98);
  *(float *)(local_30 + 0xb0) = *(float *)(local_30 + 0xa4) - *(float *)(local_30 + 0x98);
  *(float *)(local_30 + 0xb4) = *(float *)(local_30 + 0xa8) - *(float *)(local_30 + 0x9c);
  *(float *)(local_30 + 0xb8) = *(float *)(local_30 + 0xac) - *(float *)(local_30 + 0xa0);
  local_68 = *(float *)(local_30 + 0x98) * DAT_02cc50e4;
  local_78 = *(float *)(local_30 + 0xa0) * DAT_02cc50e4;
  local_80 = (*(float *)(local_30 + 0xb0) * DAT_02cc50e4) / (float)*(int *)(local_30 + 0x80);
  local_74 = (*(float *)(local_30 + 0xb8) * DAT_02cc50e4) / (float)*(int *)(local_30 + 0x84);
  local_5c = *(int *)(local_30 + 0x84);
  while (local_5c = local_5c + -1, -1 < local_5c) {
    for (local_50 = 0; local_50 < *(int *)(local_30 + 0x80); local_50 = local_50 + 1) {
      local_58 = (int)((float)local_50 * local_80 + local_68);
      local_54 = (int)((float)(local_50 + 1) * local_80 + local_68);
      local_4c = (int)((float)local_5c * local_74 + local_78);
      local_48 = (int)((float)(local_5c + 1) * local_74 + local_78);
      local_38 = local_4c;
      if (*(int *)(local_30 + 0xcc) == 0) {
        uStack_2c = 0;
        fStack_28 = 0.0;
        uStack_24 = 0;
        for (; local_38 < local_48; local_38 = local_38 + 1) {
          for (local_3c = local_58; local_3c < local_54; local_3c = local_3c + 1) {
            puVar4 = (ushort *)FUN_00492d60(local_3c,local_38);
            fStack_28 = (float)(*puVar4 & 0xfff) + fStack_28;
          }
        }
        local_40 = (&DAT_02cd9580)
                   [(int)((fStack_28 * 255.0) /
                         (float)((local_54 - local_58) * (local_48 - local_4c) * 0xfff)) & 0xff];
      }
      else {
        fStack_20 = 0.0;
        fStack_1c = 0.0;
        fStack_18 = 0.0;
        for (; local_38 < local_48; local_38 = local_38 + 1) {
          for (local_3c = local_58; local_3c < local_54; local_3c = local_3c + 1) {
            uVar2 = FUN_00780dc0(local_3c,local_38);
            puVar3 = (undefined2 *)FUN_00780fd0(local_8c,uVar2);
            local_5f = *puVar3;
            local_5d = *(byte *)(puVar3 + 1);
            local_44._0_1_ = (byte)local_5f;
            fStack_20 = (float)(byte)local_44 + fStack_20;
            local_44._1_1_ = (byte)((ushort)local_5f >> 8);
            fStack_1c = (float)local_44._1_1_ + fStack_1c;
            fStack_18 = (float)local_5d + fStack_18;
            local_44 = local_5f;
            local_42 = local_5d;
          }
        }
        local_64 = 1.0 / (float)((local_54 - local_58) * (local_48 - local_4c));
        fStack_20 = fStack_20 * local_64;
        fStack_1c = fStack_1c * local_64;
        fStack_18 = fStack_18 * local_64;
        local_40 = ((int)fStack_20 & 0xffU) << 0x10 | 0xff000000 | ((int)fStack_1c & 0xffU) << 8 |
                   (int)fStack_18 & 0xffU;
      }
      *local_34 = (undefined1)local_40;
      local_34[1] = (char)(local_40 >> 8);
      local_34[2] = (char)(local_40 >> 0x10);
      local_34[3] = 0xff;
      local_34 = local_34 + 4;
    }
    uVar5 = Ogre::PixelBox::getRowSkip(local_70);
    local_34 = local_34 + uVar5 * 4;
  }
  local_6c = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_88);
  (**(code **)(*(int *)local_6c + 0x10))();
  local_8 = 0xffffffff;
  Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr
            ((HardwarePixelBufferSharedPtr *)local_88);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

