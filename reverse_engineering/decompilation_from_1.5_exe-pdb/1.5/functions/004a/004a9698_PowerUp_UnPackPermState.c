/*
 * Entry: 004a9698
 * Name: PowerUp::UnPackPermState
 * Namespace: PowerUp
 * Signature: void UnPackPermState(PowerUp * this, void * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::UnPackPermState(PowerUp *this,void *param_1,uint param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = DistributedObject::GetGameObject(*(ulong *)param_1);
  if (pGVar1 != (GameObject *)0x0) {
    GameObject::SetOwner((GameObject *)&this[-1]._padding_,pGVar1);
  }
  pGVar1 = DistributedObject::GetGameObject(*(ulong *)((int)param_1 + 4));
  if (pGVar1 != (GameObject *)0x0) {
    GameObject::SetTarget((GameObject *)&this[-1]._padding_,pGVar1);
  }
  return;
}
