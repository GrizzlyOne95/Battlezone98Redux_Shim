/*
 * Entry: 004b20bb
 * Name: Team::AddMaxPilot
 * Namespace: Team
 * Signature: void AddMaxPilot(Team * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::AddMaxPilot(Team *this,long param_1)

{
  long *plVar1;
  int iVar2;
  
  plVar1 = &this->maxPilot;
  *plVar1 = *plVar1 + param_1;
  iVar2 = *plVar1;
  if ((((iVar2 < this->curPilot) && (this->curPilot = iVar2, param_1 < 0)) && (iVar2 == 0)) &&
     (this == GameObject::userTeamList)) {
    BettyVoice::PilotDepleted(&bettyVoice);
  }
  return;
}
