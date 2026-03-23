
void __fastcall FUN_00678cd0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  uint uVar4;
  undefined4 uVar5;
  code *pcVar6;
  uint uStack_114;
  undefined1 local_104 [4];
  undefined1 local_100 [4];
  undefined1 local_fc [4];
  HardwareIndexBuffer *local_f8;
  HardwareVertexBuffer *local_f4;
  SharedPtr<class_Ogre::HardwareIndexBuffer> *local_f0;
  undefined4 local_e8;
  HardwareIndexBuffer *local_e4;
  SharedPtr<class_Ogre::HardwareVertexBuffer> *local_e0;
  SharedPtr<class_Ogre::HardwareIndexBuffer> *local_dc;
  SharedPtr<class_Ogre::HardwareIndexBuffer> *local_d8;
  HardwareVertexBuffer *local_d4;
  HardwareVertexBuffer *local_d0;
  SharedPtr<class_Ogre::HardwareVertexBuffer> *local_cc;
  undefined4 local_c8;
  int local_c4;
  void *local_c0;
  void *local_bc;
  HardwareIndexBuffer *local_b8;
  int *local_b4;
  HardwareIndexBuffer *local_b0;
  int *local_ac;
  void *local_a8;
  int *local_a4;
  SharedPtr<class_Ogre::HardwareVertexBuffer> *local_a0;
  HardwareIndexBufferSharedPtr *local_9c;
  SharedPtr<class_Ogre::HardwareVertexBuffer> *local_98;
  int *local_94;
  int *local_90;
  void *local_8c;
  void *local_88;
  void *local_84;
  SharedPtr<class_Ogre::HardwareIndexBuffer> *local_80;
  int *local_7c;
  HardwareVertexBuffer *local_78;
  int *local_74;
  undefined4 local_70;
  void *local_6c;
  undefined4 local_68;
  HardwareIndexBuffer *local_64;
  HardwareIndexBuffer *local_60;
  HardwareVertexBuffer *local_5c;
  HardwareVertexBuffer *local_58;
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  void *local_4c;
  void *local_48;
  short local_44;
  undefined1 local_40 [4];
  uint local_3c;
  char local_38;
  char local_37;
  char local_36;
  char local_35;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  int local_28;
  int local_24;
  int local_20;
  int *local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f350;
  local_10 = ExceptionList;
  uStack_114 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_114;
  ExceptionList = &local_10;
  local_18 = param_1;
  if (*(char *)(param_1 + 0x1dc) != '\0') {
    local_14 = (undefined1 *)&uStack_114;
    FUN_007d6b70("DynamicGeometry: prepare for submit when already prepared\n");
    FUN_00679550();
    return;
  }
  if (*(char *)(param_1 + 0xd8) == '\0') {
    local_14 = (undefined1 *)&uStack_114;
    FUN_00679550();
    return;
  }
  FUN_0041ff50();
  cVar1 = FUN_0041fc90();
  if (cVar1 != '\0') {
    FUN_00679550();
    return;
  }
  pcVar6 = FUN_00678950;
  puVar2 = (undefined4 *)FID_conflict_end(local_fc);
  uVar5 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_100);
  FUN_0067b9d0(*puVar2,uVar5,pcVar6);
  FID_conflict_begin(&local_34);
  FID_conflict_end(local_50);
  while (cVar1 = FID_conflict_operator__(local_50), cVar1 != '\0') {
    piVar3 = (int *)FUN_00421ec0();
    if (*(char *)(*piVar3 + 0x31) == '\0') {
      FUN_0046b260(&local_70,0);
      while ((cVar1 = FID_conflict_operator__(local_50), cVar1 != '\0' &&
             (piVar3 = (int *)FUN_00421ec0(), *(char *)(*piVar3 + 0x31) == '\0'))) {
        FUN_00421ee0();
      }
      local_c8 = local_34;
      FUN_0067b9d0(local_70,local_34,FUN_00678b40);
    }
    else {
      FUN_00421ee0();
    }
  }
  local_8 = 0;
  local_30 = 0;
  uVar4 = FUN_0067ac40();
  if (uVar4 <= local_30) {
    FUN_006781e0();
  }
  local_e0 = (SharedPtr<class_Ogre::HardwareVertexBuffer> *)FUN_0067ac60(local_30);
  local_78 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->(local_e0);
  local_c0 = Ogre::HardwareBuffer::lock((HardwareBuffer *)local_78,1,0);
  local_28 = 0;
  local_2c = 0;
  local_48 = local_c0;
  uVar4 = FUN_0067ac40();
  if (uVar4 <= local_2c) {
    FUN_00678310();
  }
  local_80 = (SharedPtr<class_Ogre::HardwareIndexBuffer> *)FUN_0067ac60(local_2c);
  local_f8 = Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::operator->(local_80);
  local_88 = Ogre::HardwareBuffer::lock((HardwareBuffer *)local_f8,1,0);
  local_24 = 0;
  local_4c = local_88;
  FID_conflict_begin(local_40);
  FID_conflict_end(local_54);
  do {
    do {
      do {
        local_36 = FID_conflict_operator__(local_54);
        if (local_36 == '\0') {
          local_cc = (SharedPtr<class_Ogre::HardwareVertexBuffer> *)FUN_0067ac60(local_30);
          local_d4 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->(local_cc);
          local_5c = local_d4;
          (**(code **)(*(int *)local_d4 + 0x10))();
          local_dc = (SharedPtr<class_Ogre::HardwareIndexBuffer> *)FUN_0067ac60(local_2c);
          local_e4 = Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::operator->(local_dc);
          local_64 = local_e4;
          (**(code **)(*(int *)local_e4 + 0x10))();
          *(undefined1 *)(local_18 + 0x1dc) = 1;
          FUN_00679540();
          return;
        }
        local_68 = FUN_0046b260(local_104,0);
        local_90 = (int *)FUN_00421ec0();
        local_1c = (int *)*local_90;
      } while (local_1c[0x16] == 0);
      local_e8 = (**(code **)(*local_1c + 4))();
      local_35 = FUN_004c85a0();
    } while (local_35 != '\0');
    if ((0x10000 < (uint)(local_28 + local_1c[0x16])) ||
       (0x18000 < (uint)(local_24 + local_1c[0x22]))) {
      local_98 = (SharedPtr<class_Ogre::HardwareVertexBuffer> *)FUN_0067ac60(local_30);
      local_d0 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->(local_98);
      local_58 = local_d0;
      (**(code **)(*(int *)local_d0 + 0x10))();
      local_30 = local_30 + 1;
      uVar4 = FUN_0067ac40();
      if (uVar4 <= local_30) {
        FUN_006781e0();
      }
      local_a0 = (SharedPtr<class_Ogre::HardwareVertexBuffer> *)FUN_0067ac60(local_30);
      local_f4 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->(local_a0);
      local_a8 = Ogre::HardwareBuffer::lock((HardwareBuffer *)local_f4,1,0);
      local_28 = 0;
      local_48 = local_a8;
      local_d8 = (SharedPtr<class_Ogre::HardwareIndexBuffer> *)FUN_0067ac60(local_2c);
      local_b0 = Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::operator->(local_d8);
      local_60 = local_b0;
      (**(code **)(*(int *)local_b0 + 0x10))();
      local_2c = local_2c + 1;
      uVar4 = FUN_0067ac40();
      if (uVar4 <= local_2c) {
        FUN_00678310();
      }
      local_f0 = (SharedPtr<class_Ogre::HardwareIndexBuffer> *)FUN_0067ac60(local_2c);
      local_b8 = Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::operator->(local_f0);
      local_6c = Ogre::HardwareBuffer::lock((HardwareBuffer *)local_b8,1,0);
      local_24 = 0;
      local_4c = local_6c;
    }
    local_74 = (int *)FUN_004200d0(local_1c[0x1e]);
    local_84 = (void *)(local_1c[0x15] * *(int *)(local_18 + 0x14c) + *local_74);
    local_7c = (int *)FUN_004200d0(local_1c[0x23]);
    local_8c = (void *)(*local_7c + local_1c[0x21] * 2);
    memcpy((void *)(local_28 * *(int *)(local_18 + 0x14c) + (int)local_48),local_84,
           local_1c[0x16] * *(int *)(local_18 + 0x14c));
    memcpy((void *)((int)local_4c + local_24 * 2),local_8c,local_1c[0x22] << 1);
    local_94 = (int *)FUN_004200d0(local_30);
    local_1c[0x13] = *local_94;
    local_1c[0x15] = local_28;
    local_9c = (HardwareIndexBufferSharedPtr *)FUN_0067ac60(local_2c);
    Ogre::HardwareIndexBufferSharedPtr::operator=
              ((HardwareIndexBufferSharedPtr *)(local_1c + 0x1f),local_9c);
    local_1c[0x21] = local_24;
    local_28 = local_28 + local_1c[0x16];
    local_24 = local_24 + local_1c[0x22];
    if ((char)local_1c[0xc] != '\0') {
      while (local_38 = FID_conflict_operator__(local_54), local_38 != '\0') {
        local_a4 = (int *)FUN_00421ec0();
        local_20 = *local_a4;
        if (*(int *)(local_20 + 0x58) != 0) {
          local_37 = FUN_00677a80(local_1c,local_20);
          if (((local_37 == '\0') || (0x10000 < (uint)(local_28 + *(int *)(local_20 + 0x58)))) ||
             (0x18000 < (uint)(local_24 + *(int *)(local_20 + 0x88)))) break;
          local_ac = (int *)FUN_004200d0(*(undefined4 *)(local_20 + 0x78));
          local_bc = (void *)(*(int *)(local_20 + 0x54) * *(int *)(local_18 + 0x14c) + *local_ac);
          local_b4 = (int *)FUN_004200d0(*(undefined4 *)(local_20 + 0x8c));
          local_c4 = *local_b4 + *(int *)(local_20 + 0x84) * 2;
          memcpy((void *)(local_28 * *(int *)(local_18 + 0x14c) + (int)local_48),local_bc,
                 *(int *)(local_20 + 0x58) * *(int *)(local_18 + 0x14c));
          local_44 = (short)local_1c[0x16];
          for (local_3c = 0; local_3c < *(uint *)(local_20 + 0x88); local_3c = local_3c + 1) {
            *(short *)((int)local_4c + (local_24 + local_3c) * 2) =
                 *(short *)(local_c4 + local_3c * 2) + local_44;
          }
          local_28 = local_28 + *(int *)(local_20 + 0x58);
          local_24 = local_24 + *(int *)(local_20 + 0x88);
          local_1c[0x16] = local_1c[0x16] + *(int *)(local_20 + 0x58);
          local_1c[0x22] = local_1c[0x22] + *(int *)(local_20 + 0x88);
        }
        FUN_00421ee0();
      }
    }
    FUN_0041fe40(&local_1c);
  } while( true );
}

