/*
 * Entry: 004e731c
 * Name: AnimObj_Start
 * Namespace: Global
 * Signature: long AnimObj_Start(void * param_1, int param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_Start(void *param_1,int param_2,int *param_3)

{
  tagANIMOBJ_HEADER *ptVar1;
  tagANIMOBJ_ACTIVE_LIST *ptVar2;
  tagANIMOBJ_ANIM *ptVar3;
  int iVar4;
  int iVar5;
  
  *param_3 = -1;
  if (0x1ff < AnimObj_ActiveCount) {
    DEBUG_systemError("AnimObj_Start() active anim list overflow");
    return -1;
  }
  iVar5 = 0;
  if (AnimCount < 1) {
    return -1;
  }
  while (((ptVar1 = AnimList[iVar5], ptVar1->obj != param_1 || (ptVar1->entity == (int *)0x0)) ||
         (*(void **)ptVar1->entity != param_1))) {
    iVar5 = iVar5 + 1;
    if (AnimCount <= iVar5) {
      return -1;
    }
  }
  iVar5 = 0;
  if (ptVar1->animCount < 1) {
    return -1;
  }
  ptVar3 = ptVar1->animPtr;
  do {
    if (ptVar3->animIndex == param_2) {
      iVar5 = 0;
      ptVar2 = AnimActiveList;
      do {
        if (ptVar2->status == 0) {
          *(undefined1 *)((int)ptVar1->entity + 7) = 1;
          ptVar2->status = 1;
          ptVar2->animHeader = ptVar1;
          ptVar2->frameRate = ptVar3->frameRate;
          ptVar2->startFrame = ptVar3->startFrame;
          iVar4 = ptVar3->frameCount;
          if (iVar4 < 1) {
            ptVar2->lastFrame = ptVar3->startFrame + 1 + iVar4;
            iVar4 = -ptVar3->frameCount;
          }
          else {
            ptVar2->lastFrame = ptVar3->startFrame + -1 + iVar4;
            iVar4 = ptVar3->frameCount;
          }
          ptVar2->framesToDo = iVar4;
          ptVar2->curFrame = (float)ptVar2->startFrame;
          if (ptVar3->loopCount < 1) {
            iVar4 = -1;
          }
          else {
            iVar4 = ptVar3->loopCount + -1;
          }
          ptVar2->loopsToDo = iVar4;
          *param_3 = iVar5;
          AnimObj_ActiveCount = AnimObj_ActiveCount + 1;
          return 0;
        }
        ptVar2 = ptVar2 + 1;
        iVar5 = iVar5 + 1;
      } while ((int)ptVar2 < 0xbac8e8);
      DEBUG_systemWarning("AnimObj_Start() found no empty slots in ActiveList");
      return -1;
    }
    iVar5 = iVar5 + 1;
    ptVar3 = ptVar3 + 1;
  } while (iVar5 < ptVar1->animCount);
  return -1;
}
