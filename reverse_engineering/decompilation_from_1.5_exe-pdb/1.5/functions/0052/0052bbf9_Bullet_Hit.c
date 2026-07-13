/*
 * Entry: 0052bbf9
 * Name: Bullet::Hit
 * Namespace: Bullet
 * Signature: void Hit(Bullet * this, GameObject * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Bullet::Hit(Bullet *this,GameObject *param_1,VECTOR_3D *param_2)

{
  uint *puVar1;
  OBJECT_CLASS_T OVar2;
  bool bVar3;
  char cVar4;
  _OBJ76 *p_Var5;
  MAT_3D *pMVar6;
  int iVar7;
  int iVar8;
  ExplosionClass *pEVar9;
  VECTOR_3D *unaff_ESI;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar10;
  MAT_3D local_9c;
  MAT_3D local_5c;
  float local_1c;
  float local_18;
  float local_14;
  VECTOR_3D local_10;
  
  if (param_1 == (GameObject *)0x0) {
    pMVar6 = Build_Orthogonal_Matrix(&local_9c,(VECTOR_3D *)unaff_EDI,unaff_ESI);
    iVar7 = this->_padding_;
    pMVar10 = &local_5c;
    for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
      pMVar10->right_x = pMVar6->right_x;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    local_5c.posit_x = *(double *)(iVar7 + 0x48);
    local_5c.posit_y = *(double *)(iVar7 + 0x50) + 0.009999999776482582;
    local_5c.posit_z = *(double *)(iVar7 + 0x58);
    pEVar9 = *(ExplosionClass **)(this->_padding_ + 0x3c);
    if (pEVar9 != (ExplosionClass *)0x0) {
      ExplosionClass::Build(pEVar9,&local_5c,(_OBJ76 *)this->_padding_);
    }
    goto LAB_0052bd64;
  }
  p_Var5 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
  pMVar6 = Matrix_Inverse(&local_9c,unaff_EDI);
  iVar7 = this->_padding_;
  pMVar10 = &local_5c;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    pMVar10->right_x = pMVar6->right_x;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  local_1c = (float)*(double *)(iVar7 + 0x48);
  local_18 = (float)*(double *)(iVar7 + 0x50);
  local_14 = (float)*(double *)(iVar7 + 0x58);
  local_10.x = local_1c;
  local_10.y = local_18;
  local_10.z = local_14;
  Vector_Transform(&local_10,&local_10,1,&local_5c);
  (**(code **)(param_1->_padding_ + 0x38))(&this->_padding_,&local_10);
  param_1->hitOrdClass = (OrdnanceClass *)this->_padding_;
  OVar2 = p_Var5->class_id;
  if (OVar2 == CLASS_ID_HELICOPTER) {
LAB_0052bcbf:
    pEVar9 = *(ExplosionClass **)(this->_padding_ + 0x40);
  }
  else if (OVar2 == CLASS_ID_STRUCTURE1) {
LAB_0052bcb7:
    pEVar9 = *(ExplosionClass **)(this->_padding_ + 0x44);
  }
  else {
    if (2 < (int)OVar2) {
      if ((int)OVar2 < 8) goto LAB_0052bcbf;
      if ((OVar2 == CLASS_ID_BRIDGE) || (OVar2 == CLASS_ID_STRUCTURE2)) goto LAB_0052bcb7;
    }
    pEVar9 = *(ExplosionClass **)(this->_padding_ + 0x3c);
  }
  if (pEVar9 != (ExplosionClass *)0x0) {
    ExplosionClass::Build(pEVar9,(MAT_3D *)(this->_padding_ + 0x20),(_OBJ76 *)this->_padding_);
  }
  bVar3 = DistributedObject::IsLocal((DistributedObject *)&param_1->_padding_);
  if (bVar3) {
    iVar7 = dynamic_object(p_Var5);
    if (iVar7 != 0) {
      iVar7 = IsCraft(p_Var5);
      if (iVar7 != 0) {
        cVar4 = (**(code **)(param_1->_padding_ + 0x68))();
        if (cVar4 == '\0') goto LAB_0052bd64;
      }
      puVar1 = (uint *)(this->_padding_ + 0x14);
      *puVar1 = *puVar1 | 2;
    }
  }
LAB_0052bd64:
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 | 0x200;
  return;
}
