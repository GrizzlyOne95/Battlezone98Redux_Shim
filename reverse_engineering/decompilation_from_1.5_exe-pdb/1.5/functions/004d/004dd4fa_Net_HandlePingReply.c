/*
 * Entry: 004dd4fa
 * Name: Net::HandlePingReply
 * Namespace: Net
 * Signature: void HandlePingReply(Net * this, ushort param_1, PINGREPLY_PACKET * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
Net::HandlePingReply(Net *this,ushort param_1,PINGREPLY_PACKET *param_2,ulong param_3)

{
  uint uVar1;
  NetPlayer *pNVar2;
  PINGREPLY_PACKET *pPVar3;
  uint uVar4;
  ulong uVar5;
  PINGREPLY_PACKET *pPVar6;
  uint uVar7;
  uint uVar8;
  PINGREPLY_PACKET *pPVar9;
  bool bVar10;
  PINGREPLY_PACKET *local_20;
  PINGREPLY_PACKET *local_1c;
  NetPlayer *local_18;
  PINGREPLY_PACKET *local_14;
  uint local_10;
  PINGREPLY_PACKET *local_c;
  PINGREPLY_PACKET *local_8;
  
  pNVar2 = NetPlayer::Find(param_1);
  local_18 = pNVar2;
  if ((network_loggit != 0) && (fp == (_iobuf *)0x0)) {
    fp = (_iobuf *)fopen("j.log","w");
  }
  if (pNVar2 == (NetPlayer *)0x0) {
    return;
  }
  if ((param_2->master_send_time < pNVar2->dwNewestSendTime) && (network_loggit != 0)) {
    fprintf((FILE *)fp,"OLDTIMEPACKET: this one %lu, already one%lu\n",param_2->master_send_time,
            pNVar2->dwNewestSendTime);
    DisplayMessage("OLDTIMEPACKET: this one %lu, already one%lu\n");
  }
  pNVar2->dwNewestSendTime = param_2->master_send_time;
  local_8 = (PINGREPLY_PACKET *)NetPlayer::GetHistOffLow(pNVar2,(int *)&local_1c);
  pPVar3 = (PINGREPLY_PACKET *)NetPlayer::GetHistOffHigh(pNVar2,(int *)&local_20);
  uVar8 = param_2->master_send_time;
  uVar7 = uVar8;
  if (param_3 < uVar8) {
    uVar7 = param_3;
  }
  uVar1 = param_2->slave_received_time;
  uVar4 = (param_3 - uVar7 >> 1) + uVar7;
  if (uVar4 < uVar1) {
    uVar5 = uVar1 - uVar4;
  }
  else {
    uVar5 = uVar4 - uVar1;
  }
  local_10 = (uint)(uVar4 >= uVar1);
  if (param_3 < uVar8) {
    uVar8 = 0;
  }
  else {
    uVar8 = param_3 - uVar8;
  }
  if (uVar7 < uVar1) {
    local_c = (PINGREPLY_PACKET *)(uVar1 - uVar7);
  }
  else {
    local_c = (PINGREPLY_PACKET *)(uVar7 - uVar1);
  }
  _param_1 = (PINGREPLY_PACKET *)(uint)(uVar7 >= uVar1);
  bVar10 = param_3 < uVar1;
  if (bVar10) {
    param_3 = uVar1 - param_3;
  }
  else {
    param_3 = param_3 - uVar1;
  }
  local_14 = (PINGREPLY_PACKET *)(uint)!bVar10;
  if (network_loggit != 0) {
    fprintf((FILE *)fp,"NEW OFFSET: %lu, %d, %lu\n",uVar5,local_10,uVar8);
    fprintf((FILE *)fp,"NEW LOW HIGH: %lu, %lu\n",param_3,local_c);
    fprintf((FILE *)fp,"NEWSLOW HIGH: %d, %d\n",local_14,_param_1);
  }
  pNVar2 = local_18;
  NetPlayer::AddHist(local_18,uVar5,uVar8,local_10,param_3,(int)local_14,(ulong)local_c,
                     (int)_param_1);
  pPVar9 = local_1c;
  if (pNVar2->bClockInitialized != false) {
    pPVar6 = local_c;
    if ((local_20 == (PINGREPLY_PACKET *)0x0) && (_param_1 == (PINGREPLY_PACKET *)0x1)) {
LAB_004dd6c4:
      param_2 = _param_1;
      pPVar3 = local_c;
    }
    else {
      if (local_20 == (PINGREPLY_PACKET *)0x1) {
        if (_param_1 == (PINGREPLY_PACKET *)0x1) {
          if (pPVar3 <= local_c) goto LAB_004dd6c4;
          goto LAB_004dd6b1;
        }
      }
      else {
LAB_004dd6b1:
        if (((local_20 == (PINGREPLY_PACKET *)0x0) && (_param_1 == (PINGREPLY_PACKET *)0x0)) &&
           (local_c <= pPVar3)) goto LAB_004dd6c4;
      }
      if (local_1c == (PINGREPLY_PACKET *)0x1) {
        if (local_14 != (PINGREPLY_PACKET *)0x0) {
          if (local_14 != (PINGREPLY_PACKET *)0x1) goto LAB_004dd70a;
          if (local_8 < param_3) goto LAB_004dd6eb;
        }
      }
      else {
LAB_004dd6eb:
        if (((local_1c != (PINGREPLY_PACKET *)0x0) || (local_14 != (PINGREPLY_PACKET *)0x0)) ||
           (param_3 < local_8)) {
LAB_004dd70a:
          if ((local_20 == (PINGREPLY_PACKET *)0x0) && (local_1c == (PINGREPLY_PACKET *)0x1)) {
LAB_004dd732:
            param_2 = local_8;
            local_1c = local_20;
            local_20 = pPVar9;
            local_8 = pPVar3;
            if (pPVar9 == (PINGREPLY_PACKET *)0x0) {
LAB_004dd751:
              pPVar3 = param_2;
              pPVar9 = local_20;
              if (local_14 != (PINGREPLY_PACKET *)0x1) goto LAB_004dd755;
            }
            else {
LAB_004dd755:
              if (local_20 == (PINGREPLY_PACKET *)0x1) goto LAB_004dd759;
LAB_004dd765:
              if (((local_20 != (PINGREPLY_PACKET *)0x0) || (local_14 != (PINGREPLY_PACKET *)0x0))
                 || (pPVar3 = param_2, pPVar9 = (PINGREPLY_PACKET *)0x0, param_2 < param_3))
              goto LAB_004dd77d;
            }
          }
          else {
            param_2 = pPVar3;
            if (local_20 != (PINGREPLY_PACKET *)0x1) {
LAB_004dd722:
              if (local_20 == (PINGREPLY_PACKET *)0x0) {
                if ((local_1c == (PINGREPLY_PACKET *)0x0) && (local_8 < pPVar3)) goto LAB_004dd732;
                goto LAB_004dd751;
              }
              goto LAB_004dd755;
            }
            if (local_1c == (PINGREPLY_PACKET *)0x1) {
              if (pPVar3 < local_8) goto LAB_004dd732;
              goto LAB_004dd722;
            }
LAB_004dd759:
            if (local_14 == (PINGREPLY_PACKET *)0x1) {
              pPVar3 = param_2;
              pPVar9 = local_20;
              if (param_3 < param_2) goto LAB_004dd765;
            }
            else {
LAB_004dd77d:
              param_2 = local_14;
              pPVar3 = (PINGREPLY_PACKET *)param_3;
              pPVar9 = param_2;
            }
          }
          param_2 = pPVar9;
          if (local_1c == (PINGREPLY_PACKET *)0x1) {
            if (_param_1 != (PINGREPLY_PACKET *)0x0) {
              if (_param_1 != (PINGREPLY_PACKET *)0x1) goto LAB_004dd7b6;
              if (local_8 < local_c) goto LAB_004dd79a;
            }
          }
          else {
LAB_004dd79a:
            if (((local_1c != (PINGREPLY_PACKET *)0x0) || (_param_1 != (PINGREPLY_PACKET *)0x0)) ||
               (local_c < local_8)) goto LAB_004dd7b6;
          }
          pPVar6 = local_8;
          _param_1 = local_1c;
          goto LAB_004dd7b6;
        }
      }
      param_2 = local_14;
      pPVar6 = (PINGREPLY_PACKET *)param_3;
      pPVar3 = (PINGREPLY_PACKET *)param_3;
      _param_1 = local_14;
    }
LAB_004dd7b6:
    if (_param_1 == (PINGREPLY_PACKET *)0x1) {
      if (param_2 == (PINGREPLY_PACKET *)0x1) {
        uVar8 = (int)pPVar3 - (int)pPVar6;
        uVar5 = (int)&pPVar6->master_send_time + (uVar8 >> 1);
        local_10 = 1;
      }
      else {
LAB_004dd7e6:
        uVar8 = (int)&pPVar3->master_send_time + (int)&pPVar6->master_send_time;
        pPVar9 = pPVar6;
        if (pPVar6 <= pPVar3) {
          pPVar9 = pPVar3;
        }
        uVar5 = (int)pPVar9 - (uVar8 >> 1);
      }
    }
    else {
      if ((_param_1 != (PINGREPLY_PACKET *)0x0) || (param_2 != (PINGREPLY_PACKET *)0x0))
      goto LAB_004dd7e6;
      uVar8 = (int)pPVar6 - (int)pPVar3;
      uVar5 = (int)&pPVar3->master_send_time + (uVar8 >> 1);
      local_10 = 0;
    }
    pNVar2 = local_18;
    if (network_loggit == 0) goto LAB_004dd855;
    fprintf((FILE *)fp,"HIS LOW HIGH: %lu, %lu\n",pPVar3,pPVar6);
    fprintf((FILE *)fp,"HISSLOW HIGH: %d, %d\n",param_2,_param_1);
    pNVar2 = local_18;
  }
  if (network_loggit != 0) {
    fprintf((FILE *)fp,"SAVE OFFSET: %lu, %d, %lu\n",uVar5,local_10,uVar8);
  }
LAB_004dd855:
  NetPlayer::SetOffset(pNVar2,uVar5);
  NetPlayer::SetAddOffset(pNVar2,local_10);
  NetPlayer::SetDelay(pNVar2,uVar8);
  pNVar2->dwPingReplies = pNVar2->dwPingReplies | 1;
  pNVar2->bClockInitialized = true;
  return;
}
