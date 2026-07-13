/*
 * Entry: 00482d9c
 * Name: Building::RegCollision
 * Namespace: Building
 * Signature: bool RegCollision(Building * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
Building::RegCollision(Building *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  undefined1 uVar1;
  _OBJ76 *p_Var2;
  EULER *pEVar3;
  int *piVar4;
  int iVar5;
  float *pfVar6;
  EULER local_a0;
  float local_58 [6];
  float local_40;
  float fStack_3c;
  float fStack_38;
  VECTOR_3D local_10;
  
  p_Var2 = this->root;
  if ((_OBJ76 *)this->_padding_ == p_Var2) {
    if ((((char)this->_padding_ != '\0') && (this->_padding_ != 0)) &&
       (p_Var2 = (_OBJ76 *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x30))(),
       param_1 == p_Var2)) {
      return false;
    }
    pEVar3 = ClassGetEuler(&local_a0,param_1);
    pfVar6 = local_58;
    for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar6 = pEVar3->mass;
      pEVar3 = (EULER *)&pEVar3->mass_inv;
      pfVar6 = pfVar6 + 1;
    }
    local_10.x = local_40;
    local_10.y = fStack_3c;
    local_10.z = fStack_38;
    Damage_Resolve((_OBJ76 *)this->_padding_,param_1,&local_10,&param_2->normal,&param_2->point);
    uVar1 = 1;
  }
  else {
    if (p_Var2 == (_OBJ76 *)0x0) {
      piVar4 = (int *)0x0;
    }
    else {
      piVar4 = p_Var2->gameObj;
    }
    uVar1 = (**(code **)(*piVar4 + 0x48))(param_1,param_2,param_3);
  }
  return (bool)uVar1;
}
