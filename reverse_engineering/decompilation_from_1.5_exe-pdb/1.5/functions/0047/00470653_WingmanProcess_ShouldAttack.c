/*
 * Entry: 00470653
 * Name: WingmanProcess::ShouldAttack
 * Namespace: WingmanProcess
 * Signature: bool ShouldAttack(WingmanProcess * this, State param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall WingmanProcess::ShouldAttack(WingmanProcess *this,State param_1)

{
  bool bVar1;
  State SVar2;
  
  if (param_1 == ATTACK) {
    if (*(int *)(*(int *)&this->field_0x30 + 0xc) == 6) {
      bVar1 = AttackWaitVsAttack(this);
      return bVar1;
    }
    SVar2 = ATTACK;
  }
  else {
    if (param_1 != FOLLOW) {
      if (param_1 == USTATE1) {
        bVar1 = OffensiveProcess::WaitVsAttack((OffensiveProcess *)this);
        return bVar1;
      }
      bVar1 = OffensiveProcess::ShouldAttack((OffensiveProcess *)this,param_1);
      return bVar1;
    }
    if ((*(int *)&this->field_0x20 == 0) && (*(int *)(*(int *)&this->field_0x30 + 0xc) != 4)) {
      return false;
    }
    SVar2 = FOLLOW;
  }
  bVar1 = OffensiveProcess::ShouldAttack((OffensiveProcess *)this,SVar2);
  return bVar1;
}
