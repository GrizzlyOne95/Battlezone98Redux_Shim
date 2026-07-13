/*
 * Entry: 004e78f5
 * Name: TraverseObjTree
 * Namespace: Global
 * Signature: long TraverseObjTree(_OBJ76 * param_1, int param_2, tagANIMOBJ_ACTIVE_LIST * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
TraverseObjTree(_OBJ76 *param_1,int param_2,tagANIMOBJ_ACTIVE_LIST *param_3,float param_4)

{
  tagANIMOBJ_HEADER *ptVar1;
  int iVar2;
  _OBJ76 *p_Var3;
  tagANIMOBJ_MESH *ptVar4;
  float unaff_EBX;
  
  ptVar1 = param_3->animHeader;
  p_Var3 = param_1;
  do {
    if (p_Var3 == (_OBJ76 *)0x0) {
      return 0;
    }
    iVar2 = ptVar1->meshCount;
    param_1 = (_OBJ76 *)0x0;
    if (0 < iVar2) {
      ptVar4 = ptVar1->meshPtr;
      do {
        if ((*(int *)ptVar4->meshName == (int)p_Var3->id) &&
           (*(int *)(ptVar4->meshName + 4) == *(int *)((int)&p_Var3->id + 4))) {
          AnimateMeshTransform
                    (p_Var3,(tagANIMOBJ_MESH *)param_3,(tagANIMOBJ_ACTIVE_LIST *)param_4,unaff_EBX);
          break;
        }
        param_1 = (_OBJ76 *)((int)&param_1->objHandle + 1);
        ptVar4 = ptVar4 + 1;
      } while ((int)param_1 < iVar2);
    }
    if (p_Var3->child != (_OBJ76 *)0x0) {
      TraverseObjTree(p_Var3->child,param_2,param_3,param_4);
    }
    p_Var3 = p_Var3->sibling;
  } while( true );
}
