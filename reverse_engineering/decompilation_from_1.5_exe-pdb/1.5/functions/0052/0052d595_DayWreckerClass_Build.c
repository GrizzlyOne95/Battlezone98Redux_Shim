/*
 * Entry: 0052d595
 * Name: DayWreckerClass::Build
 * Namespace: DayWreckerClass
 * Signature: GameObject * Build(DayWreckerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall DayWreckerClass::Build(DayWreckerClass *this,_OBJ76 *param_1)

{
  DayWrecker *pDVar1;
  
  pDVar1 = GameObject::operator_new(0x228);
  if (pDVar1 == (DayWrecker *)0x0) {
    pDVar1 = (DayWrecker *)0x0;
  }
  else {
    pDVar1 = DayWrecker::DayWrecker(pDVar1,param_1,this);
  }
  return (GameObject *)pDVar1;
}
