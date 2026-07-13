/*
 * Entry: 004dd48b
 * Name: Net::HandleBandwidth
 * Namespace: Net
 * Signature: void HandleBandwidth(Net * this, BANDWIDTH_PACKET * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::HandleBandwidth(Net *this,BANDWIDTH_PACKET *param_1,int param_2)

{
  int iVar1;
  
  dwBandwidth = param_1->dwBandwidth;
  if (7 < (uint)param_2) {
    NextPositionPacketInterval = (uint)param_1->packetInterval4ms * 4;
    if (LimitHiNPPI < NextPositionPacketInterval) {
      NextPositionPacketInterval = LimitHiNPPI;
    }
    if (LimitLowNPPI <= NextPositionPacketInterval) goto LAB_004dd4d7;
  }
  NextPositionPacketInterval = LimitLowNPPI;
LAB_004dd4d7:
  iVar1 = MaxPositionPacketInterval / DivisorMPPI2NPPI;
  if ((NextPositionPacketInterval < iVar1) &&
     (NextPositionPacketInterval = iVar1, LimitHiNPPI < iVar1)) {
    NextPositionPacketInterval = LimitHiNPPI;
  }
  return;
}
