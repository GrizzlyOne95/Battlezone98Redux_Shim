/*
 * Entry: 0048dd5f
 * Name: DistributedObject::TempStateSendAll
 * Namespace: DistributedObject
 * Signature: void TempStateSendAll(_ToBeSent * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DistributedObject::TempStateSendAll(_ToBeSent *param_1,int param_2)

{
  _ToBeSent *p_Var1;
  MAT_3D MVar2;
  float fVar3;
  byte bVar4;
  DWORD DVar5;
  BASE_STRUCT *pBVar6;
  int iVar7;
  REDUCED_MAT *pRVar8;
  byte *pbVar9;
  int extraout_EAX;
  ulong uVar10;
  int iVar11;
  char *pcVar12;
  uint uVar13;
  int *piVar14;
  undefined4 *puVar15;
  char *pcVar16;
  dp_s *unaff_EDI;
  undefined4 *puVar17;
  char *pcVar18;
  float10 fVar19;
  float fVar20;
  undefined4 uStack_ca4;
  undefined1 in_stack_fffff360 [36];
  undefined4 in_stack_fffff384;
  char *in_stack_fffff388;
  undefined4 in_stack_fffff38c;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  REDUCED_MAT local_c58;
  int local_c48;
  GameObject *local_c44;
  _ToBeSent *local_c40;
  int local_c3c;
  char *local_c38;
  char *local_c34;
  char *local_c30;
  float local_c2c;
  char *local_c28;
  uchar local_c21;
  int local_c20;
  uint local_c1c;
  char *local_c18;
  int *local_c14;
  char *local_c10;
  int local_c0c;
  uchar local_c08 [48];
  undefined1 local_bd8 [2000];
  char local_408;
  char local_407 [4];
  char cStack_403;
  uchar local_402 [1018];
  uint local_8;
  
  uVar10 = Net::dwLastByteSentCount;
  local_8 = __security_cookie ^ (uint)local_bd8;
  local_c40 = param_1;
  local_c38 = (char *)Net::dwLastByteSentCount;
  local_c1c = dpNumPlayers();
  if ((int)local_c1c < 1) {
    local_c1c = 1;
  }
  local_c1c = local_c1c - 1;
  DVar5 = Get_TimeNow();
  local_c14 = (int *)(DVar5 - Net::dwLastByteSentTime);
  local_c2c = (float)(int)local_c14;
  if ((int)local_c14 < 0) {
    local_c2c = local_c2c + 4.2949673e+09;
  }
  local_c2c = local_c2c * 0.001;
  if (local_c2c == 0.0) {
    local_c2c = 0.001;
  }
  if ((BOrdnanceLength & 1) != 0) {
    BOrdnanceLength = BOrdnanceLength + '\x01';
  }
  packet_buffer[0] = '_';
  packet_buffer[1] = BOrdnanceLength;
  fVar20 = Get_Time();
  packet_buffer._2_3_ = SUB43(fVar20,0);
  packet_buffer[5] = (char)((uint)fVar20 >> 0x18);
  local_c10 = (char *)0x0;
  pcVar12 = packet_buffer + 6;
  if (BOrdnanceLength != '\0') {
    uVar13 = (uint)BOrdnanceLength;
    in_stack_fffff38c = 0x48de33;
    memcpy();
    pcVar12 = packet_buffer + uVar13 + 6;
    BOrdnanceLength = '\0';
  }
  local_c34 = (char *)GetTotalBytesSent(unaff_EDI);
  if (local_c34 < uVar10) {
    local_c38 = local_c34;
  }
  if (send_it_anyways == 0) {
    local_c14 = (int *)(local_c34 + -(int)local_c38);
    fVar20 = (float)(int)local_c14;
    if ((int)local_c14 < 0) {
      fVar20 = fVar20 + 4.2949673e+09;
    }
    fVar3 = (float)(int)Net::dwBandwidth;
    if ((int)Net::dwBandwidth < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    if ((fVar3 < fVar20 / local_c2c) || ((int)(DVar5 - Net::NextPositionPacketSendTime) < 0))
    goto LAB_0048e389;
    Net::NextPositionPacketSendTime = Net::NextPositionPacketInterval + DVar5;
  }
  tempstate_packets = 0;
  tempstate_objects = 0;
  tempstate_uncompressed = 0;
  tempstate_compressed = 0;
  if (queuedState._Mysize != 0) {
    local_c18 = pcVar12 + -0xa1146a;
    do {
      if ((char *)0xf8 < local_c18) break;
      pBVar6 = std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::front(&queuedState);
      local_c18 = local_c18 + 6;
      *(undefined4 *)pcVar12 = *(undefined4 *)pBVar6;
      *(undefined2 *)(pcVar12 + 4) = *(undefined2 *)((int)&pBVar6->dwLocalID + 2);
      pcVar12 = pcVar12 + 6;
      std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::pop_front(&queuedState);
    } while (queuedState._Mysize != 0);
  }
  local_c3c = 0;
  local_c0c = 0;
  if (0 < param_2) {
    do {
      local_c44 = local_c40[local_c0c].g;
      if (local_c44 == (GameObject *)0x0) break;
      piVar14 = &local_c44->_padding_;
      local_c14 = piVar14;
      iVar7 = (**(code **)(*piVar14 + 0x30))();
      uVar22 = *(undefined4 *)(iVar7 + 8);
      uVar21 = 0x48df57;
      local_c48 = iVar7;
      local_c21 = encode_odf(*(long64 *)(iVar7 + 8));
      if (local_c21 == '\0') {
        local_c30 = pcVar12 + 0x1c;
        local_c20 = 0x1c;
      }
      else {
        local_c30 = pcVar12 + 0x15;
        local_c20 = 0x15;
      }
      local_c28 = (char *)(uint)(local_c44 == GameObject::userObject);
      uVar23 = 0x48df90;
      (**(code **)*piVar14)();
      if ((*(uint *)(iVar7 + 0x14) & 0x200) == 0) {
        uVar23 = 0x48dfbc;
        bVar4 = (**(code **)(*piVar14 + 4))();
        pcVar12[1] = (bVar4 & 0xf | (char)local_c28 << 5) << 2;
      }
      else {
        if ((*(uint *)(iVar7 + 0x14) & 0x1000000) == 0) {
          bVar4 = (char)local_c28 << 7 | 1;
        }
        else {
          bVar4 = (char)local_c28 << 7 | 5;
        }
        pcVar12[1] = bVar4;
      }
      puVar15 = (undefined4 *)(iVar7 + 0x20);
      puVar17 = &uStack_ca4;
      for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
        *puVar17 = *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
      }
      MVar2._36_4_ = in_stack_fffff384;
      MVar2.right_x = (float)in_stack_fffff360._0_4_;
      MVar2.right_y = (float)in_stack_fffff360._4_4_;
      MVar2.right_z = (float)in_stack_fffff360._8_4_;
      MVar2.up_x = (float)in_stack_fffff360._12_4_;
      MVar2.up_y = (float)in_stack_fffff360._16_4_;
      MVar2.up_z = (float)in_stack_fffff360._20_4_;
      MVar2.front_x = (float)in_stack_fffff360._24_4_;
      MVar2.front_y = (float)in_stack_fffff360._28_4_;
      MVar2.front_z = (float)in_stack_fffff360._32_4_;
      MVar2.posit_x._0_4_ = in_stack_fffff388;
      MVar2.posit_x._4_4_ = in_stack_fffff38c;
      MVar2.posit_y._0_4_ = uVar21;
      MVar2.posit_y._4_4_ = uVar22;
      MVar2.posit_z._0_4_ = uVar23;
      MVar2.posit_z._4_4_ = unaff_EDI;
      pRVar8 = NetUtil_ReduceMatrix(&local_c58,MVar2);
      *(undefined4 *)(pcVar12 + 6) = *(undefined4 *)pRVar8->buf;
      *(undefined4 *)(pcVar12 + 10) = *(undefined4 *)(pRVar8->buf + 4);
      *(undefined4 *)(pcVar12 + 0xe) = *(undefined4 *)(pRVar8->buf + 8);
      *(undefined2 *)(pcVar12 + 0x12) = *(undefined2 *)(pRVar8->buf + 0xc);
      *(int *)(pcVar12 + 2) = local_c44->_padding_;
      if (local_c21 == '\0') {
        pbVar9 = (byte *)(pcVar12 + 0x14);
        *(undefined4 *)pbVar9 = *(undefined4 *)(local_c48 + 8);
        *(undefined4 *)(pcVar12 + 0x18) = *(undefined4 *)(local_c48 + 0xc);
        iVar7 = 8;
        do {
          *pbVar9 = *pbVar9 & 0x7f;
          pbVar9 = pbVar9 + 1;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      else {
        pcVar12[0x14] = local_c21;
      }
      if ((*(uint *)(local_c48 + 0x14) & 0x200) == 0) {
        (**(code **)(*local_c14 + 0x3c))();
      }
      pcVar16 = pcVar12 + -0xa11470;
      *pcVar12 = (char)local_c20;
      if ((int)local_c1c < 1) {
LAB_0048e083:
        local_c28 = (char *)0xf9;
      }
      else {
        _ftol2();
        local_c28 = (char *)((uint)(local_c38 + (extraout_EAX - (int)local_c34)) / local_c1c);
        if ((char *)0xf9 < local_c28) goto LAB_0048e083;
      }
      if (local_c28 < pcVar16 + local_c20) {
        local_c30 = packet_buffer;
        if (Net::bUseCompression != 0) {
          pcVar18 = pcVar12 + -0xa11476;
          in_stack_fffff388 = packet_buffer + 6;
          in_stack_fffff384 = 0x48e0c9;
          iVar7 = lzo1x_999_compress((uchar *)(packet_buffer + 6),(ulong)(pcVar18 + local_c20),
                                     local_c08,(ulong *)&local_c18,wrk);
          if (((iVar7 == 0) && (local_c18 < pcVar18 + local_c20)) && (local_c18 < local_c28 + -6)) {
            in_stack_fffff38c = 0x48e0f8;
            memcpy();
            local_c10 = local_c18;
            goto LAB_0048e254;
          }
          if (local_c10 == (char *)0x0) {
            in_stack_fffff388 = packet_buffer + 6;
            in_stack_fffff384 = 0x48e128;
            iVar7 = lzo1x_999_compress((uchar *)(packet_buffer + 6),(ulong)pcVar18,local_402,
                                       (ulong *)&local_c10,wrk);
            if ((iVar7 != 0) || (pcVar18 <= local_c10)) goto LAB_0048e157;
          }
          local_408 = '*';
          local_407[0] = packet_buffer[1];
          local_407[1] = packet_buffer[2];
          local_407[2] = packet_buffer[3];
          local_407[3] = packet_buffer[4];
          cStack_403 = packet_buffer[5];
          local_c30 = &local_408;
          pcVar16 = local_c10 + 6;
        }
LAB_0048e157:
        memcpy();
        local_c34 = (char *)GetTotalBytesSent(unaff_EDI);
        local_c14 = (int *)(local_c34 + ((int)pcVar16 * local_c1c - (int)local_c38));
        fVar20 = (float)(int)local_c14;
        if ((int)local_c14 < 0) {
          fVar20 = fVar20 + 4.2949673e+09;
        }
        fVar3 = (float)(int)Net::dwBandwidth;
        if ((int)Net::dwBandwidth < 0) {
          fVar3 = fVar3 + 4.2949673e+09;
        }
        if (((fVar3 < fVar20 / local_c2c) && (send_it_anyways == 0)) ||
           (iVar7 = SendBuf(local_c30,(int)pcVar16), iVar7 != 0)) goto LAB_0048e389;
        tempstate_packets = tempstate_packets + 1;
        tempstate_compressed = tempstate_compressed + (int)pcVar16;
        tempstate_objects = tempstate_objects + 1 + (local_c0c - local_c3c);
        tempstate_uncompressed = (int)pcVar12 + tempstate_uncompressed + -0xa11470;
        for (iVar7 = local_c3c; iVar7 <= local_c0c; iVar7 = iVar7 + 1) {
          p_Var1 = local_c40 + iVar7;
          fVar20 = Get_TimeLocal();
          p_Var1->g->_padding_ = (int)fVar20;
          fVar19 = (float10)(**(code **)(p_Var1->g->_padding_ + 0x1c))();
          p_Var1->g->_padding_ = (int)(float)fVar19;
        }
        local_c3c = local_c0c + 1;
        pcVar12 = packet_buffer + 6;
        packet_buffer._1_4_ = packet_buffer._1_4_ & 0xffffff00;
        in_stack_fffff38c = 0x48e24d;
        memcpy();
        local_c10 = (char *)0x0;
      }
LAB_0048e254:
      pcVar12 = pcVar12 + local_c20;
      local_c0c = local_c0c + 1;
    } while (local_c0c < param_2);
  }
  pcVar16 = pcVar12 + -0xa11470;
  local_c34 = packet_buffer;
  if ((char *)0x6 < pcVar16) {
    if ((Net::bUseCompression != 0) &&
       ((local_c10 != (char *)0x0 ||
        ((iVar7 = lzo1x_999_compress((uchar *)(packet_buffer + 6),(ulong)(pcVar12 + -0xa11476),
                                     local_402,(ulong *)&local_c10,wrk), iVar7 == 0 &&
         (local_c10 < pcVar12 + -0xa11476)))))) {
      local_408 = '*';
      local_407[0] = packet_buffer[1];
      local_407[1] = packet_buffer[2];
      local_407[2] = packet_buffer[3];
      local_407[3] = packet_buffer[4];
      cStack_403 = packet_buffer[5];
      local_c34 = &local_408;
      pcVar16 = local_c10 + 6;
    }
    uVar10 = GetTotalBytesSent(unaff_EDI);
    local_c14 = (int *)(uVar10 + ((int)pcVar16 * local_c1c - (int)local_c38));
    fVar20 = (float)(int)local_c14;
    if ((int)local_c14 < 0) {
      fVar20 = fVar20 + 4.2949673e+09;
    }
    fVar3 = (float)(int)Net::dwBandwidth;
    if ((int)Net::dwBandwidth < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    if (((fVar20 / local_c2c <= fVar3) || (send_it_anyways != 0)) &&
       (iVar7 = SendBuf(local_c34,(int)pcVar16), iVar7 == 0)) {
      tempstate_packets = tempstate_packets + 1;
      tempstate_compressed = tempstate_compressed + (int)pcVar16;
      tempstate_objects = tempstate_objects + (local_c0c - local_c3c);
      tempstate_uncompressed = (int)pcVar12 + tempstate_uncompressed + -0xa11470;
      for (iVar7 = local_c3c; iVar7 < local_c0c; iVar7 = iVar7 + 1) {
        p_Var1 = local_c40 + iVar7;
        fVar20 = Get_TimeLocal();
        p_Var1->g->_padding_ = (int)fVar20;
        fVar19 = (float10)(**(code **)(p_Var1->g->_padding_ + 0x1c))();
        p_Var1->g->_padding_ = (int)(float)fVar19;
      }
    }
  }
LAB_0048e389:
  Ordnance_Sent(0);
  return;
}
