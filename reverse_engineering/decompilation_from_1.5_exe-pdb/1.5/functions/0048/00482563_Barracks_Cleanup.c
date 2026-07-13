/*
 * Entry: 00482563
 * Name: Barracks::Cleanup
 * Namespace: Barracks
 * Signature: void Cleanup(Barracks * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Barracks::Cleanup(Barracks *this)

{
  Team::AddMaxPilot((Team *)this->_padding_,-*(int *)(this->_padding_ + 0x160));
  Building::Cleanup((Building *)this);
  return;
}
