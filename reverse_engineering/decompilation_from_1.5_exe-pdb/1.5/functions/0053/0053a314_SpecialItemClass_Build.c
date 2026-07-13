/*
 * Entry: 0053a314
 * Name: SpecialItemClass::Build
 * Namespace: SpecialItemClass
 * Signature: Weapon * Build(SpecialItemClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall SpecialItemClass::Build(SpecialItemClass *this,_OBJ76 *param_1)

{
  SpecialItem *pSVar1;
  
  pSVar1 = operator_new(0xc0);
  if (pSVar1 == (SpecialItem *)0x0) {
    pSVar1 = (SpecialItem *)0x0;
  }
  else {
    pSVar1 = SpecialItem::SpecialItem(pSVar1,param_1,this);
  }
  return (Weapon *)pSVar1;
}
