/*
 * Entry: 004d0a22
 * Name: LightningFeature::DelBoltEmitter
 * Namespace: LightningFeature
 * Signature: void DelBoltEmitter(LightningFeature * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::DelBoltEmitter(LightningFeature *this,_OBJ76 *param_1)

{
  BoltEmitter *pBVar1;
  BoltEmitter **ppBVar2;
  
  ppBVar2 = this->activeList;
  if (ppBVar2 < this->activeList + this->activeNum) {
    do {
      pBVar1 = *ppBVar2;
      if (pBVar1->target == param_1) {
        this->activeNum = this->activeNum + -1;
        *ppBVar2 = this->activeList[this->activeNum];
        this->activeList[this->activeNum] = pBVar1;
      }
      else {
        ppBVar2 = ppBVar2 + 1;
      }
    } while (ppBVar2 < this->activeList + this->activeNum);
  }
  return;
}
