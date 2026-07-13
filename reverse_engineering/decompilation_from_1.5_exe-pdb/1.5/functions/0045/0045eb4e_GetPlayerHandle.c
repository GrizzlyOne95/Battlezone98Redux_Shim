/*
 * Entry: 0045eb4e
 * Name: GetPlayerHandle
 * Namespace: Global
 * Signature: int GetPlayerHandle(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPlayerHandle(void)

{
  GameObject *this;
  GameObject *pGVar1;
  
  this = GameObject::userObject;
  if (GameObject::userObject == (GameObject *)0x0) {
    playerHandle = 0;
    return 0;
  }
  pGVar1 = GameObjectHandle::GetObj(playerHandle);
  if (pGVar1 == this) {
    return playerHandle;
  }
  playerHandle = GameObject::GetHandle(this);
  return playerHandle;
}
