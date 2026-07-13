/*
 * Entry: 0053669f
 * Name: PopperClass::Build
 * Namespace: PopperClass
 * Signature: Ordnance * Build(PopperClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall PopperClass::Build(PopperClass *this,_OBJ76 *param_1)

{
  Popper *pPVar1;
  
  pPVar1 = operator_new(0xe8);
  if (pPVar1 == (Popper *)0x0) {
    pPVar1 = (Popper *)0x0;
  }
  else {
    pPVar1 = Popper::Popper(pPVar1,param_1,this);
  }
  return (Ordnance *)pPVar1;
}
