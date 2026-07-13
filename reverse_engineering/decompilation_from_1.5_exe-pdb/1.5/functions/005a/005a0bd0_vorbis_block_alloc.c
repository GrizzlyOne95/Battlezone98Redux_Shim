/*
 * Entry: 005a0bd0
 * Name: _vorbis_block_alloc
 * Namespace: Global
 * Signature: void * _vorbis_block_alloc(vorbis_block * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl _vorbis_block_alloc(vorbis_block *param_1,long param_2)

{
  int iVar1;
  alloc_chain *paVar2;
  void *pvVar3;
  uint _Size;
  
  _Size = param_2 + 7U & 0xfffffff8;
  if (param_1->localalloc < (int)(param_1->localtop + _Size)) {
    if (param_1->localstore != (void *)0x0) {
      paVar2 = malloc(8);
      param_1->totaluse = param_1->totaluse + param_1->localtop;
      paVar2->next = param_1->reap;
      paVar2->ptr = param_1->localstore;
      param_1->reap = paVar2;
    }
    param_1->localalloc = _Size;
    pvVar3 = malloc(_Size);
    param_1->localstore = pvVar3;
    param_1->localtop = 0;
  }
  iVar1 = param_1->localtop;
  param_1->localtop = iVar1 + _Size;
  return (void *)((int)param_1->localstore + iVar1);
}
