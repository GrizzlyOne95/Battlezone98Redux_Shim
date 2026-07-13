/*
 * Entry: 004b1c2e
 * Name: Team::FirstEmptySlot
 * Namespace: Team
 * Signature: int FirstEmptySlot(Team * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Team::FirstEmptySlot(Team *this,int param_1,int param_2)

{
  while( true ) {
    if (param_2 < param_1) {
      return -1;
    }
    if (this->teamSlot[param_1] == (GameObject *)0x0) break;
    param_1 = param_1 + 1;
  }
  return param_1;
}
