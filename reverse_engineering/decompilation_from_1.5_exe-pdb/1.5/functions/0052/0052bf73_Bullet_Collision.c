/*
 * Entry: 0052bf73
 * Name: Bullet::Collision
 * Namespace: Bullet
 * Signature: _OBJ76 * Collision(Bullet * this, float * param_1, VECTOR_3D_LONG * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __thiscall
Bullet::Collision(Bullet *this,float *param_1,VECTOR_3D_LONG *param_2,VECTOR_3D *param_3)

{
  _OBJ76 *p_Var1;
  Bullet *pBVar2;
  bool bVar3;
  BBOX *pBVar4;
  GameObject *pGVar5;
  tagENTITY *ptVar6;
  int iVar7;
  VECTOR_3D *unaff_EDI;
  BBOX *pBVar8;
  float10 fVar9;
  Range_Search_Results local_84;
  BBOX local_40;
  BBOX local_28;
  Bullet *local_10;
  _OBJ76 *local_c;
  int *local_8;
  
  if (0.0 < *param_1) {
    iVar7 = this->_padding_;
    fVar9 = (float10)1 / (float10)*param_1;
    local_28.min.x = (float)*(double *)(iVar7 + 0x48);
    local_28.min.y = (float)*(double *)(iVar7 + 0x50);
    local_28.min.z = (float)*(double *)(iVar7 + 0x58);
    local_28.max.x = (float)(((float10)param_2->x - (float10)*(double *)(iVar7 + 0x48)) * fVar9);
    local_28.max.y = (float)(((float10)param_2->y - (float10)*(double *)(iVar7 + 0x50)) * fVar9);
    local_28.max.z = (float)(((float10)param_2->z - (float10)*(double *)(iVar7 + 0x58)) * fVar9);
    local_10 = this;
    pBVar4 = GetOrdBBox(&local_28,(VECTOR_3D *)*param_1,(float)&local_28.max,unaff_EDI);
    local_c = (_OBJ76 *)0x0;
    pBVar8 = &local_40;
    for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
      (pBVar8->min).x = (pBVar4->min).x;
      pBVar4 = (BBOX *)&(pBVar4->min).y;
      pBVar8 = (BBOX *)&(pBVar8->min).y;
    }
    Range::Search(GameObject::objectRange,(double)local_40.min.x,(double)local_40.min.z,
                  (double)local_40.max.x,(double)local_40.max.z,&local_84);
    while (bVar3 = Range_Search_Results::Get_Next_Object(&local_84,&local_8), bVar3) {
      pGVar5 = GameObject::GetObj(*local_8);
      if (pGVar5 != (GameObject *)0x0) {
        ptVar6 = (tagENTITY *)(**(code **)(pGVar5->_padding_ + 0x2c))();
        pBVar2 = local_10;
        p_Var1 = ptVar6->obj76;
        if ((local_10->noHitOwner == false) || ((_OBJ76 *)local_10->_padding_ != p_Var1)) {
          iVar7 = CheckBoxes(&local_40,ptVar6);
          if ((iVar7 != 0) &&
             (bVar3 = IntersectGameObject(&local_28.min,&local_28.max,param_1,param_3,pGVar5,
                                          *(float *)(pBVar2->_padding_ + 0xd4)), bVar3)) {
            param_2->x = (double)(*param_1 * local_28.max.x + local_28.min.x);
            param_2->y = (double)(*param_1 * local_28.max.y + local_28.min.y);
            param_2->z = (double)(*param_1 * local_28.max.z + local_28.min.z);
            local_c = p_Var1;
          }
        }
        else {
          iVar7 = CheckBoxes(&local_40,ptVar6);
          if (iVar7 == 0) {
            pBVar2->noHitOwner = false;
          }
        }
      }
    }
  }
  else {
    local_c = (_OBJ76 *)0x0;
  }
  return local_c;
}
