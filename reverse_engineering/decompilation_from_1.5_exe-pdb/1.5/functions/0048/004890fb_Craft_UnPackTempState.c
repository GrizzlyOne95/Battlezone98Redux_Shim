/*
 * Entry: 004890fb
 * Name: Craft::UnPackTempState
 * Namespace: Craft
 * Signature: void UnPackTempState(Craft * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::UnPackTempState(Craft *this,void *param_1,uint *param_2)

{
  GameObject *this_00;
  int iVar1;
  undefined4 *puVar2;
  void *pvVar3;
  NetProcess *this_01;
  AiMission *pAVar4;
  long extraout_EAX;
  int extraout_EAX_00;
  _OBJ76 **pp_Var5;
  
  pvVar3 = param_1;
  GameObject::SetObjective
            ((GameObject *)(this[-1].smokeList + 4),(bool)(*(byte *)((int)param_1 + 2) >> 5 & 1));
  if ((*(byte *)((int)param_1 + 2) & 0x80) == 0) {
    this->_padding_ = 0;
    puVar2 = (undefined4 *)this->_padding_;
    if (puVar2 != (undefined4 *)0x0) {
      (**(code **)*puVar2)(1);
      this->_padding_ = 0;
    }
  }
  else {
    this->_padding_ = this->_padding_;
    if (this->_padding_ == 0) {
      this_01 = operator_new(0x14);
      if (this_01 == (NetProcess *)0x0) {
        param_1 = (void *)0x0;
      }
      else {
        param_1 = NetProcess::NetProcess(this_01);
      }
      iVar1 = *(int *)param_1;
      pp_Var5 = this[-1].smokeList + 4;
      pAVar4 = AiMission::GetCurrent();
      (**(code **)(iVar1 + 0x18))(pAVar4,pp_Var5);
    }
  }
  this->_padding_ = (int)((float)*(byte *)((int)pvVar3 + 1) * 0.003921569);
  _ftol2_sse();
  this_00 = (GameObject *)(this[-1].smokeList + 4);
  GameObject::SetCurAmmo(this_00,extraout_EAX);
  this->_padding_ = (int)((float)*(byte *)pvVar3 * 0.003921569);
  _ftol2_sse();
  GameObject::SetCurHealth(this_00,(float)extraout_EAX_00);
  (**(code **)(this_00->_padding_ + 0xa0))(this->_padding_);
  if ((*(byte *)((int)pvVar3 + 2) & 0x10) != 0) {
    obj_set_flag((_OBJ76 *)this->_padding_,0x280);
    DistributedObject::SetLocal((DistributedObject *)this);
  }
  *param_2 = *param_2 - 3;
  return;
}
