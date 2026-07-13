/*
 * Entry: 00542b46
 * Name: Create_D3D_App_Ex
 * Namespace: Global
 * Signature: int Create_D3D_App_Ex(VIDEO_DEVICE * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Create_D3D_App_Ex(VIDEO_DEVICE *param_1,int param_2,int param_3)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = D3DAppCreateFromHWND((int)param_1,param_2,*(HWND__ **)(unaff_ESI + 0x88));
  if (iVar1 == 0) {
    return 0;
  }
  (**(code **)(unaff_ESI + 0x3c8))();
  (**(code **)(unaff_ESI + 0x3cc))();
  return (uint)(*(int *)(unaff_ESI + 0x2c) != 0);
}
