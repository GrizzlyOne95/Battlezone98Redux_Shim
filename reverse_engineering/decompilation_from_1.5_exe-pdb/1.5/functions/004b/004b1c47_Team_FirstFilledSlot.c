/*
 * Entry: 004b1c47
 * Name: Team::FirstFilledSlot
 * Namespace: Team
 * Signature: int FirstFilledSlot(Team * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Team::FirstFilledSlot(Team *this,int param_1,int param_2)

{
  while( true ) {
    if (param_2 < param_1) {
      return -1;
    }
    if (this->teamSlot[param_1] != (GameObject *)0x0) break;
    param_1 = param_1 + 1;
  }
  return param_1;
}
