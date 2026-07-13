/*
 * Entry: 005433c3
 * Name: Repair_D3D_Buffer_Edge
 * Namespace: Global
 * Signature: void Repair_D3D_Buffer_Edge(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Repair_D3D_Buffer_Edge(VIDEO_DEVICE *param_1)

{
  int unaff_ESI;
  tagPOINT local_1c;
  undefined4 local_14;
  long local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  spriteZ = 0.0;
  ClampZ();
  SetZBufferRange(0);
  local_1c.x = *(long *)(unaff_ESI + 0x1c);
  local_14 = *(undefined4 *)(unaff_ESI + 0x24);
  local_1c.y = *(long *)(unaff_ESI + 0x28);
  local_8 = *(undefined4 *)(unaff_ESI + 0x20);
  local_10 = local_1c.y;
  local_c = local_14;
  D3D_PolyLine(&local_1c,3,(POLYGON_SKIN)0x0);
  return;
}
