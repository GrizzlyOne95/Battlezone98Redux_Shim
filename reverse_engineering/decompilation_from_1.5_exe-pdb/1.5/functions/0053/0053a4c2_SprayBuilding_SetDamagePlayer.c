/*
 * Entry: 0053a4c2
 * Name: SprayBuilding::SetDamagePlayer
 * Namespace: SprayBuilding
 * Signature: void SetDamagePlayer(SprayBuilding * this, bool param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SprayBuilding::SetDamagePlayer(SprayBuilding *this,bool param_1,bool param_2)

{
  this->dmg_player = param_1;
  this->dmg_remote = param_2;
  return;
}
