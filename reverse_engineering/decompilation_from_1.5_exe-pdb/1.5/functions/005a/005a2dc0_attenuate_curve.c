/*
 * Entry: 005a2dc0
 * Name: attenuate_curve
 * Namespace: Global
 * Signature: void attenuate_curve(float * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl attenuate_curve(float *param_1,float param_2)

{
  int in_EAX;
  float *pfVar1;
  int iVar2;
  
  iVar2 = 7;
  pfVar1 = (float *)(in_EAX + 8);
  do {
    iVar2 = iVar2 + -1;
    pfVar1[-2] = pfVar1[-2] + (float)param_1;
    pfVar1[-1] = (float)param_1 + pfVar1[-1];
    *pfVar1 = *pfVar1 + (float)param_1;
    pfVar1[1] = pfVar1[1] + (float)param_1;
    pfVar1[2] = pfVar1[2] + (float)param_1;
    pfVar1[3] = pfVar1[3] + (float)param_1;
    pfVar1[4] = (float)param_1 + pfVar1[4];
    pfVar1[5] = pfVar1[5] + (float)param_1;
    pfVar1 = pfVar1 + 8;
  } while (iVar2 != 0);
  return;
}
