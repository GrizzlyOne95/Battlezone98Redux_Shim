/*
 * Entry: 0047be74
 * Name: AmmoPowerupClass::Build
 * Namespace: AmmoPowerupClass
 * Signature: GameObject * Build(AmmoPowerupClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall AmmoPowerupClass::Build(AmmoPowerupClass *this,_OBJ76 *param_1)

{
  AmmoPowerup *pAVar1;
  
  pAVar1 = GameObject::operator_new(0x228);
  if (pAVar1 == (AmmoPowerup *)0x0) {
    pAVar1 = (AmmoPowerup *)0x0;
  }
  else {
    pAVar1 = AmmoPowerup::AmmoPowerup(pAVar1,param_1,this);
  }
  return (GameObject *)pAVar1;
}
