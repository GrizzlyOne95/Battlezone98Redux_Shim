/*
 * Entry: 005aa910
 * Name: drftf1
 * Namespace: Global
 * Signature: void drftf1(int param_1, float * param_2, float * param_3, float * param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl drftf1(int param_1,float *param_2,float *param_3,float *param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int in_ECX;
  float *pfVar5;
  float *unaff_EBX;
  float *unaff_EBP;
  float *unaff_ESI;
  float *unaff_EDI;
  int iVar6;
  int local_14;
  int *local_10;
  int local_4;
  
  local_4 = *(int *)(in_ECX + 4);
  local_14 = 1;
  if (0 < local_4) {
    local_10 = (int *)(in_ECX + 4 + local_4 * 4);
    iVar3 = param_1;
    iVar6 = param_1;
    do {
      iVar1 = *local_10;
      iVar2 = iVar3 / iVar1;
      iVar3 = param_1 / iVar3;
      local_14 = 1 - local_14;
      iVar6 = iVar6 - (iVar1 + -1) * iVar3;
      if (iVar1 == 4) {
        dradf4(iVar2,(int)(param_3 + iVar6 + -1),param_3 + iVar3 + iVar6 + -1,
               param_3 + iVar3 + iVar6 + iVar3 + -1,unaff_EBP,unaff_EDI,unaff_EBX);
      }
      else if (iVar1 == 2) {
        if (local_14 == 0) {
          dradf2(iVar2,(int)(param_3 + iVar6 + -1),unaff_EBP,unaff_EDI,unaff_EBX);
        }
        else {
          dradf2(iVar2,(int)(param_3 + iVar6 + -1),unaff_EBP,unaff_EDI,unaff_EBX);
        }
      }
      else {
        if (iVar3 == 1) {
          local_14 = 1 - local_14;
        }
        if (local_14 == 0) {
          dradfg(iVar1,iVar2,iVar3 * iVar2,(int)unaff_ESI,unaff_ESI,param_2,param_3 + iVar6 + -1,
                 unaff_EBP,unaff_EDI,unaff_EBX);
          local_14 = 1;
        }
        else {
          dradfg(iVar1,iVar2,iVar3 * iVar2,(int)param_2,param_2,unaff_ESI,param_3 + iVar6 + -1,
                 unaff_EBP,unaff_EDI,unaff_EBX);
          local_14 = 0;
        }
      }
      local_10 = local_10 + -1;
      local_4 = local_4 + -1;
      iVar3 = iVar2;
    } while (local_4 != 0);
    if (local_14 != 1) {
      iVar3 = 0;
      if (3 < param_1) {
        iVar6 = (param_1 - 4U >> 2) + 1;
        iVar3 = iVar6 * 4;
        pfVar4 = unaff_ESI + 1;
        pfVar5 = param_2 + 3;
        do {
          pfVar4[-1] = pfVar5[-3];
          iVar6 = iVar6 + -1;
          *pfVar4 = *(float *)((int)param_2 + (-0x10 - (int)unaff_ESI) + (int)(pfVar4 + 4));
          pfVar4[1] = pfVar5[-1];
          pfVar4[2] = *pfVar5;
          pfVar4 = pfVar4 + 4;
          pfVar5 = pfVar5 + 4;
        } while (iVar6 != 0);
      }
      if (iVar3 < param_1) {
        iVar6 = param_1 - iVar3;
        pfVar4 = unaff_ESI + iVar3;
        do {
          iVar6 = iVar6 + -1;
          *pfVar4 = *(float *)((int)pfVar4 + ((int)param_2 - (int)unaff_ESI));
          pfVar4 = pfVar4 + 1;
        } while (iVar6 != 0);
      }
    }
  }
  return;
}
