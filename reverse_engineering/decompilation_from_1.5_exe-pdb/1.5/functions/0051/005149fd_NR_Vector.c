/*
 * Entry: 005149fd
 * Name: NR_Vector
 * Namespace: Global
 * Signature: float * NR_Vector(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float * __cdecl NR_Vector(int param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,(param_2 - param_1) * 4 + 4);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Vector()");
  }
  return (float *)((int)pvVar1 + param_1 * -4);
}
