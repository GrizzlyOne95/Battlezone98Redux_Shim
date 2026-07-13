/*
 * Entry: 0053af24
 * Name: LeaderRound::GetTarget
 * Namespace: LeaderRound
 * Signature: GameObject * GetTarget(LeaderRound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall LeaderRound::GetTarget(LeaderRound *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(this->hitObj);
  return pGVar1;
}
