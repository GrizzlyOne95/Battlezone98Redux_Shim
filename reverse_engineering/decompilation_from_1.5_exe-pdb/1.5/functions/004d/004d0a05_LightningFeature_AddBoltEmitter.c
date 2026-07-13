/*
 * Entry: 004d0a05
 * Name: LightningFeature::AddBoltEmitter
 * Namespace: LightningFeature
 * Signature: void AddBoltEmitter(LightningFeature * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::AddBoltEmitter(LightningFeature *this,_OBJ76 *param_1)

{
  int iVar1;
  BoltEmitter *pBVar2;
  
  iVar1 = this->activeNum;
  if (iVar1 < 0x10) {
    pBVar2 = this->activeList[iVar1];
    this->activeNum = iVar1 + 1;
    pBVar2->target = param_1;
  }
  return;
}
