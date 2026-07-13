/*
 * Entry: 005278ae
 * Name: encrypt_buffer
 * Namespace: Global
 * Signature: void * encrypt_buffer(void * param_1, int param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl encrypt_buffer(void *param_1,int param_2,long param_3)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = param_2 >> 2; 0 < iVar1; iVar1 = iVar1 + -1) {
    *puVar2 = *puVar2 ^ param_3;
    puVar2 = puVar2 + 1;
  }
  return param_1;
}
