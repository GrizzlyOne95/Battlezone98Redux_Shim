/*
 * Entry: 004b1c16
 * Name: Team::SetSlot
 * Namespace: Team
 * Signature: void SetSlot(Team * this, int param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::SetSlot(Team *this,int param_1,GameObject *param_2)

{
  this->teamSlot[param_1] = param_2;
  return;
}
