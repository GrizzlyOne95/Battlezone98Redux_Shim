/*
 * Entry: 005a5d40
 * Name: flag_lossless
 * Namespace: Global
 * Signature: void flag_lossless(int param_1, float param_2, float param_3, float * param_4, float * param_5, int * param_6, int param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
flag_lossless(int param_1,float param_2,float param_3,float *param_4,float *param_5,int *param_6,
             int param_7,int param_8)

{
  float *pfVar1;
  int *piVar2;
  int in_EAX;
  undefined4 *in_ECX;
  int iVar3;
  int iVar4;
  
  piVar2 = param_6;
  iVar3 = 0;
  if (0 < (int)param_6) {
    iVar4 = in_EAX - (int)in_ECX;
    do {
      if (iVar3 < param_1 - (int)param_5) {
        param_6 = (int *)param_2;
      }
      else {
        param_6 = (int *)param_3;
      }
      pfVar1 = (float *)(iVar4 + (int)in_ECX);
      if ((float)param_6 <= ABS(*(float *)((int)pfVar1 + ((int)param_4 - in_EAX))) / *pfVar1) {
        *in_ECX = 1;
      }
      else {
        *in_ECX = 0;
      }
      iVar3 = iVar3 + 1;
      in_ECX = in_ECX + 1;
    } while (iVar3 < (int)piVar2);
  }
  return;
}
