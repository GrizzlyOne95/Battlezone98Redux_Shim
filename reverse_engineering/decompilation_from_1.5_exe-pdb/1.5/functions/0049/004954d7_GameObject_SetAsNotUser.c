/*
 * Entry: 004954d7
 * Name: GameObject::SetAsNotUser
 * Namespace: GameObject
 * Signature: void SetAsNotUser(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetAsNotUser(GameObject *this)

{
  AiProcess *pAVar1;
  
  pAVar1 = this->aiProcess;
  if (pAVar1 != (AiProcess *)0x0) {
    (**(code **)pAVar1->_padding_)(1);
    this->aiProcess = (AiProcess *)0x0;
  }
  (**(code **)(this->_padding_ + 8))();
  (**(code **)(this->_padding_ + 4))(*(ushort *)((int)&this->obj->flags + 2) & 0xf);
  return;
}
