/*
 * Entry: 004d134f
 * Name: LightningFeature::Submit
 * Namespace: LightningFeature
 * Signature: void Submit(LightningFeature * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::Submit(LightningFeature *this,CAMERA *param_1)

{
  BoltEmitter **ppBVar1;
  
  if (View_Record.Current_View != OVER_VIEW) {
    for (ppBVar1 = this->activeList; ppBVar1 != this->activeList + this->activeNum;
        ppBVar1 = ppBVar1 + 1) {
      if ((*ppBVar1)->flash != 0) {
        RenderBoltSegs(this,*ppBVar1,param_1);
      }
    }
  }
  return;
}
