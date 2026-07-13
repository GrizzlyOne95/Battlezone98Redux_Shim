/*
 * Entry: 00531bf9
 * Name: Mine::Simulate
 * Namespace: Mine
 * Signature: void Simulate(Mine * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mine::Simulate(Mine *this,float param_1)

{
  uint *puVar1;
  float fVar2;
  bool bVar3;
  
  if (this->lifeTimer < param_1) {
    param_1 = this->lifeTimer;
  }
  fVar2 = this->lifeTimer - param_1;
  this->lifeTimer = fVar2;
  if (fVar2 <= 0.0) {
    bVar3 = Net::IsNetGame();
    if ((bVar3) && ((*(byte *)(this->_padding_ + 0x14) & 0x80) == 0)) {
      puVar1 = (uint *)(this->_padding_ + 0x14);
      *puVar1 = *puVar1 | 0x280;
      DistributedObject::SetLocal((DistributedObject *)&this->_padding_);
    }
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x280;
  }
  if ((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0) {
    (**(code **)(this->_padding_ + 0x14))();
  }
  return;
}
