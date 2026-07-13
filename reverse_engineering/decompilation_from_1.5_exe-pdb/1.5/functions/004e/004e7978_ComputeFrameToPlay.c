/*
 * Entry: 004e7978
 * Name: ComputeFrameToPlay
 * Namespace: Global
 * Signature: float ComputeFrameToPlay(tagANIMOBJ_ACTIVE_LIST * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ComputeFrameToPlay(tagANIMOBJ_ACTIVE_LIST *param_1)

{
  int iVar1;
  float fVar2;
  int extraout_EAX;
  int iVar3;
  int extraout_EAX_00;
  int iVar4;
  float fVar5;
  
  fVar5 = TimeStep();
  iVar3 = param_1->lastFrame;
  fVar5 = fVar5 * param_1->frameRate;
  iVar4 = param_1->startFrame;
  if (iVar4 < iVar3) {
    fVar5 = fVar5 + param_1->curFrame;
    param_1->curFrame = fVar5;
    fVar2 = (float)iVar3;
    if (fVar2 < fVar5) {
      iVar1 = param_1->loopsToDo;
      if (iVar1 == 0) {
        param_1->curFrame = fVar2;
      }
      else {
        param_1->curFrame = (float)(iVar4 - iVar3) + fVar5;
        if (0 < iVar1) {
          param_1->loopsToDo = iVar1 + -1;
        }
      }
    }
    if (param_1->loopsToDo == -1) goto LAB_004e7a60;
    ceil((double)(fVar2 - param_1->curFrame));
    _ftol2_sse();
    iVar4 = param_1->lastFrame - param_1->startFrame;
    iVar3 = extraout_EAX;
  }
  else {
    fVar5 = param_1->curFrame - fVar5;
    param_1->curFrame = fVar5;
    fVar2 = (float)iVar3;
    if (fVar5 < fVar2) {
      iVar1 = param_1->loopsToDo;
      if (iVar1 == 0) {
        param_1->curFrame = fVar2;
      }
      else {
        param_1->curFrame = (float)(iVar4 - iVar3) + fVar5;
        if (0 < iVar1) {
          param_1->loopsToDo = iVar1 + -1;
        }
      }
    }
    if (param_1->loopsToDo == -1) goto LAB_004e7a60;
    ceil((double)(param_1->curFrame - fVar2));
    _ftol2_sse();
    iVar4 = param_1->startFrame - param_1->lastFrame;
    iVar3 = extraout_EAX_00;
  }
  param_1->framesToDo = iVar3 + (iVar4 + 1) * param_1->loopsToDo;
LAB_004e7a60:
  return param_1->curFrame;
}
