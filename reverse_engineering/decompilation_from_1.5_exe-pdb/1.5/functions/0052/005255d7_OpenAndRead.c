/*
 * Entry: 005255d7
 * Name: OpenAndRead
 * Namespace: Global
 * Signature: int OpenAndRead(char * param_1, long * param_2, char * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OpenAndRead(char *param_1,long *param_2,char **param_3)

{
  int _FileHandle;
  size_t _Size;
  char *_DstBuf;
  int iVar1;
  
  _FileHandle = _open(param_1,0x8000);
  if (_FileHandle != -1) {
    _Size = _filelength(_FileHandle);
    *param_2 = _Size;
    _DstBuf = malloc(_Size);
    *param_3 = _DstBuf;
    if (_DstBuf != (char *)0x0) {
      iVar1 = _read(_FileHandle,_DstBuf,*param_2);
      if (iVar1 == *param_2) {
        return _FileHandle;
      }
      if (hDefaultHeap != (void *)0x0) {
        free(*param_3);
      }
    }
    _close(_FileHandle);
  }
  return -1;
}
