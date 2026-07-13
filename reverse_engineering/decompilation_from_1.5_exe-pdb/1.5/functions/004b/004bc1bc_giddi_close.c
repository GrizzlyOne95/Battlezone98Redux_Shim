/*
 * Entry: 004bc1bc
 * Name: giddi_close
 * Namespace: Global
 * Signature: int giddi_close(_GIDDI_DEVDESC * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_close(_GIDDI_DEVDESC *param_1)

{
  char **ppcVar1;
  
  if (param_1 == (_GIDDI_DEVDESC *)0x0) {
    return 0;
  }
  if ((param_1->analog_desc != (char **)0x0) && (hDefaultHeap != (void *)0x0)) {
    free(param_1->analog_desc);
  }
  if ((param_1->analog_names != (char **)0x0) && (hDefaultHeap != (void *)0x0)) {
    free(param_1->analog_names);
  }
  ppcVar1 = param_1->discrete_desc;
  if (ppcVar1 != (char **)0x0) {
    if (*ppcVar1 != (char *)0x0) {
      if (hDefaultHeap == (void *)0x0) goto LAB_004bc21f;
      free(*ppcVar1);
    }
    if (hDefaultHeap != (void *)0x0) {
      free(param_1->discrete_desc);
    }
  }
LAB_004bc21f:
  ppcVar1 = param_1->discrete_names;
  if (ppcVar1 != (char **)0x0) {
    if (*ppcVar1 != (char *)0x0) {
      if (hDefaultHeap == (void *)0x0) goto LAB_004bc245;
      free(*ppcVar1);
    }
    if (hDefaultHeap != (void *)0x0) {
      free(param_1->discrete_names);
    }
  }
LAB_004bc245:
  if ((param_1->data != (void *)0x0) && (hDefaultHeap != (void *)0x0)) {
    free(param_1->data);
  }
  return 0;
}
