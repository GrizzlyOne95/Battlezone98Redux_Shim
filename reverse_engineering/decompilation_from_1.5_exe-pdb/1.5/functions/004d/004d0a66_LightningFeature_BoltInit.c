/*
 * Entry: 004d0a66
 * Name: LightningFeature::BoltInit
 * Namespace: LightningFeature
 * Signature: void BoltInit(LightningFeature * this, BoltEmitter * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::BoltInit(LightningFeature *this,BoltEmitter *param_1)

{
  float fVar1;
  tagENTITY *ptVar2;
  int iVar3;
  
  param_1->flash = 0;
  param_1->flashes = 1;
  if (param_1->target == (_OBJ76 *)0x0) {
    fVar1 = 0.0;
  }
  else {
    ptVar2 = FindObjectEntity(param_1->target);
    fVar1 = (ptVar2->bSphere).radius * 0.75 + (ptVar2->bSphere).origin.y;
  }
  param_1->ground = fVar1;
  iVar3 = rand();
  param_1->delay =
       (float)iVar3 * (BoltSet.maxDelay - BoltSet.minDelay) * 3.051851e-05 + BoltSet.minDelay;
  param_1->duration = BoltSet.duration;
  return;
}
