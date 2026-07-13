/*
 * Entry: 0048a20b
 * Name: DistributedObject::GetPlayerName
 * Namespace: DistributedObject
 * Signature: char * GetPlayerName(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall DistributedObject::GetPlayerName(DistributedObject *this)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 != 0) && (this->activnet_id != 0xfa01)) {
    pcVar2 = NetPlayer_GetPlayerName(this->activnet_id);
    return pcVar2;
  }
  return (char *)0x0;
}
