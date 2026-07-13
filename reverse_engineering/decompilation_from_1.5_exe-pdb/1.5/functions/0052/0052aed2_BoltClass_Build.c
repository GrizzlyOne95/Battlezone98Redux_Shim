/*
 * Entry: 0052aed2
 * Name: BoltClass::Build
 * Namespace: BoltClass
 * Signature: Ordnance * Build(BoltClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall BoltClass::Build(BoltClass *this,_OBJ76 *param_1)

{
  Bolt *pBVar1;
  
  pBVar1 = operator_new(0x100);
  if (pBVar1 == (Bolt *)0x0) {
    pBVar1 = (Bolt *)0x0;
  }
  else {
    pBVar1 = Bolt::Bolt(pBVar1,param_1,this);
  }
  return (Ordnance *)pBVar1;
}
