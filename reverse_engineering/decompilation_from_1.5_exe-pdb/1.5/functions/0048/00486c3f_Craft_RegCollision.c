/*
 * Entry: 00486c3f
 * Name: Craft::RegCollision
 * Namespace: Craft
 * Signature: bool RegCollision(Craft * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
Craft::RegCollision(Craft *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  char cVar1;
  _OBJ76 *p_Var2;
  EULER *pEVar3;
  int iVar4;
  CLSN_INFO *pCVar5;
  CLSN_INFO *pCVar6;
  float *pfVar7;
  EULER local_bc;
  float local_74 [6];
  float local_5c;
  float local_58;
  float local_54;
  VECTOR_3D local_2c;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  
  if (((((*(byte *)(this->_padding_ + 0x14) & 0x20) != 0) || (param_1->class_id == CLASS_ID_POWERUP)
       ) || ((param_1->class_id == CLASS_ID_PERSON && ((param_1->flags & 0x200) != 0)))) ||
     (((((char)this->_padding_ != '\0' && (this->_padding_ != 0)) &&
       (p_Var2 = (_OBJ76 *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x30))(),
       param_1 == p_Var2)) || ((this->vhcl->flags & 0x20000) != 0)))) {
    return false;
  }
  pCVar5 = param_2;
  pCVar6 = &this->vhcl->clsn_info;
  for (iVar4 = 0x1e; iVar4 != 0; iVar4 = iVar4 + -1) {
    pCVar6->collided = pCVar5->collided;
    pCVar5 = (CLSN_INFO *)&pCVar5->obj;
    pCVar6 = (CLSN_INFO *)&pCVar6->obj;
  }
  iVar4 = dynamic_object(param_1);
  if (iVar4 != 0) {
    p_Var2 = obj_get_root(param_1);
    iVar4 = IsCraft(p_Var2);
    if ((iVar4 == 0) || (cVar1 = (**(code **)(*(int *)p_Var2->gameObj + 0x68))(), cVar1 != '\0'))
    goto LAB_00486cfe;
  }
  (this->vhcl->clsn_info).euler.mass = 0.0;
LAB_00486cfe:
  local_20 = (float)this->_padding_;
  local_1c = (float)this->_padding_;
  local_18 = (float)this->_padding_;
  pEVar3 = ClassGetEuler(&local_bc,param_1);
  pfVar7 = local_74;
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar7 = pEVar3->mass;
    pEVar3 = (EULER *)&pEVar3->mass_inv;
    pfVar7 = pfVar7 + 1;
  }
  local_2c.x = local_5c - local_20;
  local_2c.y = local_58 - local_1c;
  local_2c.z = local_54 - local_18;
  local_14 = local_2c.x;
  local_10 = local_2c.y;
  local_c = local_2c.z;
  Damage_Resolve((_OBJ76 *)this->_padding_,param_1,&local_2c,&param_2->normal,&param_2->point);
  return true;
}
