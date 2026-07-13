/*
 * Entry: 004b1fa0
 * Name: Team::AddScrap
 * Namespace: Team
 * Signature: void AddScrap(Team * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::AddScrap(Team *this,long param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = this->curScrap ^ 0x33333333;
  uVar1 = uVar2 + param_1;
  this->curScrap = uVar1 ^ 0x33333333;
  if (this->maxScrap < (int)uVar1) {
    this->curScrap = this->maxScrap ^ 0x33333333;
  }
  if (((param_1 < 0) && (this->curScrap == 0x33333333)) && (this == GameObject::userTeamList)) {
    BettyVoice::ScrapDepleted(&bettyVoice);
  }
  AISchedule_AddScrap(this->teamNumber,(this->curScrap ^ 0x33333333U) - uVar2);
  return;
}
