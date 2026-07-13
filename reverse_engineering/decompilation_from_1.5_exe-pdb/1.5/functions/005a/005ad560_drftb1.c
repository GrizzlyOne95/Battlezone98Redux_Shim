/*
 * Entry: 005ad560
 * Name: drftb1
 * Namespace: Global
 * Signature: void drftb1(int param_1, float * param_2, float * param_3, float * param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl drftb1(int param_1,float *param_2,float *param_3,float *param_4,int *param_5)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  int in_EDX;
  int iVar4;
  float *unaff_EBX;
  int iVar5;
  float *unaff_ESI;
  float *unaff_EDI;
  int local_18;
  int local_14;
  int *local_10;
  int local_8;
  
  local_8 = *(int *)(in_EDX + 4);
  local_18 = 0;
  local_14 = 1;
  if (0 < local_8) {
    local_10 = (int *)(in_EDX + 8);
    iVar5 = 1;
    do {
      iVar4 = *local_10;
      iVar1 = param_1 / (iVar4 * iVar5);
      if (iVar4 == 4) {
        dradb4(iVar5,(int)(param_4 + local_14 + -1),param_4 + iVar1 + local_14 + -1,
               param_4 + iVar1 + local_14 + iVar1 + -1,unaff_EDI,unaff_EBX,unaff_ESI);
        local_18 = 1 - local_18;
      }
      else if (iVar4 == 2) {
        dradb2(iVar5,(int)(param_4 + local_14 + -1),unaff_EDI,unaff_EBX,unaff_ESI);
        local_18 = 1 - local_18;
      }
      else if (iVar4 == 3) {
        pfVar2 = param_3;
        if (local_18 != 0) {
          pfVar2 = param_2;
        }
        dradb3(iVar5,(int)pfVar2,param_4 + local_14 + -1,param_4 + iVar1 + local_14 + -1,unaff_EDI,
               unaff_EBX);
        local_18 = 1 - local_18;
      }
      else {
        pfVar2 = param_2;
        pfVar3 = param_3;
        if (local_18 != 0) {
          pfVar2 = param_3;
          pfVar3 = param_2;
        }
        dradbg(iVar1,iVar4,iVar5,iVar1 * iVar5,pfVar2,pfVar3,param_4 + local_14 + -1,unaff_EDI,
               unaff_EBX,unaff_ESI);
        if (iVar1 == 1) {
          local_18 = 1 - local_18;
        }
      }
      local_10 = local_10 + 1;
      local_14 = local_14 + (iVar4 + -1) * iVar1;
      local_8 = local_8 + -1;
      iVar5 = iVar4 * iVar5;
    } while (local_8 != 0);
    if (local_18 != 0) {
      iVar5 = 0;
      if (3 < param_1) {
        iVar4 = (param_1 - 4U >> 2) + 1;
        iVar5 = iVar4 * 4;
        pfVar2 = param_2 + 1;
        pfVar3 = param_3 + 3;
        do {
          pfVar2[-1] = pfVar3[-3];
          iVar4 = iVar4 + -1;
          *pfVar2 = *(float *)((int)param_3 + (-0x10 - (int)param_2) + (int)(pfVar2 + 4));
          pfVar2[1] = pfVar3[-1];
          pfVar2[2] = *pfVar3;
          pfVar2 = pfVar2 + 4;
          pfVar3 = pfVar3 + 4;
        } while (iVar4 != 0);
      }
      if (iVar5 < param_1) {
        iVar4 = param_1 - iVar5;
        pfVar2 = param_2 + iVar5;
        do {
          iVar4 = iVar4 + -1;
          *pfVar2 = *(float *)((int)pfVar2 + ((int)param_3 - (int)param_2));
          pfVar2 = pfVar2 + 1;
        } while (iVar4 != 0);
      }
    }
  }
  return;
}
