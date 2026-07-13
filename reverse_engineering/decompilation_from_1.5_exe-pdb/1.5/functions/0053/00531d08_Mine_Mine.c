/*
 * Entry: 00531d08
 * Name: Mine::Mine
 * Namespace: Mine
 * Signature: Mine * Mine(Mine * this, _OBJ76 * param_1, MineClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Mine * __thiscall Mine::Mine(Mine *this,_OBJ76 *param_1,MineClass *param_2)

{
  double *pdVar1;
  VECTOR_3D_LONG VVar2;
  MineClass *pMVar3;
  MAT_3D *pMVar4;
  int iVar5;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar6;
  MAT_3D local_84;
  double local_44;
  double local_3c;
  double local_34;
  VECTOR_3D local_2c;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float local_14;
  float local_10;
  float local_c;
  Mine *local_8;
  
  pMVar3 = param_2;
  local_8 = this;
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  DeleteCollisionEntity((tagENTITY *)this->_padding_);
  this->lifeTimer = pMVar3->lifeSpan;
  pdVar1 = &(param_1->transform).posit_x;
  local_44 = *pdVar1;
  local_3c = (param_1->transform).posit_y;
  local_34 = (param_1->transform).posit_z;
  VVar2.z._4_4_ = (int)((ulonglong)local_34 >> 0x20);
  VVar2._0_20_ = *(undefined1 (*) [20])pdVar1;
  Floor_GetFloor(VVar2,(float *)&param_2,&local_2c);
  local_3c = (double)(float)param_2;
  local_20 = (param_1->transform).front_x;
  fStack_1c = (param_1->transform).front_y;
  fStack_18 = (param_1->transform).front_z;
  local_14 = local_20;
  local_10 = fStack_1c;
  local_c = fStack_18;
  pMVar4 = Build_Orthogonal_Matrix(&local_84,unaff_EDI,unaff_ESI);
  pMVar6 = &param_1->transform;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pMVar6->right_x = pMVar4->right_x;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
  }
  (param_1->transform).posit_x = local_44;
  (param_1->transform).posit_y = local_3c;
  (param_1->transform).posit_z = local_34;
  GameObject::UpdatePosition((GameObject *)local_8);
  return local_8;
}
