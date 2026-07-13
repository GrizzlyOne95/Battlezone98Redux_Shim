/*
 * Entry: 005a0c40
 * Name: _vorbis_block_ripcord
 * Namespace: Global
 * Signature: void _vorbis_block_ripcord(vorbis_block * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _vorbis_block_ripcord(vorbis_block *param_1)

{
  alloc_chain *paVar1;
  alloc_chain *_Memory;
  void *pvVar2;
  
  _Memory = param_1->reap;
  while (_Memory != (alloc_chain *)0x0) {
    paVar1 = _Memory->next;
    free(_Memory->ptr);
    _Memory->ptr = (void *)0x0;
    _Memory->next = (alloc_chain *)0x0;
    free(_Memory);
    _Memory = paVar1;
  }
  if (param_1->totaluse != 0) {
    pvVar2 = realloc(param_1->localstore,param_1->localalloc + param_1->totaluse);
    param_1->localstore = pvVar2;
    param_1->localalloc = param_1->localalloc + param_1->totaluse;
    param_1->totaluse = 0;
  }
  param_1->reap = (alloc_chain *)0x0;
  param_1->localtop = 0;
  return;
}
