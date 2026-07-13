/*
 * Entry: 00481f71
 * Name: SetGASAudioProperties
 * Namespace: Global
 * Signature: void SetGASAudioProperties(_gas_object * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetGASAudioProperties(_gas_object *param_1,int param_2)

{
  int *piVar1;
  undefined4 extraout_EAX;
  int extraout_EAX_00;
  int iVar2;
  undefined4 extraout_EAX_01;
  int unaff_ESI;
  _gas_object *unaff_EDI;
  
  if (unaff_ESI != 0) {
    if (((*(byte *)(unaff_ESI + 0x14) & 0x20) != 0) && ((*(byte *)(unaff_ESI + 0x60) & 0x20) != 0))
    {
      piVar1 = *(int **)(unaff_ESI + 0x54);
      iVar2 = *piVar1;
      _ftol2();
      (**(code **)(iVar2 + 0x44))(piVar1,extraout_EAX);
    }
    if ((*(uint *)(unaff_ESI + 0x14) & 0x40) != 0) {
      _ftol2_sse();
      iVar2 = extraout_EAX_00;
      if (extraout_EAX_00 < 0) {
        iVar2 = 0;
      }
      if (100 < iVar2) {
        iVar2 = 100;
      }
      (**(code **)(**(int **)(unaff_ESI + 0x54) + 0x3c))
                (*(int **)(unaff_ESI + 0x54),VolumeLevels[iVar2]);
    }
    if (((*(byte *)(unaff_ESI + 0x14) & 0x80) != 0) &&
       (GM->listener == (IDirectSound3DListener *)0x0)) {
      piVar1 = *(int **)(unaff_ESI + 0x54);
      iVar2 = *piVar1;
      _ftol2_sse();
      (**(code **)(iVar2 + 0x40))(piVar1,extraout_EAX_01);
    }
    if ((*(int *)(unaff_ESI + 0x5c) != 0) && (GM->listener != (IDirectSound3DListener *)0x0)) {
      SetGAS3DProperties(unaff_EDI);
      if ((*(uint *)(unaff_ESI + 0x14) & 0x200) != 0) {
        *(uint *)(unaff_ESI + 0x78) = *(uint *)(unaff_ESI + 0x78) | 0x10;
        *(undefined4 *)(unaff_ESI + 0x5c) = 0;
        *(undefined4 *)(unaff_ESI + 0x80) = 0;
      }
      if (param_1 != (_gas_object *)0x0) {
        (**(code **)((int)*GM->listener + 0x44))(GM->listener);
      }
    }
    *(uint *)(unaff_ESI + 0x14) = *(uint *)(unaff_ESI + 0x14) & 0xfffffe1f;
  }
  return;
}
