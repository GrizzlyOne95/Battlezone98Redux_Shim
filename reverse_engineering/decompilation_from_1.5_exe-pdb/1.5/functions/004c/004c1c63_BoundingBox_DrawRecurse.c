/*
 * Entry: 004c1c63
 * Name: BoundingBox::DrawRecurse
 * Namespace: BoundingBox
 * Signature: void DrawRecurse(BoundingBox * this, _OBJ76 * param_1, MAT_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
BoundingBox::DrawRecurse(BoundingBox *this,_OBJ76 *param_1,MAT_3D *param_2,long param_3)

{
  float fVar1;
  MAT_3D *pMVar2;
  uint uVar3;
  int iVar4;
  MAT_3D *pMVar5;
  MAT_3D local_c8;
  MAT_3D local_88;
  MAT_3D local_48;
  BoundingBox *local_8;
  
  local_8 = this;
  do {
    if (param_1 == (_OBJ76 *)0x0) {
      return;
    }
    if (param_2 == (MAT_3D *)0x0) {
      pMVar2 = &param_1->transform;
    }
    else {
      pMVar2 = Matrix_Multiply(&local_c8,&param_1->transform,param_2);
      pMVar5 = &local_88;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        pMVar5->right_x = pMVar2->right_x;
        pMVar2 = (MAT_3D *)&pMVar2->right_y;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
      }
      pMVar2 = &local_88;
    }
    uVar3 = param_1->flags & 0xf000;
    pMVar5 = &local_48;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar5->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
    if (uVar3 == 0x2000) {
      DrawBox(local_8,&(param_1->bBox).min,&(param_1->bBox).max,&local_48,param_3);
    }
    else if (uVar3 == 0x3000) {
      DrawBox(local_8,&(param_1->bBox).min,&(param_1->bBox).max,&local_48,
              DisplayInterface::colorGrey);
      DrawSphere(local_8,&(param_1->bSphere).origin,(param_1->bSphere).radius,&local_48,
                 DisplayInterface::colorDkGrey);
      DrawGeom(local_8,param_1->clsnInfo,&local_48,param_3);
    }
    else {
      if (uVar3 == 0x4000) {
        fVar1 = (param_1->bSphere).radius;
      }
      else {
        if (uVar3 != 0x5000) goto LAB_004c1d85;
        fVar1 = (param_1->bSphere).radius * 0.75;
      }
      DrawSphere(local_8,&(param_1->bSphere).origin,fVar1,&local_48,param_3);
    }
LAB_004c1d85:
    if (param_1->child != (_OBJ76 *)0x0) {
      DrawRecurse(local_8,param_1->child,&local_48,param_3);
    }
    param_1 = param_1->sibling;
  } while( true );
}
