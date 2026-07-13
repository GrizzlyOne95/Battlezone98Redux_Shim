/*
 * Entry: 0053220e
 * Name: Missile::UnPack
 * Namespace: Missile
 * Signature: uint UnPack(Missile * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall Missile::UnPack(Missile *this,char *param_1)

{
  uint uVar1;
  GameObject *pGVar2;
  
  uVar1 = Ordnance::UnPack((Ordnance *)this,param_1);
  pGVar2 = DistributedObject::GetGameObject(*(ulong *)(param_1 + uVar1));
  SetTarget(this,pGVar2);
  return uVar1 + 4;
}
