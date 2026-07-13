/*
 * Entry: 0053be28
 * Name: TerrainExposeClass::BuildClass
 * Namespace: TerrainExposeClass
 * Signature: WeaponClass * BuildClass(TerrainExposeClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall TerrainExposeClass::BuildClass(TerrainExposeClass *this,long64 param_1)

{
  TerrainExposeClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0xa8);
  if (pTVar1 == (TerrainExposeClass *)0x0) {
    pTVar1 = (TerrainExposeClass *)0x0;
  }
  else {
    pTVar1 = TerrainExposeClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pTVar1;
}
