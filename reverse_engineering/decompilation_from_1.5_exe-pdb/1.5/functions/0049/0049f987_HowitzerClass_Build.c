/*
 * Entry: 0049f987
 * Name: HowitzerClass::Build
 * Namespace: HowitzerClass
 * Signature: GameObject * Build(HowitzerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall HowitzerClass::Build(HowitzerClass *this,_OBJ76 *param_1)

{
  Howitzer *pHVar1;
  
  pHVar1 = GameObject::operator_new(0x338);
  if (pHVar1 == (Howitzer *)0x0) {
    pHVar1 = (Howitzer *)0x0;
  }
  else {
    pHVar1 = Howitzer::Howitzer(pHVar1,param_1,this);
  }
  return (GameObject *)pHVar1;
}
