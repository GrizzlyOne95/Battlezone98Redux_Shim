/*
 * Entry: 0053b189
 * Name: LeaderRound::Cleanup
 * Namespace: LeaderRound
 * Signature: void Cleanup(LeaderRound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LeaderRound::Cleanup(LeaderRound *this)

{
  if (this->launcherObj != (TargetingGun *)0x0) {
    this->launcherObj->leaderObj = (LeaderRound *)0x0;
  }
  Rocket::Cleanup((Rocket *)this);
  return;
}
