/*
 * Entry: 0044e334
 * Name: OffensiveProcess::ShouldAttack
 * Namespace: OffensiveProcess
 * Signature: bool ShouldAttack(OffensiveProcess * this, State param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::ShouldAttack(OffensiveProcess *this,State param_1)

{
  bool bVar1;
  
  if (param_1 != WAIT) {
    if (param_1 == GOTO) {
      if (this->isFriend != false) {
        return false;
      }
      bVar1 = EnemyGotoVsAttack(this);
      return bVar1;
    }
    if (param_1 == ATTACK) {
      bVar1 = AttackVsAttack(this);
      return bVar1;
    }
    if (param_1 == FOLLOW) {
      bVar1 = FriendFollowVsAttack(this);
      return bVar1;
    }
    if (param_1 != DEFEND) {
      return false;
    }
  }
  bVar1 = WaitVsAttack(this);
  return bVar1;
}
