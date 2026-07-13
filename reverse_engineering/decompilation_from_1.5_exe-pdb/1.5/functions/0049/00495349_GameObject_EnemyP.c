/*
 * Entry: 00495349
 * Name: GameObject::EnemyP
 * Namespace: GameObject
 * Signature: bool EnemyP(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::EnemyP(GameObject *this,int param_1)

{
  bool bVar1;
  
  if (((this->teamList != (Team *)0x0) && (-1 < param_1)) &&
     (bVar1 = Team::EnemyP(this->teamList,param_1), bVar1)) {
    return true;
  }
  return false;
}
