/*
 * Entry: 0049a43b
 * Name: Geizer::StopSteam
 * Namespace: Geizer
 * Signature: void StopSteam(Geizer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Geizer::StopSteam(Geizer *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 | 0x401;
  this->isSteamOn = false;
  return;
}
