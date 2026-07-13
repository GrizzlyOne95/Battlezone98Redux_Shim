/*
 * Entry: 004b1c24
 * Name: Team::GetSlot
 * Namespace: Team
 * Signature: GameObject * GetSlot(Team * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Team::GetSlot(Team *this,int param_1)

{
  return this->teamSlot[param_1];
}
