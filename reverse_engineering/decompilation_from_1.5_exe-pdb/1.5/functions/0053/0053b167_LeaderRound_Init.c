/*
 * Entry: 0053b167
 * Name: LeaderRound::Init
 * Namespace: LeaderRound
 * Signature: void Init(LeaderRound * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LeaderRound::Init(LeaderRound *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  Rocket::Init((Rocket *)this,param_1,param_2);
  this->hitObj = 0;
  this->launcherObj = (TargetingGun *)0x0;
  return;
}
