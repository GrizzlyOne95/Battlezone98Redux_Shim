/*
 * Entry: 0052c75a
 * Name: CannonClass::Build
 * Namespace: CannonClass
 * Signature: Weapon * Build(CannonClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall CannonClass::Build(CannonClass *this,_OBJ76 *param_1)

{
  Cannon *pCVar1;
  
  pCVar1 = operator_new(0xb8);
  if (pCVar1 == (Cannon *)0x0) {
    pCVar1 = (Cannon *)0x0;
  }
  else {
    pCVar1 = Cannon::Cannon(pCVar1,param_1,this);
  }
  return (Weapon *)pCVar1;
}
