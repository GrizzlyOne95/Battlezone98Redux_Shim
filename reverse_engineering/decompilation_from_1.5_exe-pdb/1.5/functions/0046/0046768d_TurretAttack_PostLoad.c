/*
 * Entry: 0046768d
 * Name: TurretAttack::PostLoad
 * Namespace: TurretAttack
 * Signature: bool PostLoad(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretAttack::PostLoad(TurretAttack *this)

{
  GameObject *pGVar1;
  bool bVar2;
  int iVar3;
  AttackGroup *this_00;
  FollowGroup *this_01;
  float fVar4;
  
  iVar3 = ConvertHandle(this->_padding_);
  this->_padding_ = iVar3;
  iVar3 = ConvertHandle(this->_padding_);
  this->_padding_ = iVar3;
  iVar3 = ConvertHandle(this->_padding_);
  this->_padding_ = iVar3;
  if ((float)this->_padding_ == 0.0) {
    fVar4 = Get_Time();
    this->_padding_ = (int)fVar4;
  }
  bVar2 = SObject::PostLoad((SObject *)this);
  pGVar1 = (GameObject *)this->_padding_;
  if (pGVar1 != (GameObject *)0x0) {
    this_00 = AttackGroup::Find(pGVar1);
    this->_padding_ = (int)this_00;
    AttackGroup::Join(this_00,(GameObject *)this->_padding_,(UnitTask *)this);
    this->_padding_ = 0;
  }
  pGVar1 = (GameObject *)this->_padding_;
  if (pGVar1 != (GameObject *)0x0) {
    this_01 = FollowGroup::Find(pGVar1);
    this->_padding_ = (int)this_01;
    FollowGroup::Join(this_01,(GameObject *)this->_padding_);
    this->_padding_ = 0;
  }
  this->_padding_ = this->_padding_;
  iVar3 = this->_padding_;
  if (iVar3 != 0) {
    this->_padding_ = *(int *)(*(int *)(iVar3 + 8) + -8 + *(int *)(iVar3 + 4) * 8);
    fVar4 = *(float *)(*(int *)(iVar3 + 8) + -4 + *(int *)(iVar3 + 4) * 8);
    this->_padding_ = (int)fVar4;
    fVar4 = Terrain_FindFloor((double)(float)this->_padding_,(double)fVar4);
    this->_padding_ = (int)fVar4;
  }
  (**(code **)(this->_padding_ + 0x14))();
  return bVar2;
}
