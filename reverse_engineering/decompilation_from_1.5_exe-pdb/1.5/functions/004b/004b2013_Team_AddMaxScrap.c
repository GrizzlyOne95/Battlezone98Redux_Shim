/*
 * Entry: 004b2013
 * Name: Team::AddMaxScrap
 * Namespace: Team
 * Signature: void AddMaxScrap(Team * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::AddMaxScrap(Team *this,long param_1)

{
  long *plVar1;
  uint uVar2;
  uint uVar3;
  
  plVar1 = &this->maxScrap;
  *plVar1 = *plVar1 + param_1;
  uVar3 = this->curScrap ^ 0x33333333;
  if (*plVar1 < (int)uVar3) {
    uVar2 = *plVar1 ^ 0x33333333;
    this->curScrap = uVar2;
    if (((param_1 < 0) && (uVar2 == 0x33333333)) && (this == GameObject::userTeamList)) {
      BettyVoice::ScrapDepleted(&bettyVoice);
    }
    AISchedule_AddScrap(this->teamNumber,(this->curScrap ^ 0x33333333U) - uVar3);
  }
  return;
}
