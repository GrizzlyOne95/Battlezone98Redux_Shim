/*
 * Entry: 004accc8
 * Name: giddi_read_channels
 * Namespace: Global
 * Signature: int giddi_read_channels(void * param_1, long * param_2, long * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_read_channels(void *param_1,long *param_2,long *param_3)

{
  bool bVar1;
  bool bVar2;
  
  if (param_3 != (long *)0x0) {
    bVar1 = controlMode == 0;
    bVar2 = editMode == 1;
    *param_3 = bVar1 | 2;
    if (bVar2) {
      *param_3 = bVar1 | 6;
    }
  }
  return 0;
}
