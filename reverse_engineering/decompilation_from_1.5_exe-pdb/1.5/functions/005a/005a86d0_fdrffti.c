/*
 * Entry: 005a86d0
 * Name: fdrffti
 * Namespace: Global
 * Signature: void fdrffti(int param_1, float * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fdrffti(int param_1,float *param_2,int *param_3)

{
  int in_EAX;
  int *in_ECX;
  int in_EDX;
  
  if (in_EAX != 1) {
    drfti1(in_EAX,(float *)(in_EDX + in_EAX * 4),in_ECX);
  }
  return;
}
