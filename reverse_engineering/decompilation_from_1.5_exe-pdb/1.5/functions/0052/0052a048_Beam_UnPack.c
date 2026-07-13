/*
 * Entry: 0052a048
 * Name: Beam::UnPack
 * Namespace: Beam
 * Signature: uint UnPack(Beam * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall Beam::UnPack(Beam *this,char *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = Ordnance::UnPack((Ordnance *)this,param_1);
  if ((byte)param_1[uVar1] < 5) {
    uVar2 = (uint)(byte)param_1[uVar1];
  }
  else {
    uVar2 = 0xffffffff;
  }
  this->hardpoint = uVar2;
  return uVar1 + 1;
}
