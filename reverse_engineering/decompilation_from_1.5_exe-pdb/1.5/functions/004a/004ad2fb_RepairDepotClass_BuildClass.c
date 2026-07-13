/*
 * Entry: 004ad2fb
 * Name: RepairDepotClass::BuildClass
 * Namespace: RepairDepotClass
 * Signature: GameObjectClass * BuildClass(RepairDepotClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall RepairDepotClass::BuildClass(RepairDepotClass *this,long64 param_1)

{
  RepairDepotClass *pRVar1;
  undefined4 unaff_ESI;
  
  pRVar1 = operator_new(0x180);
  if (pRVar1 == (RepairDepotClass *)0x0) {
    pRVar1 = (RepairDepotClass *)0x0;
  }
  else {
    pRVar1 = RepairDepotClass(pRVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pRVar1;
}
