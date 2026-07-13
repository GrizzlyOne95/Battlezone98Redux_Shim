/*
 * Entry: 004a9640
 * Name: PowerUp::PackPermState
 * Namespace: PowerUp
 * Signature: void PackPermState(PowerUp * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::PackPermState(PowerUp *this,void *param_1,uint *param_2)

{
  GameObject *pGVar1;
  ulong uVar2;
  
  *param_2 = *param_2 + 8;
  pGVar1 = GameObject::GetObj(this->_padding_);
  if (pGVar1 == (GameObject *)0x0) {
    *(undefined4 *)param_1 = 0;
  }
  else {
    uVar2 = DistributedObject::GetID((DistributedObject *)&pGVar1->_padding_);
    *(ulong *)param_1 = uVar2;
  }
  pGVar1 = GameObject::GetObj(this->_padding_);
  if (pGVar1 == (GameObject *)0x0) {
    *(undefined4 *)((int)param_1 + 4) = 0;
  }
  else {
    uVar2 = DistributedObject::GetID((DistributedObject *)&pGVar1->_padding_);
    *(ulong *)((int)param_1 + 4) = uVar2;
  }
  return;
}
