/*
 * Entry: 0048b07d
 * Name: DistributedObject::UpdatePermState
 * Namespace: DistributedObject
 * Signature: void UpdatePermState(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::UpdatePermState(DistributedObject *this)

{
  MAT_3D MVar1;
  MAT_3D MVar2;
  uchar uVar3;
  byte bVar4;
  int iVar5;
  DistributedObject *pDVar6;
  int iVar7;
  REDUCED_MAT *pRVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 unaff_EDI;
  undefined4 *puVar11;
  char *pcVar12;
  undefined4 uStack_68;
  undefined1 in_stack_ffffff9c [24];
  undefined4 in_stack_ffffffb4;
  undefined4 in_stack_ffffffb8;
  undefined4 in_stack_ffffffbc;
  undefined4 in_stack_ffffffc0;
  undefined4 in_stack_ffffffc4;
  undefined4 in_stack_ffffffc8;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  REDUCED_MAT RStack_10;
  
  packet_buffer_length = 0;
  iVar5 = (**(code **)(this->_padding_ + 0x30))();
  if (iVar5 != 0) {
    uVar14 = *(undefined4 *)(iVar5 + 8);
    uVar13 = 0x48b0ac;
    uVar3 = encode_odf(*(long64 *)(iVar5 + 8));
    if (uVar3 == '\0') {
      if (GameObject::userObject == (GameObject *)0x0) {
        pDVar6 = (DistributedObject *)0x0;
      }
      else {
        pDVar6 = (DistributedObject *)&GameObject::userObject->_padding_;
      }
      iVar7 = (**(code **)this->_padding_)();
      if (iVar7 == 0) {
        pcVar12 = packet_buffer;
        for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
          pcVar12[0] = '\0';
          pcVar12[1] = '\0';
          pcVar12[2] = '\0';
          pcVar12[3] = '\0';
          pcVar12 = pcVar12 + 4;
        }
        bVar4 = (**(code **)(this->_padding_ + 4))();
        packet_buffer[1] = (bVar4 & 0xf | (this == pDVar6) << 5 | 0x10) << 2;
      }
      else {
        uVar15 = 0x48b18b;
        bVar4 = (**(code **)(this->_padding_ + 4))();
        packet_buffer[1] = (bVar4 & 0xf | (this == pDVar6) << 5) << 2;
        puVar10 = (undefined4 *)(iVar5 + 0x20);
        puVar11 = &uStack_68;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar11 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar11 = puVar11 + 1;
        }
        MVar2.front_x = (float)in_stack_ffffffb4;
        MVar2.right_x = (float)in_stack_ffffff9c._0_4_;
        MVar2.right_y = (float)in_stack_ffffff9c._4_4_;
        MVar2.right_z = (float)in_stack_ffffff9c._8_4_;
        MVar2.up_x = (float)in_stack_ffffff9c._12_4_;
        MVar2.up_y = (float)in_stack_ffffff9c._16_4_;
        MVar2.up_z = (float)in_stack_ffffff9c._20_4_;
        MVar2.front_y = (float)in_stack_ffffffb8;
        MVar2.front_z = (float)in_stack_ffffffbc;
        MVar2._36_4_ = in_stack_ffffffc0;
        MVar2.posit_x._0_4_ = in_stack_ffffffc4;
        MVar2.posit_x._4_4_ = in_stack_ffffffc8;
        MVar2.posit_y._0_4_ = uVar13;
        MVar2.posit_y._4_4_ = uVar14;
        MVar2.posit_z._0_4_ = uVar15;
        MVar2.posit_z._4_4_ = unaff_EDI;
        pRVar8 = NetUtil_ReduceMatrix(&RStack_10,MVar2);
        packet_buffer._6_2_ = (undefined2)*(undefined4 *)pRVar8->buf;
        packet_buffer._8_2_ = (undefined2)((uint)*(undefined4 *)pRVar8->buf >> 0x10);
        packet_buffer._10_2_ = (undefined2)*(undefined4 *)(pRVar8->buf + 4);
        packet_buffer._12_2_ = (undefined2)((uint)*(undefined4 *)(pRVar8->buf + 4) >> 0x10);
        packet_buffer._14_2_ = (undefined2)*(undefined4 *)(pRVar8->buf + 8);
        packet_buffer._16_2_ = (undefined2)((uint)*(undefined4 *)(pRVar8->buf + 8) >> 0x10);
        packet_buffer._18_2_ = *(undefined2 *)(pRVar8->buf + 0xc);
        packet_buffer._2_2_ = (undefined2)this->dwLocalID;
        packet_buffer._4_2_ = (undefined2)(this->dwLocalID >> 0x10);
        packet_buffer._20_4_ = *(undefined4 *)(iVar5 + 8);
        packet_buffer._24_4_ = *(undefined4 *)(iVar5 + 0xc);
      }
      uVar9 = 0;
      do {
        packet_buffer[uVar9 + 0x14] = packet_buffer[uVar9 + 0x14] & 0x7f;
        uVar9 = uVar9 + 1;
      } while (uVar9 < 8);
      uVar9 = 0x1c;
    }
    else {
      if (GameObject::userObject == (GameObject *)0x0) {
        pDVar6 = (DistributedObject *)0x0;
      }
      else {
        pDVar6 = (DistributedObject *)&GameObject::userObject->_padding_;
      }
      iVar7 = (**(code **)this->_padding_)();
      if (iVar7 == 0) {
        packet_buffer[0] = '\0';
        packet_buffer[1] = '\0';
        packet_buffer[2] = '\0';
        packet_buffer[3] = '\0';
        packet_buffer[4] = '\0';
        packet_buffer[5] = '\0';
        packet_buffer[6] = '\0';
        packet_buffer[7] = '\0';
        packet_buffer[8] = '\0';
        packet_buffer[9] = '\0';
        packet_buffer[10] = '\0';
        packet_buffer[0xb] = '\0';
        packet_buffer[0xc] = '\0';
        packet_buffer[0xd] = '\0';
        packet_buffer[0xe] = '\0';
        packet_buffer[0xf] = '\0';
        packet_buffer[0x10] = '\0';
        packet_buffer[0x11] = '\0';
        packet_buffer[0x12] = '\0';
        packet_buffer[0x13] = '\0';
        packet_buffer._20_4_ = packet_buffer._20_4_ & 0xffffff00;
        bVar4 = (**(code **)(this->_padding_ + 4))();
        packet_buffer[1] = (bVar4 & 0xf | (this == pDVar6) << 5 | 0x10) << 2;
      }
      else {
        uVar15 = 0x48b0e4;
        bVar4 = (**(code **)(this->_padding_ + 4))();
        packet_buffer[1] = (bVar4 & 0xf | (this == pDVar6) << 5) << 2;
        puVar10 = (undefined4 *)(iVar5 + 0x20);
        puVar11 = &uStack_68;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar11 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar11 = puVar11 + 1;
        }
        MVar1.front_x = (float)in_stack_ffffffb4;
        MVar1.right_x = (float)in_stack_ffffff9c._0_4_;
        MVar1.right_y = (float)in_stack_ffffff9c._4_4_;
        MVar1.right_z = (float)in_stack_ffffff9c._8_4_;
        MVar1.up_x = (float)in_stack_ffffff9c._12_4_;
        MVar1.up_y = (float)in_stack_ffffff9c._16_4_;
        MVar1.up_z = (float)in_stack_ffffff9c._20_4_;
        MVar1.front_y = (float)in_stack_ffffffb8;
        MVar1.front_z = (float)in_stack_ffffffbc;
        MVar1._36_4_ = in_stack_ffffffc0;
        MVar1.posit_x._0_4_ = in_stack_ffffffc4;
        MVar1.posit_x._4_4_ = in_stack_ffffffc8;
        MVar1.posit_y._0_4_ = uVar13;
        MVar1.posit_y._4_4_ = uVar14;
        MVar1.posit_z._0_4_ = uVar15;
        MVar1.posit_z._4_4_ = unaff_EDI;
        pRVar8 = NetUtil_ReduceMatrix(&RStack_10,MVar1);
        packet_buffer._6_2_ = (undefined2)*(undefined4 *)pRVar8->buf;
        packet_buffer._8_2_ = (undefined2)((uint)*(undefined4 *)pRVar8->buf >> 0x10);
        packet_buffer._10_2_ = (undefined2)*(undefined4 *)(pRVar8->buf + 4);
        packet_buffer._12_2_ = (undefined2)((uint)*(undefined4 *)(pRVar8->buf + 4) >> 0x10);
        packet_buffer._14_2_ = (undefined2)*(undefined4 *)(pRVar8->buf + 8);
        packet_buffer._16_2_ = (undefined2)((uint)*(undefined4 *)(pRVar8->buf + 8) >> 0x10);
        packet_buffer._18_2_ = *(undefined2 *)(pRVar8->buf + 0xc);
        packet_buffer._2_2_ = (undefined2)this->dwLocalID;
        packet_buffer._4_2_ = (undefined2)(this->dwLocalID >> 0x10);
        packet_buffer[0x14] = uVar3;
      }
      uVar9 = 0x15;
    }
    packet_buffer_length = uVar9;
    (**(code **)(this->_padding_ + 0x44))();
    packet_buffer[0] = (char)packet_buffer_length;
    if (((uVar9 < packet_buffer_length) && (dp != (dp_s *)0x0)) &&
       ((*(byte *)(iVar5 + 0x14) & 0x80) == 0)) {
      GetKeyForObject((DistributedObject *)packet_buffer);
      dpSetPlayerData();
    }
  }
  return;
}
