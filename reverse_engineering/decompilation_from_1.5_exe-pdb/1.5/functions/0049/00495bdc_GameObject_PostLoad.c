/*
 * Entry: 00495bdc
 * Name: GameObject::PostLoad
 * Namespace: GameObject
 * Signature: bool PostLoad(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::PostLoad(GameObject *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = &(this->curCmd).who;
  iVar2 = ConvertHandle(*piVar1);
  *piVar1 = iVar2;
  piVar1 = &(this->nextCmd).who;
  iVar2 = ConvertHandle(*piVar1);
  *piVar1 = iVar2;
  return true;
}
