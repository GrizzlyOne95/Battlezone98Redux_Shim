/*
 * Entry: 004d10c8
 * Name: LightningFeature::Simulate
 * Namespace: LightningFeature
 * Signature: void Simulate(LightningFeature * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::Simulate(LightningFeature *this,float param_1)

{
  BoltEmitter *pBVar1;
  float fVar2;
  BoltEmitter **ppBVar3;
  
  ppBVar3 = this->activeList;
  if (ppBVar3 < this->activeList + this->activeNum) {
    do {
      pBVar1 = *ppBVar3;
      fVar2 = pBVar1->delay - param_1;
      pBVar1->delay = fVar2;
      if (fVar2 <= 0.0) {
        if (pBVar1->flash == 0) {
          if (pBVar1->target == (_OBJ76 *)0x0) {
            GenerateBoltPos(this,pBVar1,&View_Record.MainCam);
          }
          else {
            SetBoltPos(this,pBVar1,&View_Record.MainCam);
          }
          GenerateBoltSegs(this,pBVar1);
          if (BoltSet.sound[0] != '\0') {
            DoAudioFixedLoc(BoltSet.sound,pBVar1->target,(GAS_CTRL *)0x0);
          }
          TerrainSkyFlash = 0;
        }
        if (pBVar1->flash < pBVar1->flashes) {
          pBVar1->flash = pBVar1->flash + 1;
          pBVar1->delay = pBVar1->duration + pBVar1->delay;
        }
        else {
          TerrainSkyFlash = 0;
          BoltInit(this,pBVar1);
        }
      }
      ppBVar3 = ppBVar3 + 1;
    } while (ppBVar3 < this->activeList + this->activeNum);
  }
  return;
}
