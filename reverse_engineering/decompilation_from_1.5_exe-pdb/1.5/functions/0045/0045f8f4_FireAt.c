/*
 * Entry: 0045f8f4
 * Name: FireAt
 * Namespace: Global
 * Signature: void FireAt(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FireAt(int param_1,int param_2)

{
  Carrier *this;
  GameObject *this_00;
  GameObject *pGVar1;
  
  this_00 = GameObjectHandle::GetObj(param_1);
  if ((this_00 != (GameObject *)0x0) && (this = this_00->carrier, this != (Carrier *)0x0)) {
    Carrier::SetSelected(this,this_00->weaponMask);
    Carrier::TriggerSelected(this);
    pGVar1 = GameObjectHandle::GetObj(param_2);
    if (pGVar1 != (GameObject *)0x0) {
      GameObject::SetTarget(this_00,pGVar1);
    }
  }
  return;
}
