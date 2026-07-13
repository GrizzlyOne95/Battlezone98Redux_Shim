/*
 * Entry: 00474553
 * Name: SetObjCollision
 * Namespace: Global
 * Signature: void SetObjCollision(_OBJ76 * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetObjCollision(_OBJ76 *param_1,MAT_3D *param_2)

{
  MAT_3D *pMVar1;
  CLSN_GEOM *pCVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  MAT_3D *pMVar6;
  MAT_3D local_80;
  MAT_3D local_40;
  
  do {
    if (param_1 == (_OBJ76 *)0x0) {
      return;
    }
    pMVar1 = Matrix_Multiply(&local_40,&param_1->transform,param_2);
    pMVar6 = &local_80;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar1->right_x;
      pMVar1 = (MAT_3D *)&pMVar1->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    uVar5 = param_1->flags & 0xf000;
    if (uVar5 == 0x3000) {
      Cgeom_Delete(param_1);
    }
    if (uVar5 == 0) {
      uVar5 = CurrentDefaultCollision;
    }
    if (((uVar5 == 0x1000) || (param_1->class_id == CLASS_ID_NONCOLLIDABLE)) ||
       ((param_1->flags & 1) != 0)) {
      param_1->flags = param_1->flags & 0xffff1fff | 0x1000;
    }
    else {
      iVar4 = GeoCache_SelectLOD(param_1,0);
      if ((iVar4 == 0) || (param_1->geom == (_GEOMETRY *)0x0)) {
        if ((uVar5 != 0x4000) && (uVar5 != 0x5000)) goto LAB_0047460d;
      }
      else if (uVar5 == 0x3000) {
        if (param_1->geom->vertex_count < 3) {
LAB_0047460d:
          uVar3 = param_1->flags & 0xffff1fff | 0x1000;
        }
        else {
          pCVar2 = Cgeom_Create(param_1,&local_80);
          param_1->clsnInfo = pCVar2;
          if (pCVar2 == (CLSN_GEOM *)0x0) goto LAB_0047460d;
          uVar3 = param_1->flags & 0xffff3fff | 0x3000;
        }
        param_1->flags = uVar3;
        goto LAB_00474649;
      }
      param_1->flags = param_1->flags ^ (param_1->flags ^ uVar5) & 0xf000;
    }
LAB_00474649:
    if (param_1->child != (_OBJ76 *)0x0) {
      SetObjCollision(param_1->child,&local_80);
    }
    param_1 = param_1->sibling;
  } while( true );
}
