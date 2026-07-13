/*
 * Entry: 004df048
 * Name: Net::Join
 * Namespace: Net
 * Signature: void Join(Net * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::Join(Net *this)

{
  int iVar1;
  
  iVar1 = dpOpen(dp,&sDesc,dpOpenCallback,this);
  if (iVar1 != 0) {
    DEBUG_systemError("Open connection to network for joining");
  }
  this->state = WAITING_FOR_OPEN;
  return;
}
