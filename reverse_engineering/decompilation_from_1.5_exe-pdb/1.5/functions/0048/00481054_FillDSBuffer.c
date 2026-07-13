/*
 * Entry: 00481054
 * Name: FillDSBuffer
 * Namespace: Global
 * Signature: int FillDSBuffer(IDirectSoundBuffer * param_1, uchar * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FillDSBuffer(IDirectSoundBuffer *param_1,uchar *param_2,ulong param_3)

{
  int iVar1;
  int *unaff_ESI;
  int unaff_EDI;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (((unaff_ESI != (int *)0x0) && (unaff_EDI != 0)) && (param_1 != (IDirectSoundBuffer *)0x0)) {
    iVar1 = (**(code **)(*unaff_ESI + 0x2c))();
    if (-1 < iVar1) {
      memcpy(local_14);
      if (local_8 != 0) {
        memcpy(local_10,local_c + unaff_EDI,local_8);
      }
      (**(code **)(*unaff_ESI + 0x4c))();
      return 1;
    }
  }
  return 0;
}
