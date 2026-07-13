/*
 * Entry: 004b1c6c
 * Name: Team::SetScrap
 * Namespace: Team
 * Signature: void SetScrap(Team * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::SetScrap(Team *this,long param_1)

{
  this->curScrap = param_1 ^ 0x33333333;
  return;
}
