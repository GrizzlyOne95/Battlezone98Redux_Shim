/*
 * Entry: 004ed4ca
 * Name: Add_Inter_Object_Info
 * Namespace: Global
 * Signature: INTER_OBJECT_NODE * Add_Inter_Object_Info(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

INTER_OBJECT_NODE * __cdecl Add_Inter_Object_Info(_OBJ76 *param_1,_OBJ76 *param_2)

{
  INTER_OBJECT_NODE *pIVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  _OBJ76 *in_EAX;
  OBJECT_NODE *pOVar6;
  _OBJ76 *unaff_EDI;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  OBJECT_NODE *local_8;
  
  local_8 = Find_Object_Info(unaff_EDI);
  if (local_8 == (OBJECT_NODE *)0x0) {
    local_8 = Add_Object_Info(unaff_EDI);
  }
  pOVar6 = Find_Object_Info(unaff_EDI);
  if (pOVar6 == (OBJECT_NODE *)0x0) {
    pOVar6 = Add_Object_Info(unaff_EDI);
  }
  inter_objectdb[io_nextfree].next =
       inter_object_table[(((uint)param_1 ^ (uint)in_EAX) * 0x6cd + 0xaab) % 0x9c7];
  inter_object_table[(((uint)param_1 ^ (uint)in_EAX) * 0x6cd + 0xaab) % 0x9c7] = io_nextfree;
  pIVar1 = inter_objectdb + io_nextfree;
  pIVar1->objA = param_1;
  inter_objectdb[io_nextfree].objB = in_EAX;
  fVar2 = (local_8->sphere).origin.x;
  fVar3 = (local_8->sphere).origin.z;
  fVar4 = (pOVar6->sphere).origin.x;
  fVar5 = (pOVar6->sphere).origin.z;
  fVar7 = (float10)fVar2 - (float10)fVar4;
  fVar8 = (float10)(local_8->sphere).origin.y - (float10)(pOVar6->sphere).origin.y;
  fVar9 = (float10)fVar3 - (float10)fVar5;
  inter_objectdb[io_nextfree].dirvecBA.x = (float)fVar7;
  inter_objectdb[io_nextfree].dirvecBA.y = (float)fVar8;
  inter_objectdb[io_nextfree].dirvecBA.z = (float)fVar9;
  inter_objectdb[io_nextfree].dirvecAB.x = (float)-fVar7;
  inter_objectdb[io_nextfree].dirvecAB.y = (float)-fVar8;
  inter_objectdb[io_nextfree].dirvecAB.z = (float)-fVar9;
  fVar11 = (float10)0;
  if ((fVar11 == fVar7) && (fVar11 == fVar9)) {
    inter_objectdb[io_nextfree].aimBA = (float)fVar11;
  }
  else {
    fVar10 = (float10)fpatan(fVar7,fVar9);
    inter_objectdb[io_nextfree].aimBA = (float)fVar10;
  }
  inter_objectdb[io_nextfree].dist_2D = (float)SQRT(fVar9 * fVar9 + fVar7 * fVar7);
  inter_objectdb[io_nextfree].dist_3D = (float)SQRT(fVar8 * fVar8 + fVar9 * fVar9 + fVar7 * fVar7);
  fVar7 = (float10)fVar4 - (float10)fVar2;
  fVar8 = (float10)fVar5 - (float10)fVar3;
  if ((fVar11 != fVar7) || (fVar11 != fVar8)) {
    fVar11 = (float10)fpatan(fVar7,fVar8);
  }
  inter_objectdb[io_nextfree].aimAB = (float)fVar11;
  io_nextfree = io_nextfree + 1;
  return pIVar1;
}
