/*
 * Entry: 004852f7
 * Name: ConstructionRig::PostLoad
 * Namespace: ConstructionRig
 * Signature: bool PostLoad(ConstructionRig * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ConstructionRig::PostLoad(ConstructionRig *this)

{
  bool bVar1;
  int iVar2;
  
  if ((Geizer *)this->_padding_ != (Geizer *)0x0) {
    Geizer::Lock((Geizer *)this->_padding_);
    iVar2 = GameObject::GetHandle((GameObject *)this->_padding_);
    this->_padding_ = iVar2;
  }
  if (this->_padding_ != 0) {
    Producer::HasPower((Producer *)this);
    if (this->_padding_ == 2) {
      if ((Geizer *)this->_padding_ != (Geizer *)0x0) {
        Geizer::StopSteam((Geizer *)this->_padding_);
      }
      BlockCells((GameObject *)this,true);
    }
    if ((Geizer *)this->_padding_ != (Geizer *)0x0) {
      Geizer::Lock((Geizer *)this->_padding_);
      iVar2 = GameObject::GetHandle((GameObject *)this->_padding_);
      this->_padding_ = iVar2;
    }
  }
  bVar1 = Craft::PostLoad((Craft *)this);
  return bVar1;
}
