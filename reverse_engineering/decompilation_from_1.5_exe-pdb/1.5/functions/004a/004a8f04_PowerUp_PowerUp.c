/*
 * Entry: 004a8f04
 * Name: PowerUp::PowerUp
 * Namespace: PowerUp
 * Signature: PowerUp * PowerUp(PowerUp * this, _OBJ76 * param_1, PowerUpClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerUp * __thiscall PowerUp::PowerUp(PowerUp *this,_OBJ76 *param_1,PowerUpClass *param_2)

{
  int iVar1;
  int *piVar2;
  _OBJ76 *p_Var3;
  VEHICLE *pVVar4;
  
  GameObject::GameObject((GameObject *)this,param_1,(GameObjectClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  pVVar4 = get_obj_vhcl(param_1);
  this->vhcl = pVVar4;
  pVVar4->entity = (tagENTITY *)this->_padding_;
  GameObject::SetCommand((GameObject *)this,CMD_NONE);
  iVar1 = this->_padding_;
  if (((iVar1 == 0) || (*(int *)(iVar1 + 0x24) != 1)) ||
     (piVar2 = *(int **)(iVar1 + 0x28), piVar2 == (int *)0x0)) {
    p_Var3 = (_OBJ76 *)this->_padding_;
    get_obj_bounding_box(p_Var3,&(p_Var3->bBox).min,&(p_Var3->bBox).max);
  }
  else {
    *(int *)(this->_padding_ + 0xd8) = piVar2[3];
    *(int *)(this->_padding_ + 0xdc) = piVar2[7];
    *(int *)(this->_padding_ + 0xe0) = piVar2[0xb];
    *(int *)(this->_padding_ + 0xe4) = piVar2[*piVar2 + 2];
    *(int *)(this->_padding_ + 0xe8) = piVar2[piVar2[1] + 6];
    *(int *)(this->_padding_ + 0xec) = piVar2[piVar2[2] + 10];
  }
  return this;
}
