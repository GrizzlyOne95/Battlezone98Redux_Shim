/*
 * Entry: 004e0a74
 * Name: NetPlayer::AddHist
 * Namespace: NetPlayer
 * Signature: void AddHist(NetPlayer * this, ulong param_1, ulong param_2, int param_3, ulong param_4, int param_5, ulong param_6, int param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
NetPlayer::AddHist(NetPlayer *this,ulong param_1,ulong param_2,int param_3,ulong param_4,int param_5
                  ,ulong param_6,int param_7)

{
  int iVar1;
  
  this->hist[this->iHistQueuePointer].dwOffset = param_1;
  this->hist[this->iHistQueuePointer].dwDelay = param_2;
  this->hist[this->iHistQueuePointer].BAddOffset = param_3;
  this->hist[this->iHistQueuePointer].dwOffHigh = param_4;
  this->hist[this->iHistQueuePointer].BAddOffHigh = param_5;
  this->hist[this->iHistQueuePointer].dwOffLow = param_6;
  this->hist[this->iHistQueuePointer].BAddOffLow = param_7;
  this->iHistQueuePointer = (this->iHistQueuePointer + 1) % 10;
  iVar1 = this->iHistQueueSize;
  if (iVar1 < 10) {
    this->iHistQueueSize = iVar1 + 1;
  }
  return;
}
