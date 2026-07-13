/*
 * Entry: 0049f14d
 * Name: HoverCraftClass::Build
 * Namespace: HoverCraftClass
 * Signature: GameObject * Build(HoverCraftClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall HoverCraftClass::Build(HoverCraftClass *this,_OBJ76 *param_1)

{
  HoverCraft *pHVar1;
  
  pHVar1 = GameObject::operator_new(0x2c0);
  if (pHVar1 == (HoverCraft *)0x0) {
    pHVar1 = (HoverCraft *)0x0;
  }
  else {
    pHVar1 = HoverCraft::HoverCraft(pHVar1,param_1,this);
  }
  return (GameObject *)pHVar1;
}
