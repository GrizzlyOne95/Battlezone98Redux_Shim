/*
 * Entry: 00531f96
 * Name: Missile::Pack
 * Namespace: Missile
 * Signature: uint Pack(Missile * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall Missile::Pack(Missile *this,char *param_1)

{
  uint uVar1;
  GameObject *pGVar2;
  ulong uVar3;
  
  uVar1 = Ordnance::Pack((Ordnance *)this,param_1);
  pGVar2 = GameObject::GetObj(this->targetHandle);
  if (pGVar2 == (GameObject *)0x0) {
    *(ulong *)(param_1 + uVar1) = 0;
  }
  else {
    uVar3 = DistributedObject::GetID((DistributedObject *)&pGVar2->_padding_);
    *(ulong *)(param_1 + uVar1) = uVar3;
  }
  return uVar1 + 4;
}
