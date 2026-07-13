/*
 * Entry: 0049a426
 * Name: Geizer::StartSteam
 * Namespace: Geizer
 * Signature: void StartSteam(Geizer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Geizer::StartSteam(Geizer *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 & 0xfffffbfe;
  this->isSteamOn = true;
  return;
}
