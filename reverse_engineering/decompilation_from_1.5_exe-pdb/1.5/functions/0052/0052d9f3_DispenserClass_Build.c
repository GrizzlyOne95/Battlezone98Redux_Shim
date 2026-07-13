/*
 * Entry: 0052d9f3
 * Name: DispenserClass::Build
 * Namespace: DispenserClass
 * Signature: Weapon * Build(DispenserClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall DispenserClass::Build(DispenserClass *this,_OBJ76 *param_1)

{
  Dispenser *pDVar1;
  
  pDVar1 = operator_new(0xb8);
  if (pDVar1 == (Dispenser *)0x0) {
    pDVar1 = (Dispenser *)0x0;
  }
  else {
    pDVar1 = Dispenser::Dispenser(pDVar1,param_1,this);
  }
  return (Weapon *)pDVar1;
}
