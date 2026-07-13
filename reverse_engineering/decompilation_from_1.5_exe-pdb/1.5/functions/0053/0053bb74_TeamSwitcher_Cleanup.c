/*
 * Entry: 0053bb74
 * Name: TeamSwitcher::Cleanup
 * Namespace: TeamSwitcher
 * Signature: void Cleanup(TeamSwitcher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TeamSwitcher::Cleanup(TeamSwitcher *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 & 0xfffffff7;
  Bullet::Cleanup((Bullet *)this);
  return;
}
