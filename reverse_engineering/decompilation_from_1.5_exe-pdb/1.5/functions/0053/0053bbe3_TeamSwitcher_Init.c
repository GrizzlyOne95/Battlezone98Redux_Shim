/*
 * Entry: 0053bbe3
 * Name: TeamSwitcher::Init
 * Namespace: TeamSwitcher
 * Signature: void Init(TeamSwitcher * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TeamSwitcher::Init(TeamSwitcher *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  uint uVar1;
  
  Rocket::Init((Rocket *)this,param_1,param_2);
  this->hitObj = 0;
  uVar1 = *(ushort *)(this->_padding_ + 0x16) & 0xf;
  this->myTeam = uVar1;
  this->savedTeam = uVar1;
  return;
}
