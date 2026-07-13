/*
 * Entry: 004e71aa
 * Name: AnimObj_Add
 * Namespace: Global
 * Signature: long AnimObj_Add(void * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_Add(void *param_1,void *param_2,void *param_3)

{
  tagANIMOBJ_HEADER *ptVar1;
  int iVar2;
  int iVar3;
  size_t _Size;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)((int)param_1 + 0x18) * 0x94;
  iVar2 = *(int *)((int)param_1 + 0x1c) * 0x84;
  iVar3 = *(int *)((int)param_1 + 0x20) * 0x14;
  iVar5 = *(int *)((int)param_1 + 0x24) * 0x10;
  _Size = (*(int *)((int)param_1 + 0x28) + 4) * 0x10 + iVar5 + iVar3 + iVar2 + iVar4;
  if (((*(int *)((int)param_1 + 0x1c) * *(int *)((int)param_1 + 0x18) <
        *(int *)((int)param_1 + 0x28)) || (*(int *)((int)param_1 + 0x20) != 0)) ||
     (*(int *)((int)param_1 + 0x24) != 0)) {
    ptVar1 = malloc(_Size);
    if (ptVar1 == (tagANIMOBJ_HEADER *)0x0) {
      DEBUG_systemError("AnimObj_Add() anim list malloc failed");
      return -1;
    }
    memcpy(ptVar1,(int)param_1 + 8,_Size);
    AnimList[AnimCount] = ptVar1;
    ptVar1->animPtr = (tagANIMOBJ_ANIM *)(ptVar1 + 1);
    ptVar1->meshPtr = (tagANIMOBJ_MESH *)((int)ptVar1 + iVar4 + 0x40);
    ptVar1->rotKeyPtr = (tagANIMOBJ_ROTKEY *)((int)ptVar1 + iVar4 + iVar2 + 0x40);
    ptVar1->sclKeyPtr = (tagANIMOBJ_SCLKEY *)((int)ptVar1 + iVar4 + iVar2 + iVar3 + 0x40);
    AnimCount = AnimCount + 1;
    ptVar1->posKeyPtr = (tagANIMOBJ_POSKEY *)((int)ptVar1 + iVar4 + iVar2 + iVar3 + iVar5 + 0x40);
    ptVar1->obj = *(void **)param_2;
  }
  return 0;
}
