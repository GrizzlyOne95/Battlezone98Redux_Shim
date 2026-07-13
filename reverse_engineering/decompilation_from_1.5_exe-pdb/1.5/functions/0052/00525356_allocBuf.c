/*
 * Entry: 00525356
 * Name: allocBuf
 * Namespace: Global
 * Signature: void * allocBuf(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl allocBuf(int param_1)

{
  void *pvVar1;
  
  pvVar1 = malloc(param_1);
  if (pvVar1 == (void *)0x0) {
                    /* WARNING: Subroutine does not return */
    I76FatalError((char *)0x0);
  }
  return pvVar1;
}
