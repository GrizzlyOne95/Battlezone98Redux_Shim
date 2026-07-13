/*
 * Entry: 005a0cb0
 * Name: vorbis_block_clear
 * Namespace: Global
 * Signature: int vorbis_block_clear(vorbis_block * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_block_clear(vorbis_block *param_1)

{
  void *_Memory;
  int iVar1;
  undefined4 *puVar2;
  
  _Memory = param_1->internal;
  _vorbis_block_ripcord(param_1);
  if (param_1->localstore != (void *)0x0) {
    free(param_1->localstore);
  }
  if (_Memory != (void *)0x0) {
    iVar1 = 0;
    puVar2 = (undefined4 *)((int)_Memory + 0xc);
    do {
      oggpack_writeclear(*puVar2);
      if (iVar1 != 7) {
        free((void *)*puVar2);
      }
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar1 < 0xf);
    free(_Memory);
  }
  memset(param_1,0,0x70);
  return 0;
}
