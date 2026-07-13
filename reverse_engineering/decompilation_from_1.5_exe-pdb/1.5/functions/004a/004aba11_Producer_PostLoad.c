/*
 * Entry: 004aba11
 * Name: Producer::PostLoad
 * Namespace: Producer
 * Signature: bool PostLoad(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::PostLoad(Producer *this)

{
  bool bVar1;
  int iVar2;
  
  if (this->powerSource != (Geizer *)0x0) {
    Geizer::Lock(this->powerSource);
    iVar2 = GameObject::GetHandle((GameObject *)this->powerSource);
    this->powerHandle = iVar2;
  }
  if (this->_padding_ != 0) {
    HasPower(this);
    if (this->_padding_ == 2) {
      if (this->powerSource != (Geizer *)0x0) {
        Geizer::StopSteam(this->powerSource);
      }
      BlockCells((GameObject *)this,true);
    }
    if (this->powerSource != (Geizer *)0x0) {
      Geizer::Lock(this->powerSource);
      iVar2 = GameObject::GetHandle((GameObject *)this->powerSource);
      this->powerHandle = iVar2;
    }
  }
  bVar1 = Craft::PostLoad((Craft *)this);
  return bVar1;
}
