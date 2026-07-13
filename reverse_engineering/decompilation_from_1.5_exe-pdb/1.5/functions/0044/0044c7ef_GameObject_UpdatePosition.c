/*
 * Entry: 0044c7ef
 * Name: GameObject::UpdatePosition
 * Namespace: GameObject
 * Signature: void UpdatePosition(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::UpdatePosition(GameObject *this)

{
  float fVar1;
  tagENTITY *ptVar2;
  MAT_3D *pMVar3;
  SPHERE *pSVar4;
  int iVar5;
  MAT_3D *pMVar6;
  float *pfVar7;
  MAT_3D local_c8;
  MAT_3D local_88;
  float local_48 [4];
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  double local_20;
  double local_18;
  double local_10;
  SPHERE *local_8;
  
  ptVar2 = this->ent;
  if (ptVar2 == (tagENTITY *)0x0) {
    local_8 = &this->obj->bSphere;
  }
  else {
    local_8 = &ptVar2->bSphere;
  }
  if (ptVar2 == (tagENTITY *)0x0) {
    pMVar3 = obj_rel_parent_matrix(&local_c8,this->obj,(_OBJ76 *)0x0);
    pMVar6 = &local_88;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar6->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    pMVar3 = &local_88;
    pSVar4 = local_8;
  }
  else {
    pMVar3 = &this->obj->transform;
    pSVar4 = local_8;
  }
  fVar1 = (pSVar4->origin).x;
  pfVar7 = local_48;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar7 = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pfVar7 = pfVar7 + 1;
  }
  (this->pos).x =
       local_30 * (pSVar4->origin).z + (pSVar4->origin).y * local_48[3] + fVar1 * local_48[0] +
       (float)local_20;
  (this->pos).y =
       local_2c * (pSVar4->origin).z +
       (pSVar4->origin).y * local_38 + (pSVar4->origin).x * local_48[1] + (float)local_18;
  ptVar2 = this->ent;
  (this->pos).z =
       local_28 * (pSVar4->origin).z +
       (pSVar4->origin).y * local_34 + (pSVar4->origin).x * local_48[2] + (float)local_10;
  if (ptVar2 != (tagENTITY *)0x0) {
    (ptVar2->bBox).min.x = (this->pos).x - (ptVar2->bSphere).radius;
    (this->ent->bBox).max.x = (this->ent->bSphere).radius + (this->pos).x;
    (this->ent->bBox).min.y = (this->pos).y - (this->ent->bSphere).radius;
    (this->ent->bBox).max.y = (this->ent->bSphere).radius + (this->pos).y;
    (this->ent->bBox).min.z = (this->pos).z - (this->ent->bSphere).radius;
    (this->ent->bBox).max.z = (this->ent->bSphere).radius + (this->pos).z;
  }
  return;
}
