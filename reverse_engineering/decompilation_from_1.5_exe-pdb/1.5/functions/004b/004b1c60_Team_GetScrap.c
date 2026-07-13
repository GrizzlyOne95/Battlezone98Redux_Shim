/*
 * Entry: 004b1c60
 * Name: Team::GetScrap
 * Namespace: Team
 * Signature: long GetScrap(Team * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __thiscall Team::GetScrap(Team *this)

{
  return this->curScrap ^ 0x33333333;
}
