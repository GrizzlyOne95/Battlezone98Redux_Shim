/*
 * Entry: 00514a66
 * Name: NR_Svector
 * Namespace: Global
 * Signature: ushort * NR_Svector(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl NR_Svector(int param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,(param_2 - param_1) * 2 + 2);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Svector()");
  }
  return (ushort *)((int)pvVar1 + param_1 * -2);
}
