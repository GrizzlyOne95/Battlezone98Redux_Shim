/*
 * Entry: 004d09f6
 * Name: LightningFeature::Cleanup
 * Namespace: LightningFeature
 * Signature: void Cleanup(LightningFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::Cleanup(LightningFeature *this)

{
  int iVar1;
  BOLT_SET *pBVar2;
  
  pBVar2 = &BoltSet;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pBVar2->bolts = 0;
    pBVar2 = (BOLT_SET *)&pBVar2->color;
  }
  return;
}
