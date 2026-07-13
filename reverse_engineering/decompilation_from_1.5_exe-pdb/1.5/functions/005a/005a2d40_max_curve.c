/*
 * Entry: 005a2d40
 * Name: max_curve
 * Namespace: Global
 * Signature: void max_curve(float * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl max_curve(float *param_1,float *param_2)

{
  int in_EAX;
  int in_ECX;
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  
  pfVar1 = (float *)(in_ECX + 4);
  pfVar2 = (float *)(in_EAX + 0xc);
  iVar3 = 0xe;
  do {
    if (pfVar1[-1] < pfVar2[-3]) {
      pfVar1[-1] = pfVar2[-3];
    }
    if (*pfVar1 < *(float *)((in_EAX - in_ECX) + (int)pfVar1)) {
      *pfVar1 = *(float *)((in_EAX - in_ECX) + (int)pfVar1);
    }
    if (pfVar1[1] < pfVar2[-1]) {
      pfVar1[1] = pfVar2[-1];
    }
    if (pfVar1[2] < *pfVar2) {
      pfVar1[2] = *pfVar2;
    }
    pfVar1 = pfVar1 + 4;
    pfVar2 = pfVar2 + 4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}
