/*
 * Entry: 00514b14
 * Name: NR_Ptr_Vector
 * Namespace: Global
 * Signature: void * * NR_Ptr_Vector(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void ** __cdecl NR_Ptr_Vector(int param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,(param_2 - param_1) * 4 + 4);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_ptr_vector()");
  }
  return (void **)((int)pvVar1 + param_1 * -4);
}
