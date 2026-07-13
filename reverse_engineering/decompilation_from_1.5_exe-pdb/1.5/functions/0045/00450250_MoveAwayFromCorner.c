/*
 * Entry: 00450250
 * Name: MoveAwayFromCorner
 * Namespace: Global
 * Signature: void MoveAwayFromCorner(Strip * param_1, Strip * param_2, Strip * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MoveAwayFromCorner(Strip *param_1,Strip *param_2,Strip *param_3)

{
  float fVar1;
  Strip *pSVar2;
  Strip *pSVar3;
  Strip *pSVar4;
  Strip *extraout_EDX;
  Strip *pSVar5;
  Strip *pSVar6;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  pSVar5 = param_2;
  pSVar4 = param_3;
  pSVar6 = (Strip *)0x0;
  if (param_3 == lastIntNode) {
    pSVar4 = lastIntNextNode;
    pSVar6 = param_3;
  }
  if (param_1->x1 == param_2->x0) {
    uVar7 = 0;
  }
  else if (param_1->z1 == param_2->z0) {
    uVar7 = 1;
  }
  else {
    uVar7 = 2;
    if (param_1->x0 != param_2->x1) {
      uVar7 = 3;
    }
  }
  param_3 = (Strip *)0x0;
  param_2 = (Strip *)0x0;
  switch(uVar7) {
  case 0:
    fVar10 = pSVar5->z1;
    fVar9 = pSVar5->x0;
    fVar8 = pSVar5->z0;
    break;
  case 1:
    fVar10 = pSVar5->z0;
    fVar9 = pSVar5->x1;
    fVar8 = pSVar5->z0;
    break;
  case 2:
    fVar10 = pSVar5->z1;
    fVar9 = pSVar5->x1;
    fVar8 = pSVar5->z0;
    fVar1 = pSVar5->x1;
    goto LAB_00450353;
  case 3:
    fVar10 = pSVar5->z1;
    fVar9 = pSVar5->x1;
    fVar8 = pSVar5->z1;
    break;
  default:
    goto switchD_004502c0_default;
  }
  fVar1 = pSVar5->x0;
LAB_00450353:
  Intersects(pSVar4->x,pSVar4->z,param_1->x,param_1->z,fVar1,fVar8,fVar9,fVar10,(float *)&param_2,
             (float *)&param_3);
  pSVar5 = extraout_EDX;
switchD_004502c0_default:
  pSVar4 = (Strip *)0x0;
  pSVar2 = pSVar4;
  pSVar3 = pSVar4;
  switch(uVar7) {
  case 0:
  case 2:
    pSVar4 = (Strip *)pSVar5->z0;
    if ((float)pSVar4 < param_1->z0) {
      pSVar4 = (Strip *)param_1->z0;
    }
    pSVar2 = (Strip *)param_1->z1;
    pSVar3 = param_3;
    if (pSVar5->z1 < (float)pSVar2) {
      pSVar2 = (Strip *)pSVar5->z1;
    }
    break;
  case 1:
  case 3:
    pSVar4 = (Strip *)pSVar5->x0;
    if ((float)pSVar4 < param_1->x0) {
      pSVar4 = (Strip *)param_1->x0;
    }
    pSVar2 = (Strip *)param_1->x1;
    pSVar3 = param_2;
    if (pSVar5->x1 < (float)pSVar2) {
      pSVar2 = (Strip *)pSVar5->x1;
      pSVar3 = param_2;
    }
  }
  fVar10 = (float)pSVar2 - (float)pSVar4;
  if (NAN(fVar10) || 3.0 < fVar10 == (fVar10 == 3.0)) {
    if (fVar10 < 2.0) {
      fVar10 = 0.5;
    }
    else {
      fVar10 = 1.0;
    }
  }
  else {
    fVar10 = 1.5;
  }
  pSVar4 = (Strip *)(fVar10 + (float)pSVar4);
  pSVar2 = (Strip *)((float)pSVar2 - fVar10);
  if (((float)pSVar3 < (float)pSVar4) || (pSVar4 = pSVar3, (float)pSVar3 <= (float)pSVar2)) {
    pSVar2 = pSVar4;
  }
  switch(uVar7) {
  case 0:
  case 2:
    pSVar5->z = (float)pSVar2;
    if (pSVar6 != (Strip *)0x0) {
      pSVar6->z = (float)pSVar2;
      return;
    }
    break;
  case 1:
  case 3:
    pSVar5->x = (float)pSVar2;
    if (pSVar6 != (Strip *)0x0) {
      pSVar6->x = (float)pSVar2;
      return;
    }
  }
  return;
}
