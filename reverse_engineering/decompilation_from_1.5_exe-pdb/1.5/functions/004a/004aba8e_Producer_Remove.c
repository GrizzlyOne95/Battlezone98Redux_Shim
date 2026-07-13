/*
 * Entry: 004aba8e
 * Name: Producer::Remove
 * Namespace: Producer
 * Signature: void Remove(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::Remove(Producer *this)

{
  Geizer *this_00;
  
  HasPower((Producer *)(this[-1].smokeList + 5));
  if (this->_padding_ != 0) {
    Geizer::Unlock((Geizer *)this->_padding_);
    this_00 = (Geizer *)this->_padding_;
    if (this_00->isSteamOn == false) {
      Geizer::StartSteam(this_00);
      BlockCells((GameObject *)(this[-1].smokeList + 5),false);
    }
  }
  Craft::Remove((Craft *)this);
  return;
}
