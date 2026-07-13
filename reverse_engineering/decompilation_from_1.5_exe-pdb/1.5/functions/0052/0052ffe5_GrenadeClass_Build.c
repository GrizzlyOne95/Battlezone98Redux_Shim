/*
 * Entry: 0052ffe5
 * Name: GrenadeClass::Build
 * Namespace: GrenadeClass
 * Signature: Ordnance * Build(GrenadeClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall GrenadeClass::Build(GrenadeClass *this,_OBJ76 *param_1)

{
  Grenade *pGVar1;
  
  pGVar1 = operator_new(0xe8);
  if (pGVar1 == (Grenade *)0x0) {
    pGVar1 = (Grenade *)0x0;
  }
  else {
    pGVar1 = Grenade::Grenade(pGVar1,param_1,this);
  }
  return (Ordnance *)pGVar1;
}
