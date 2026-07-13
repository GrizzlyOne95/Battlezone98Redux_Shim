/*
 * Entry: 004e7747
 * Name: AnimateMeshTransform
 * Namespace: Global
 * Signature: void AnimateMeshTransform(_OBJ76 * param_1, tagANIMOBJ_MESH * param_2, tagANIMOBJ_ACTIVE_LIST * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AnimateMeshTransform
          (_OBJ76 *param_1,tagANIMOBJ_MESH *param_2,tagANIMOBJ_ACTIVE_LIST *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int in_EAX;
  int *piVar4;
  int iVar5;
  float *unaff_EBX;
  float *unaff_ESI;
  int iVar6;
  float *pfVar7;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar8;
  float local_58 [4];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  double local_30;
  double local_28;
  double local_20;
  float local_18;
  float local_14;
  float local_10;
  int iStack_c;
  int local_8;
  
  iVar5 = *(int *)(in_EAX + 0x70);
  if (iVar5 < 1) {
    local_58[0] = *(float *)(in_EAX + 0x3c);
    local_58[1] = (float)*(undefined4 *)(in_EAX + 0x40);
    local_58[2] = (float)*(undefined4 *)(in_EAX + 0x44);
    local_58[3] = (float)*(undefined4 *)(in_EAX + 0x48);
    local_48 = *(undefined4 *)(in_EAX + 0x4c);
    local_44 = *(undefined4 *)(in_EAX + 0x50);
    local_40 = *(undefined4 *)(in_EAX + 0x54);
    local_3c = *(undefined4 *)(in_EAX + 0x58);
    local_38 = *(undefined4 *)(in_EAX + 0x5c);
  }
  else {
    piVar4 = (int *)(*(int *)(in_EAX + 0x6c) * 0x14 +
                    *(int *)(*(int *)(param_2->meshName + 4) + 0x2c));
    iVar6 = 1;
    piVar3 = piVar4;
    if (1 < iVar5) {
      do {
        if (((float)*piVar3 < (float)param_3 != ((float)*piVar3 == (float)param_3)) &&
           ((float)param_3 <= (float)piVar3[5])) {
          if (-1 < iVar6 + -1) {
            iVar5 = piVar4[(iVar6 + -1) * 5];
            local_8 = (piVar4 + (iVar6 + -1) * 5)[5] - iVar5;
            SLERP((float *)(((float)param_3 - (float)iVar5) / (float)local_8),(float)unaff_EDI,
                  unaff_ESI,unaff_EBX);
            goto LAB_004e77a1;
          }
          break;
        }
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 5;
      } while (iVar6 < iVar5);
    }
    local_18 = (float)piVar4[1];
    local_14 = (float)piVar4[2];
    local_10 = (float)piVar4[3];
    iStack_c = piVar4[4];
LAB_004e77a1:
    ApplyRotation(unaff_EDI,unaff_ESI);
  }
  iVar5 = *(int *)(in_EAX + 0x80);
  if (iVar5 == 0) {
    local_30 = (double)*(float *)(in_EAX + 0x60);
    local_28 = (double)*(float *)(in_EAX + 100);
    local_10 = *(float *)(in_EAX + 0x68);
  }
  else {
    piVar4 = (int *)(*(int *)(in_EAX + 0x7c) * 0x10 +
                    *(int *)(*(int *)(param_2->meshName + 4) + 0x34));
    iVar6 = 1;
    piVar3 = piVar4;
    if (1 < iVar5) {
      do {
        if (((float)*piVar3 < (float)param_3 != ((float)*piVar3 == (float)param_3)) &&
           ((float)param_3 <= (float)piVar3[4])) {
          if (-1 < iVar6 + -1) {
            piVar4 = piVar4 + (iVar6 + -1) * 4;
            local_8 = piVar4[4] - *piVar4;
            fVar1 = ((float)param_3 - (float)*piVar4) / (float)local_8;
            fVar2 = 1.0 - fVar1;
            local_18 = fVar2 * (float)piVar4[1] + (float)piVar4[5] * fVar1;
            local_14 = (float)piVar4[6] * fVar1 + (float)piVar4[2] * fVar2;
            local_10 = fVar2 * (float)piVar4[3] + (float)piVar4[7] * fVar1;
            goto LAB_004e786c;
          }
          break;
        }
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 4;
      } while (iVar6 < iVar5);
    }
    local_18 = (float)piVar4[1];
    local_14 = (float)piVar4[2];
    local_10 = (float)piVar4[3];
LAB_004e786c:
    local_30 = (double)local_18;
    local_28 = (double)local_14;
  }
  local_20 = (double)local_10;
  pfVar7 = local_58;
  pMVar8 = &param_1->transform;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pMVar8->right_x = *pfVar7;
    pfVar7 = pfVar7 + 1;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
  }
  return;
}
