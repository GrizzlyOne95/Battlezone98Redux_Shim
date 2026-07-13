/*
 * Entry: 00482972
 * Name: BarracksClass::Build
 * Namespace: BarracksClass
 * Signature: GameObject * Build(BarracksClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall BarracksClass::Build(BarracksClass *this,_OBJ76 *param_1)

{
  Barracks *pBVar1;
  
  pBVar1 = GameObject::operator_new(0x238);
  if (pBVar1 == (Barracks *)0x0) {
    pBVar1 = (Barracks *)0x0;
  }
  else {
    pBVar1 = Barracks::Barracks(pBVar1,param_1,this);
  }
  return (GameObject *)pBVar1;
}
