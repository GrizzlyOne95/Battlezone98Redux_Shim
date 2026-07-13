/*
 * Entry: 0047b221
 * Name: Set_Satellite_View
 * Namespace: Global
 * Signature: void Set_Satellite_View(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Satellite_View(void)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *pMVar3;
  MAT_3D local_88;
  MAT_3D local_48;
  float local_8;
  
  pMVar1 = OverView_GetCameraMatrix(&local_88);
  pMVar3 = &local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  local_8 = OverView_GetZoom();
  Camera_Set_Matrix(&View_Record.MainCam,&local_48);
  if (local_8 != View_Record.MainCam.Zoom_Factor) {
    Camera_Set_Zoom(&View_Record.MainCam,local_8);
  }
  return;
}
