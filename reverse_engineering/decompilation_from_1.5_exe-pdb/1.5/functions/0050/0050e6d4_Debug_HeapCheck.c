/*
 * Entry: 0050e6d4
 * Name: Debug_HeapCheck
 * Namespace: Global
 * Signature: int Debug_HeapCheck(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Debug_HeapCheck(void)

{
  int iVar1;
  char *pcVar2;
  _HEAPINFO local_10;
  
  iVar1 = _heapset(0xff);
  if (iVar1 == -4) {
    LogError(-1,"Debug error: Heap has a bad node or has been damaged! (HEAPBADNODE)\n");
LAB_0050e715:
    if (iVar1 != -4) {
      return iVar1;
    }
  }
  else {
    if (iVar1 != -3) goto LAB_0050e715;
    LogError(-1,"Debug error: Heap has been damaged! (HEAPBADBEGIN)\n");
  }
  local_10._pentry = (int *)0x0;
  do {
    iVar1 = _heapwalk(&local_10);
  } while (iVar1 == -2);
  if (iVar1 == -6) {
    pcVar2 = "  Heap walk error %s block at %Fp of size %4.4x : bad pointer to heap\n";
  }
  else {
    if (iVar1 == -5) {
      pcVar2 = "  Heap walk was successful!?\n";
LAB_0050e79b:
      LogError(-1,pcVar2);
      return iVar1;
    }
    if (iVar1 == -4) {
      pcVar2 = "  Heap walk error %s block at %Fp of size %4.4x : bad node in heap\n";
    }
    else {
      if (iVar1 != -3) {
        if (iVar1 == -1) {
          pcVar2 = "  Heap walk was successful : empty heap!?\n";
        }
        else {
          pcVar2 = "Unknown heap walk error\n";
        }
        goto LAB_0050e79b;
      }
      pcVar2 = "  Heap walk error %s block at %Fp of size %4.4x : damaged heap\n";
    }
  }
  LogError(-1,pcVar2);
  return iVar1;
}
