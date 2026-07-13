/*
 * Entry: 004ddd94
 * Name: Net::AdjustBandwidth
 * Namespace: Net
 * Signature: void AdjustBandwidth(Net * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall Net::AdjustBandwidth(Net *this)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  DWORD DVar4;
  uint uVar5;
  undefined4 unaff_EDI;
  uint local_24;
  Net *local_20;
  undefined2 local_1c;
  ulong local_1a;
  undefined1 local_16;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (hosting) {
    uVar5 = 0;
    local_20 = this;
    uVar2 = NetPlayer_GetFirstPlayer((char **)0x0,(ulong *)0x0,(ulong *)0x0,&local_24);
    while (uVar2 != 0xfa01) {
      if (uVar5 < local_24) {
        uVar5 = local_24;
      }
      uVar2 = NetPlayer_GetNextPlayer((char **)0x0,(ulong *)0x0,(ulong *)0x0,&local_24);
    }
    bVar1 = IsHost((ushort)unaff_EDI);
    if (bVar1) {
      uVar3 = uVar5 / (uint)DivisorPing2NPPI;
      if (LimitHiNPPI < (int)(uVar5 / (uint)DivisorPing2NPPI)) {
        uVar3 = LimitHiNPPI;
      }
      if ((int)uVar3 < LimitLowNPPI) {
        uVar3 = LimitLowNPPI;
      }
      NextPositionPacketInterval = uVar3 & 0xfffffffc;
      MaxPositionPacketInterval = NextPositionPacketInterval;
    }
    if (uVar5 != 0) {
      DVar4 = Get_TimeNow();
      if ((network_loggit != 0) && (local_20->dwLastBandWidthSendTime + 1000 < DVar4)) {
        DisplayMessage("Bandwidth = %lu");
      }
      if (uVar5 < (uint)MaxPing) {
        if (local_20->dwLastBandWidthSendTime + 1000 < DVar4) {
          dwBandwidth = dwBandwidth + UpCount;
        }
      }
      else {
        dwBandwidth = dwBandwidth - 1;
      }
      if (dwBandwidth < dwMinBandwidth) {
        dwBandwidth = dwMinBandwidth;
      }
      if (dwMaxBandwidth < dwBandwidth) {
        dwBandwidth = dwMaxBandwidth;
      }
      if (local_20->dwLastBandWidthSendTime + 2000 < DVar4) {
        local_1c = 0x4250;
        local_16 = (undefined1)
                   ((int)(NextPositionPacketInterval + (NextPositionPacketInterval >> 0x1f & 3U)) >>
                   2);
        if ((ushort)_myPlayerID != 0xfa01) {
          local_1a = dwBandwidth;
          Send(dp,(ushort)_myPlayerID,0,0,&local_1c,10);
          local_20->dwLastBandWidthSendTime = DVar4;
        }
      }
    }
  }
  return;
}
