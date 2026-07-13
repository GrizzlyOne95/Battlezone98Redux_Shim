/*
 * Entry: 0047bf8b
 * Name: AnimBuildingClass::BuildClass
 * Namespace: AnimBuildingClass
 * Signature: GameObjectClass * BuildClass(AnimBuildingClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall AnimBuildingClass::BuildClass(AnimBuildingClass *this,long64 param_1)

{
  AnimBuildingClass *pAVar1;
  undefined4 unaff_ESI;
  
  pAVar1 = operator_new(0x160);
  if (pAVar1 == (AnimBuildingClass *)0x0) {
    pAVar1 = (AnimBuildingClass *)0x0;
  }
  else {
    pAVar1 = AnimBuildingClass(pAVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pAVar1;
}
