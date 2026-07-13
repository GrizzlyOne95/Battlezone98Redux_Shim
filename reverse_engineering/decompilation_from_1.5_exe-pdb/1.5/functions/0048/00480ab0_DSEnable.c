/*
 * Entry: 00480ab0
 * Name: DSEnable
 * Namespace: Global
 * Signature: int DSEnable(HWND__ * param_1, IDirectSound * * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DSEnable(HWND__ *param_1,IDirectSound **param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int *unaff_ESI;
  
  if (*unaff_ESI != 0) {
    return 1;
  }
  iVar2 = _DirectSoundCreate_12(0,unaff_ESI,0);
  if (iVar2 == 0) {
    iVar2 = (**(code **)(*(int *)*unaff_ESI + 0x18))((int *)*unaff_ESI,param_1,3);
    if (iVar2 == 0) {
      return 1;
    }
    piVar1 = (int *)*unaff_ESI;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
      *unaff_ESI = 0;
    }
  }
  return 0;
}
