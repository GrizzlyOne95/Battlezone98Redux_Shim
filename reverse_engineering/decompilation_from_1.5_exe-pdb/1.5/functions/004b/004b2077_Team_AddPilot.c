/*
 * Entry: 004b2077
 * Name: Team::AddPilot
 * Namespace: Team
 * Signature: void AddPilot(Team * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Team::AddPilot(Team *this,long param_1)

{
  this->curPilot = this->curPilot + param_1;
  if (this->maxPilot < this->curPilot) {
    this->curPilot = this->maxPilot;
  }
  if (((param_1 < 0) && (this->curPilot == 0)) && (this == GameObject::userTeamList)) {
    BettyVoice::PilotDepleted(&bettyVoice);
  }
  return;
}
