/*
 * Entry: 005c9930
 * Name: FUN_005c9930
 * Namespace: Global
 * Signature: undefined FUN_005c9930()
 * Symbol source: DEFAULT
 * Export status: ok
 */

void FUN_005c9930(int param_1,code *param_2,int param_3)

{
  int iVar1;
  size_t _NewSize;
  void *pvVar2;
  void *unaff_EBX;
  int *unaff_ESI;
  size_t _Size;
  
  _Size = (int)(param_1 + (param_1 >> 0x1f & 7U)) >> 3;
  iVar1 = ((int)(unaff_ESI[1] + param_1 + (unaff_ESI[1] + param_1 >> 0x1f & 7U)) >> 3) + *unaff_ESI;
  if (iVar1 < unaff_ESI[4]) {
LAB_005c99bb:
    if (unaff_ESI[1] == 0) {
      memmove((void *)unaff_ESI[3],unaff_EBX,_Size);
      unaff_ESI[3] = unaff_ESI[3] + _Size;
      *unaff_ESI = *unaff_ESI + _Size;
      *(undefined1 *)unaff_ESI[3] = 0;
    }
    else {
      iVar1 = 0;
      if (0 < (int)_Size) {
        do {
          (*param_2)();
          iVar1 = iVar1 + 1;
        } while (iVar1 < (int)_Size);
      }
    }
    if (param_1 + _Size * -8 != 0) {
      if (param_3 != 0) {
        (*param_2)();
        return;
      }
      (*param_2)();
    }
    return;
  }
  if ((unaff_ESI[3] != 0) && (_NewSize = iVar1 + 0x100, unaff_ESI[4] <= (int)_NewSize)) {
    unaff_ESI[4] = _NewSize;
    pvVar2 = realloc((void *)unaff_ESI[2],_NewSize);
    if (pvVar2 != (void *)0x0) {
      unaff_ESI[2] = (int)pvVar2;
      unaff_ESI[3] = *unaff_ESI + (int)pvVar2;
      goto LAB_005c99bb;
    }
  }
  if ((void *)unaff_ESI[2] != (void *)0x0) {
    free((void *)unaff_ESI[2]);
  }
  *unaff_ESI = 0;
  unaff_ESI[1] = 0;
  unaff_ESI[2] = 0;
  unaff_ESI[3] = 0;
  unaff_ESI[4] = 0;
  return;
}
