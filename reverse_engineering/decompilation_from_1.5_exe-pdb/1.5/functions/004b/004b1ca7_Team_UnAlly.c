/*
 * Entry: 004b1ca7
 * Name: Team::UnAlly
 * Namespace: Team
 * Signature: void UnAlly(Team * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::UnAlly(Team *this,int param_1)

{
  this->dwAllies = this->dwAllies & ~(1 << ((byte)param_1 & 0x1f));
  return;
}
