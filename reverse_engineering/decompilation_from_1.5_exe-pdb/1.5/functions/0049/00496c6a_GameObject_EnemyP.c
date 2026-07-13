/*
 * Entry: 00496c6a
 * Name: GameObject::EnemyP
 * Namespace: GameObject
 * Signature: bool EnemyP(GameObject * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::EnemyP(GameObject *this,GameObject *param_1)

{
  bool bVar1;
  int iVar2;
  
  if (param_1 != (GameObject *)0x0) {
    iVar2 = (**(code **)(param_1->_padding_ + 4))();
    bVar1 = EnemyP(this,iVar2);
    if (bVar1) {
      return true;
    }
  }
  return false;
}
