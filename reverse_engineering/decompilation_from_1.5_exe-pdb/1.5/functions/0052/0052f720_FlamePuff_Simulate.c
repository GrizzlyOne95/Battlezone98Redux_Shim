/*
 * Entry: 0052f720
 * Name: FlamePuff::Simulate
 * Namespace: FlamePuff
 * Signature: void Simulate(FlamePuff * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlamePuff::Simulate(FlamePuff *this,float param_1)

{
  int iVar1;
  
  Bullet::Simulate((Bullet *)this,param_1);
  iVar1 = this->_padding_;
  this->frameTimer = param_1 + this->frameTimer;
  if (this->flameIndex < *(int *)(iVar1 + 0x7c)) {
    do {
      if (*(float *)(iVar1 + 0x74) < this->frameTimer ==
          (*(float *)(iVar1 + 0x74) == this->frameTimer)) {
        return;
      }
      this->flameIndex = this->flameIndex + 1;
      this->frameTimer = this->frameTimer - *(float *)(iVar1 + 0x74);
    } while (this->flameIndex < *(int *)(iVar1 + 0x7c));
  }
  return;
}
