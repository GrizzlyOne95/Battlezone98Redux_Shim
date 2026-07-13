/*
 * Entry: 0040af97
 * Name: InitGrid
 * Namespace: Global
 * Signature: void InitGrid(int * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitGrid(int **param_1)

{
  longlong lVar1;
  void *pvVar2;
  int *unaff_ESI;
  
  if (*unaff_ESI == 0) {
    lVar1 = ((longlong)gridColumns * (longlong)gridRows & 0xffffffffU) * 4;
    pvVar2 = operator_new__(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
    *unaff_ESI = (int)pvVar2;
  }
  memset(*unaff_ESI,0,gridColumns * gridRows * 4);
  return;
}
