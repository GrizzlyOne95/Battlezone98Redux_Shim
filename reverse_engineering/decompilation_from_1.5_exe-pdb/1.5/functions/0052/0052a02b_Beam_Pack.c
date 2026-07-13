/*
 * Entry: 0052a02b
 * Name: Beam::Pack
 * Namespace: Beam
 * Signature: uint Pack(Beam * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall Beam::Pack(Beam *this,char *param_1)

{
  uint uVar1;
  
  uVar1 = Ordnance::Pack((Ordnance *)this,param_1);
  param_1[uVar1] = (char)this->hardpoint;
  return uVar1 + 1;
}
