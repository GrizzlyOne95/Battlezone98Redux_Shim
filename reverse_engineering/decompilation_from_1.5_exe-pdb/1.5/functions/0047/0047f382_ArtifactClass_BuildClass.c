/*
 * Entry: 0047f382
 * Name: ArtifactClass::BuildClass
 * Namespace: ArtifactClass
 * Signature: GameObjectClass * BuildClass(ArtifactClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ArtifactClass::BuildClass(ArtifactClass *this,long64 param_1)

{
  ArtifactClass *pAVar1;
  undefined4 unaff_ESI;
  
  pAVar1 = operator_new(0x160);
  if (pAVar1 == (ArtifactClass *)0x0) {
    pAVar1 = (ArtifactClass *)0x0;
  }
  else {
    pAVar1 = ArtifactClass(pAVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pAVar1;
}
