/*
 * Entry: 004851b1
 * Name: CommTowerClass::BuildClass
 * Namespace: CommTowerClass
 * Signature: GameObjectClass * BuildClass(CommTowerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall CommTowerClass::BuildClass(CommTowerClass *this,long64 param_1)

{
  CommTowerClass *pCVar1;
  undefined4 unaff_ESI;
  
  pCVar1 = operator_new(0x168);
  if (pCVar1 == (CommTowerClass *)0x0) {
    pCVar1 = (CommTowerClass *)0x0;
  }
  else {
    pCVar1 = CommTowerClass(pCVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pCVar1;
}
