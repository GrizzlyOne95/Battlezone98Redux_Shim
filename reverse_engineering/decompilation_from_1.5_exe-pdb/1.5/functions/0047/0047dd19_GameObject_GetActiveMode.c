/*
 * Entry: 0047dd19
 * Name: GameObject::GetActiveMode
 * Namespace: GameObject
 * Signature: int GetActiveMode(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall GameObject::GetActiveMode(GameObject *this)

{
  uint uVar1;
  
  uVar1 = (this->modeList).activeSlot;
  if (uVar1 < 0xb) {
    return (this->modeList).modeList[uVar1];
  }
  return 0;
}
