/*
 * Entry: 004e0ef8
 * Name: NetPlayer::GetFlag
 * Namespace: NetPlayer
 * Signature: void * GetFlag(NetPlayer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall NetPlayer::GetFlag(NetPlayer *this)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0x100;
  if (this->bGotFlag == false) {
    iVar1 = dpGetPlayerData(Net::dp,this->playerId,0xd,this->flagBuf,&local_8,0);
    if (iVar1 != 0) {
      return (void *)0x0;
    }
    this->bGotFlag = true;
  }
  return this->flagBuf;
}
