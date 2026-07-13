/*
 * Entry: 004df3ba
 * Name: Net::HandleSnipe
 * Namespace: Net
 * Signature: void HandleSnipe(ushort param_1, SNIPE_PACKET * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net::HandleSnipe(ushort param_1,SNIPE_PACKET *param_2)

{
  int *this;
  GameObject *pGVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  char cVar5;
  
  pGVar1 = DistributedObject::GetGameObject(param_2->dwHitObject);
  if (pGVar1 != (GameObject *)0x0) {
    this = &pGVar1->_padding_;
    iVar2 = (**(code **)(*this + 0x30))();
    if ((*(uint *)(iVar2 + 0x14) & 4) == 0) {
      *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 4;
      (**(code **)(pGVar1->_padding_ + 0x74))();
      DistributedObject::RecordDeath((DistributedObject *)this,param_2->shooterTeam);
      uVar3 = (uint)(pGVar1 == GameObject::userObject);
      cVar5 = 'S';
      uVar4 = param_2->shooterTeam;
      iVar2 = (**(code **)(*this + 4))();
      KillMessage(iVar2,uVar4,cVar5,uVar3);
    }
  }
  return;
}
