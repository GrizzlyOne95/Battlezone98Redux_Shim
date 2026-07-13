/*
 * Entry: 004ddcc6
 * Name: Net_CanBroadCastOrdnance
 * Namespace: Global
 * Signature: int Net_CanBroadCastOrdnance(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Net_CanBroadCastOrdnance(uint param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  DWORD DVar4;
  int iVar5;
  undefined1 local_24 [4];
  int local_20;
  float local_8;
  
  if (Net::dp != (dp_s *)0x0) {
    DVar4 = Get_TimeNow();
    local_8 = (float)(int)(DVar4 - Net::dwLastByteSentTime);
    if ((int)(DVar4 - Net::dwLastByteSentTime) < 0) {
      local_8 = local_8 + 4.2949673e+09;
    }
    local_8 = local_8 * 0.001;
    if (local_8 == 0.0) {
      local_8 = 0.001;
    }
    iVar5 = dpNumPlayers(Net::dp);
    dpGetStats(Net::dp,6,local_24,0x18);
    fVar1 = (float)(int)Net::dwLastByteSentCount;
    if ((int)Net::dwLastByteSentCount < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    iVar5 = (iVar5 + -1) * param_1;
    fVar3 = (float)iVar5;
    if (iVar5 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    fVar2 = (float)(int)Net::dwBandwidth;
    if ((int)Net::dwBandwidth < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    if ((fVar3 + ((float)local_20 - fVar1)) / local_8 <= fVar2) {
      return 1;
    }
  }
  return 0;
}
