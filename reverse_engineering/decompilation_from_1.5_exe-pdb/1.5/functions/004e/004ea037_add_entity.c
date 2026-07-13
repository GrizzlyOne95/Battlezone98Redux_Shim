/*
 * Entry: 004ea037
 * Name: add_entity
 * Namespace: Global
 * Signature: tagENTITY * add_entity(_OBJ76 * param_1, short param_2, CLSN_BOXES * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl add_entity(_OBJ76 *param_1,short param_2,CLSN_BOXES *param_3,float *param_4)

{
  VECTOR_3D *pVVar1;
  OBJECT_CLASS_T OVar2;
  tagENTITY *ptVar3;
  int iVar4;
  float *pfVar5;
  float fVar6;
  
  iVar4 = 0;
  if (0 < world_count) {
    ptVar3 = world;
    do {
      if (ptVar3->obj76 == (_OBJ76 *)0x0) {
        ptVar3 = world + iVar4;
        if (ptVar3 != (tagENTITY *)0x0) goto LAB_004ea096;
        break;
      }
      iVar4 = iVar4 + 1;
      ptVar3 = ptVar3 + 1;
    } while (iVar4 < world_count);
  }
  if (world_count == 0x300) {
    DEBUG_systemError(
                     "You had exceeded the maximum number of entities allowed (%d). Please reduce the size of this mission and try again"
                     );
  }
  ptVar3 = world + world_count;
  world_count = world_count + 1;
LAB_004ea096:
  ptVar3->clsnDetails = (void *)0x0;
  ptVar3->obj76 = param_1;
  ptVar3->seqNo = param_2;
  if (param_3 != (CLSN_BOXES *)0x0) {
    ptVar3->cType = CLSN_TYPE_CAR;
    ptVar3->clsnDetails = param_3;
  }
  if (param_4 != (float *)0x0) {
    pfVar5 = ptVar3->lodRanges;
    for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = *param_4;
      param_4 = param_4 + 1;
      pfVar5 = pfVar5 + 1;
    }
    ptVar3->lodRangesSet = 1;
  }
  ptVar3->Bsp_Container = (BSP_CONTAINER *)0x0;
  Cache_Invalidate_Bsp(ptVar3);
  pVVar1 = &(ptVar3->bBox).max;
  get_obj_bounding_box(param_1,&(ptVar3->bBox).min,pVVar1);
  (ptVar3->bSphere).origin.x = ((ptVar3->bBox).min.x + pVVar1->x) * 0.5;
  (ptVar3->bSphere).origin.y = ((ptVar3->bBox).max.y + (ptVar3->bBox).min.y) * 0.5;
  (ptVar3->bSphere).origin.z = ((ptVar3->bBox).max.z + (ptVar3->bBox).min.z) * 0.5;
  fVar6 = get_obj_radius(param_1,(ptVar3->bSphere).origin);
  (ptVar3->bSphere).radius = fVar6;
  iVar4 = is_user_vhcl(param_1);
  if (iVar4 != 0) {
    user_entity_ptr = ptVar3;
  }
  iVar4 = 0;
  if (0 < AddFunc_Count) {
    do {
      (*AddEntFuncs[iVar4])(ptVar3);
      iVar4 = iVar4 + 1;
    } while (iVar4 < AddFunc_Count);
  }
  Vector_Transform(&ptVar3->worldOrigin,&(ptVar3->bSphere).origin,1,&ptVar3->obj76->transform);
  iVar4 = dynamic_object(ptVar3->obj76);
  if (iVar4 != 0) {
    PrecomputeShadowPoly(ptVar3);
  }
  OVar2 = ptVar3->obj76->class_id;
  if ((1 < (int)OVar2) && (((int)OVar2 < 4 || (OVar2 == CLASS_ID_STRUCTURE2)))) {
    CastBuildingShadow(ptVar3);
  }
  ptVar3->mergeNext = (tagENTITY *)0x0;
  ptVar3->mergePrev = (tagENTITY *)0x0;
  ptVar3->mergePoly = (void *)0x0;
  ptVar3->mergeCount = 0;
  ptVar3->animFlags = '\0';
  return ptVar3;
}
