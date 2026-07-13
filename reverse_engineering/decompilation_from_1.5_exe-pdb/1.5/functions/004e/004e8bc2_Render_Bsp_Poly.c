/*
 * Entry: 004e8bc2
 * Name: Render_Bsp_Poly
 * Namespace: Global
 * Signature: void Render_Bsp_Poly(BSP_POLYGON * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Bsp_Poly(BSP_POLYGON *param_1)

{
  int in_EAX;
  POLYGON_SKIN PVar1;
  uint uVar2;
  
  if (((byte)LODInfo.flags & 2) != 0) {
    Draw_Pixel_Model(param_1);
    return;
  }
  if ((((byte)LODInfo.flags & 1) == 0) && (*(char **)(in_EAX + 8) != (char *)0x0)) {
    PVar1.Texture = Texture_Get(*(_OBJ76 **)(in_EAX + 4),*(char **)(in_EAX + 8));
    if ((TEXTURE *)PVar1.Color != (TEXTURE *)0x0) {
      uVar2 = *(byte *)(in_EAX + 3) | 0x11;
      goto LAB_004e8bf7;
    }
  }
  PVar1.Color._1_3_ = 0;
  PVar1.Color._0_1_ = *(byte *)(in_EAX + 2);
  uVar2 = *(byte *)(in_EAX + 3) & 0xffffffeb;
LAB_004e8bf7:
  if (useD3D == 0) {
    __Camera_Software_Draw_polygon__
              (Local_Camera,(POINT_3D *)(in_EAX + 0x30),(uint)*(byte *)(in_EAX + 1),PVar1,uVar2);
  }
  else {
    __Camera_Hardware_Draw_polygon__
              (Local_Camera,(POINT_3D *)(in_EAX + 0x30),(uint)*(byte *)(in_EAX + 1),PVar1,uVar2);
  }
  return;
}
