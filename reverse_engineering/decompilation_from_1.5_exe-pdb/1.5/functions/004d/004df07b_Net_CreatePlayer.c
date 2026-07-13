/*
 * Entry: 004df07b
 * Name: Net::CreatePlayer
 * Namespace: Net
 * Signature: void CreatePlayer(Net * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::CreatePlayer(Net *this)

{
  int iVar1;
  
  this->state = WAITING_FOR_CREATE_PLAYER;
  iVar1 = dpCreatePlayer(dp,dpCreatePlayerCallback,this,player_name);
  if (iVar1 != 0) {
    DEBUG_systemError("Create player failed");
  }
  return;
}
