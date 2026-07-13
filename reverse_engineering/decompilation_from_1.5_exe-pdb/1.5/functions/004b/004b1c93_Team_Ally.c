/*
 * Entry: 004b1c93
 * Name: Team::Ally
 * Namespace: Team
 * Signature: void Ally(Team * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::Ally(Team *this,int param_1)

{
  this->dwAllies = this->dwAllies | 1 << ((byte)param_1 & 0x1f);
  return;
}
