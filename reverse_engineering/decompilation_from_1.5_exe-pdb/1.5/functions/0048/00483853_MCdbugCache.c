/*
 * Entry: 00483853
 * Name: MCdbugCache
 * Namespace: Global
 * Signature: void MCdbugCache(MULTICACHE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl MCdbugCache(MULTICACHE *param_1)

{
  int iVar1;
  FILE *_File;
  size_t sVar2;
  void *_Memory;
  cachenode *_Memory_00;
  MULTICACHE *local_78;
  int local_74;
  char local_6c [100];
  uint local_8;
  
  iVar1 = cnt;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_78 = param_1;
  if (param_1 == (MULTICACHE *)0x0) {
    local_78 = &GlobalCache;
  }
  cnt = cnt + 1;
  sprintf(local_6c,"dbugcch%d.log",iVar1);
  _File = fopen(local_6c,"w");
  fprintf(_File,"Cache table\n-----------------------\n");
  local_74 = 0;
  do {
    for (_Memory = *(void **)(local_74 + (int)local_78->Cache); _Memory != (void *)0x0;
        _Memory = *(void **)((int)_Memory + 0x1c)) {
      sVar2 = _msize(_Memory);
      fprintf(_File,"name=%16s  Lock=%d  Size=%7d\n",_Memory,(int)*(short *)((int)_Memory + 0x14),
              sVar2);
    }
    local_74 = local_74 + 4;
  } while (local_74 < 0x2000);
  fprintf(_File,"\nPurge list\n-----------------------\n");
  for (_Memory_00 = local_78->PurgeHead; _Memory_00 != (cachenode *)0x0;
      _Memory_00 = _Memory_00->PurgeNext) {
    sVar2 = _msize(_Memory_00);
    fprintf(_File,"name=%16s  Lock=%d  Size=%7d\n",_Memory_00,(int)_Memory_00->Lock,sVar2);
  }
  fclose(_File);
  return;
}
