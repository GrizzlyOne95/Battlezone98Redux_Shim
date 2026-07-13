/*
 * Entry: 00496da9
 * Name: GameObject::SetDamageFlags
 * Namespace: GameObject
 * Signature: void SetDamageFlags(GameObject * this, DAMAGE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetDamageFlags(GameObject *this,DAMAGE *param_1)

{
  bool bVar1;
  int iVar2;
  GameObject *this_00;
  float fVar3;
  
  fVar3 = Get_TimeLocal();
  this->hitOrdClass = (OrdnanceClass *)0x0;
  if (param_1->dmg_source == (_OBJ76 *)0x0) {
    this->groundCollide = fVar3;
  }
  else if (param_1->damager == param_1->dmg_source) {
    if ((param_1->field_0x8 & 0x10) != 0) {
      this->playerCollide = fVar3;
    }
    bVar1 = EnemyP(this,*(ushort *)((int)&param_1->dmg_source->flags + 2) & 0xf);
    if (bVar1) {
      this->enemyCollide = fVar3;
    }
    else {
      this->friendCollide = fVar3;
    }
  }
  else {
    if ((param_1->field_0x8 & 0x10) != 0) {
      this->playerShot = fVar3;
    }
    bVar1 = EnemyP(this,*(ushort *)((int)&param_1->dmg_source->flags + 2) & 0xf);
    if (bVar1) {
      this->enemyShot = fVar3;
      BettyVoice::AttackWarning(&bettyVoice,this);
    }
    else {
      this->friendShot = fVar3;
    }
    if (param_1->damager == (_OBJ76 *)0x0) {
      this_00 = (GameObject *)0x0;
    }
    else {
      this_00 = param_1->damager->gameObj;
    }
    if ((this_00 != (GameObject *)0x0) && (this_00 != this)) {
      iVar2 = GetHandle(this_00);
      this->who_shot_JR = iVar2;
      iVar2 = GetHandle(this);
      SetWhoIShot(this_00,iVar2);
      iVar2 = (**(code **)(this_00->_padding_ + 4))();
      this_00->perceivedTeam = iVar2;
    }
  }
  return;
}
