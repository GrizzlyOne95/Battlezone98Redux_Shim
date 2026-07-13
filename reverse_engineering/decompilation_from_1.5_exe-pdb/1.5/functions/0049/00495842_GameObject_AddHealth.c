/*
 * Entry: 00495842
 * Name: GameObject::AddHealth
 * Namespace: GameObject
 * Signature: void AddHealth(GameObject * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::AddHealth(GameObject *this,float param_1)

{
  int iVar1;
  float fVar2;
  
  if ((0.0 < this->enemyShot) &&
     ((((GameObject *)&this[-1].maxHealth != userObject || (0.0 < param_1)) ||
      (iVar1 = UserPref_unlimitedArmor(), iVar1 == 0)))) {
    fVar2 = Min(this->enemyShot,this->friendCollide + param_1);
    SetCurHealth((GameObject *)&this[-1].maxHealth,fVar2);
  }
  return;
}
