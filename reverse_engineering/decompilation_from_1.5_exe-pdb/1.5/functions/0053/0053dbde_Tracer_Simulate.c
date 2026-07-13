/*
 * Entry: 0053dbde
 * Name: Tracer::Simulate
 * Namespace: Tracer
 * Signature: void Simulate(Tracer * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tracer::Simulate(Tracer *this,float param_1)

{
  int iVar1;
  
  Bullet::Simulate((Bullet *)this,param_1);
  iVar1 = this->_padding_;
  this->shotDistance =
       (float)(((float10)*(double *)(iVar1 + 0x48) - (float10)(this->startPos).x) *
               (float10)*(float *)(iVar1 + 0x38) +
              ((float10)*(double *)(iVar1 + 0x50) - (float10)(this->startPos).y) *
              (float10)*(float *)(iVar1 + 0x3c) +
              ((float10)*(double *)(iVar1 + 0x58) - (float10)(this->startPos).z) *
              (float10)*(float *)(iVar1 + 0x40));
  return;
}
