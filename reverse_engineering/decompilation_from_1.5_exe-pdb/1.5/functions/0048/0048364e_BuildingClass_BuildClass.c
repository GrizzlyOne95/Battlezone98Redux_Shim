/*
 * Entry: 0048364e
 * Name: BuildingClass::BuildClass
 * Namespace: BuildingClass
 * Signature: GameObjectClass * BuildClass(BuildingClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall BuildingClass::BuildClass(BuildingClass *this,long64 param_1)

{
  BuildingClass *pBVar1;
  undefined4 unaff_ESI;
  
  pBVar1 = operator_new(0x160);
  if (pBVar1 == (BuildingClass *)0x0) {
    pBVar1 = (BuildingClass *)0x0;
  }
  else {
    pBVar1 = BuildingClass(pBVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pBVar1;
}
