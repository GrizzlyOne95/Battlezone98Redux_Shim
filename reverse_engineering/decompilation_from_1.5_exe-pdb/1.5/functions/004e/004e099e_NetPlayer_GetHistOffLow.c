/*
 * Entry: 004e099e
 * Name: NetPlayer::GetHistOffLow
 * Namespace: NetPlayer
 * Signature: ulong GetHistOffLow(NetPlayer * this, int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __thiscall NetPlayer::GetHistOffLow(NetPlayer *this,int *param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = this->iHistQueueSize;
  iVar5 = 1;
  uVar1 = 0;
  if (0 < iVar4) {
    uVar1 = this->hist[0].dwOffLow;
    iVar5 = this->hist[0].BAddOffLow;
    if (1 < iVar4) {
      piVar2 = &this->hist[1].BAddOffLow;
      iVar4 = iVar4 + -1;
      do {
        if ((iVar5 == 0) && (iVar3 = 1, *piVar2 == 1)) {
LAB_004e09f3:
          uVar1 = piVar2[-1];
          iVar5 = iVar3;
        }
        else if (iVar5 == 1) {
          if (*piVar2 == 1) {
            iVar3 = 1;
            if (uVar1 < (uint)piVar2[-1]) goto LAB_004e09f3;
            goto LAB_004e09e4;
          }
        }
        else {
LAB_004e09e4:
          if (((iVar5 == 0) && (*piVar2 == 0)) && (iVar3 = 0, (uint)piVar2[-1] < uVar1))
          goto LAB_004e09f3;
        }
        piVar2 = piVar2 + 7;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  *param_1 = iVar5;
  return uVar1;
}
