/*
 * Entry: 004e7a66
 * Name: AnimObj_Simulate
 * Namespace: Global
 * Signature: long AnimObj_Simulate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_Simulate(void)

{
  tagANIMOBJ_HEADER *ptVar1;
  _OBJ76 *p_Var2;
  tagENTITY *ptVar3;
  tagANIMOBJ_ACTIVE_LIST *ptVar4;
  float fVar5;
  int local_4;
  
  local_4 = 0;
  ptVar4 = AnimActiveList;
  do {
    if (AnimObj_ActiveCount <= local_4) {
      return 0;
    }
    if ((ptVar4->status != 0) && (local_4 = local_4 + 1, ptVar4->status == 1)) {
      ptVar1 = ptVar4->animHeader;
      p_Var2 = ptVar1->obj;
      if ((ptVar1->entity == (void *)0x0) ||
         ((p_Var2 == (_OBJ76 *)0x0 || (ptVar3 = FindObjectEntity(p_Var2), ptVar3 != ptVar1->entity))
         )) {
        ptVar4->status = 3;
      }
      else {
        if (0 < ptVar4->framesToDo) {
          fVar5 = ComputeFrameToPlay(ptVar4);
          TraverseObjTree(p_Var2,0,ptVar4,fVar5);
          Cache_Invalidate_Bsp(ptVar1->entity);
          goto LAB_004e7ae0;
        }
        ptVar4->status = 2;
      }
      ptVar4->framesToDo = 0;
    }
LAB_004e7ae0:
    ptVar4 = ptVar4 + 1;
    if (0xbac8e7 < (int)ptVar4) {
      return 0;
    }
  } while( true );
}
