/*
 * Entry: 0050e692
 * Name: Debug_Done
 * Namespace: Global
 * Signature: void Debug_Done(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Debug_Done(void)

{
  tagATEXITNODE *ptVar1;
  tagATEXITNODE *_Memory;
  
  _Memory = atexitlist;
  while (_Memory != (tagATEXITNODE *)0x0) {
    ptVar1 = _Memory->next;
    (*_Memory->func)();
    free(_Memory);
    _Memory = ptVar1;
  }
  atexitlist = (tagATEXITNODE *)0x0;
  if (allocations != 0) {
    LogError(-1,"Debug warning: %d outstanding allocations on call to Debug_Done\n");
  }
  return;
}
