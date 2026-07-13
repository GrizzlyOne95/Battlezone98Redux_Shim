/*
 * Entry: 004b1bbf
 * Name: SupplyDepotClass::BuildClass
 * Namespace: SupplyDepotClass
 * Signature: GameObjectClass * BuildClass(SupplyDepotClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall SupplyDepotClass::BuildClass(SupplyDepotClass *this,long64 param_1)

{
  SupplyDepotClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x180);
  if (pSVar1 == (SupplyDepotClass *)0x0) {
    pSVar1 = (SupplyDepotClass *)0x0;
  }
  else {
    pSVar1 = SupplyDepotClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
