/*
 * Entry: 005a8520
 * Name: drfti1
 * Namespace: Global
 * Signature: void drfti1(int param_1, float * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl drfti1(int param_1,float *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  int local_20;
  int local_1c;
  int *local_18;
  int local_10;
  int local_c;
  
  iVar5 = 0;
  iVar3 = -1;
  iVar7 = 0;
  iVar8 = param_1;
  do {
    do {
      iVar3 = iVar3 + 1;
      if (iVar3 < 4) {
        iVar5 = ntryh[iVar3];
      }
      else {
        iVar5 = iVar5 + 2;
      }
    } while (iVar8 != (iVar8 / iVar5) * iVar5);
    iVar2 = iVar8 / iVar5;
    piVar4 = param_3 + iVar7;
    local_c = iVar7;
    do {
      iVar8 = iVar2;
      iVar7 = local_c + 1;
      piVar4[2] = iVar5;
      if ((iVar5 == 2) && (iVar7 != 1)) {
        piVar1 = piVar4 + 1;
        iVar2 = local_c;
        if (1 < iVar7) {
          do {
            piVar1[1] = *piVar1;
            iVar2 = iVar2 + -1;
            piVar1 = piVar1 + -1;
          } while (iVar2 != 0);
        }
        param_3[2] = 2;
      }
      if (iVar8 == 1) {
        param_3[1] = iVar7;
        *param_3 = param_1;
        local_20 = 0;
        local_1c = 1;
        if ((local_c != 0) && (0 < local_c)) {
          local_18 = param_3 + 2;
          do {
            local_1c = *local_18 * local_1c;
            iVar5 = param_1 / local_1c;
            local_10 = *local_18 + -1;
            if (0 < local_10) {
              do {
                if (2 < iVar5) {
                  pfVar6 = param_2 + local_20;
                  iVar8 = (iVar5 - 3U >> 1) + 1;
                  do {
                    fVar9 = (float10)__CIcos();
                    *pfVar6 = (float)fVar9;
                    fVar9 = (float10)__CIsin();
                    pfVar6[1] = (float)fVar9;
                    pfVar6 = pfVar6 + 2;
                    iVar8 = iVar8 + -1;
                  } while (iVar8 != 0);
                }
                local_20 = local_20 + iVar5;
                local_10 = local_10 + -1;
              } while (local_10 != 0);
            }
            local_18 = local_18 + 1;
            local_c = local_c + -1;
          } while (local_c != 0);
        }
        return;
      }
      iVar2 = iVar8 / iVar5;
      piVar4 = piVar4 + 1;
      local_c = iVar7;
    } while (iVar8 == (iVar8 / iVar5) * iVar5);
  } while( true );
}
