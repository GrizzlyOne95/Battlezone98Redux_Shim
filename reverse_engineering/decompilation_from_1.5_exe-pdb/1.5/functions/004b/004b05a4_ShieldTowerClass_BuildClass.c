/*
 * Entry: 004b05a4
 * Name: ShieldTowerClass::BuildClass
 * Namespace: ShieldTowerClass
 * Signature: GameObjectClass * BuildClass(ShieldTowerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ShieldTowerClass::BuildClass(ShieldTowerClass *this,long64 param_1)

{
  ShieldTowerClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x188);
  if (pSVar1 == (ShieldTowerClass *)0x0) {
    pSVar1 = (ShieldTowerClass *)0x0;
  }
  else {
    pSVar1 = ShieldTowerClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
