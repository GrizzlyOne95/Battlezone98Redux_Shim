/*
 * Entry: 0054342a
 * Name: End_D3D_Scene
 * Namespace: Global
 * Signature: int End_D3D_Scene(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl End_D3D_Scene(void)

{
  int iVar1;
  tagPOINT local_1c;
  long local_14;
  long local_10;
  long local_c;
  long local_8;
  
  spriteZ = 0.0;
  ClampZ();
  SetZBufferRange(0);
  local_1c.x = Device.Viewport.Pane.x0;
  local_1c.y = Device.Viewport.Pane.y1;
  local_10 = Device.Viewport.Pane.y1;
  local_8 = Device.Viewport.Pane.y0;
  local_14 = Device.Viewport.Pane.x1;
  local_c = Device.Viewport.Pane.x1;
  D3D_PolyLine(&local_1c,3,(POLYGON_SKIN)0x0);
  RenderExB(d3dappi.lpD3DDevice);
  iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->EndScene)(d3dappi.lpD3DDevice);
  if (iVar1 != 0) {
    return 0;
  }
  if (D3D_Video_Memory_Is_Dirty == 1) {
    D3D_Flush_Texture_Cache();
  }
  return 1;
}
