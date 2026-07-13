/*
 * Entry: 004e8c2f
 * Name: Render_Bsp_Mesh
 * Namespace: Global
 * Signature: void Render_Bsp_Mesh(BSP_POLYGON * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Bsp_Mesh(BSP_POLYGON *param_1)

{
  char *in_EAX;
  POLYGON_SKIN PVar1;
  BSP_POLYGON *unaff_EDI;
  int iVar2;
  undefined4 auStack_804 [512];
  
  if (in_EAX != (char *)0x0) {
    if ((D3IniFlags & 1U) == 0) {
      iVar2 = 0;
LAB_004e8cf0:
      auStack_804[iVar2] = in_EAX;
      iVar2 = iVar2 + 1;
      if (*(float *)(in_EAX + 0x24) < 0.0) goto LAB_004e8d45;
      do {
        in_EAX = *(char **)(in_EAX + 0x2c);
        while( true ) {
          if (in_EAX != (char *)0x0) goto LAB_004e8cf0;
          if (iVar2 == 0) {
            return;
          }
          in_EAX = (char *)auStack_804[iVar2 + -1];
          iVar2 = iVar2 + -1;
          if (in_EAX[1] == '\0') {
            if (*in_EAX == '\x02') {
              Render_Sprite_Entity(*(_ZSORTING **)(in_EAX + 4),Local_Camera);
            }
          }
          else {
            Render_Bsp_Poly(unaff_EDI);
          }
          if (*(float *)(in_EAX + 0x24) < 0.0) break;
LAB_004e8d45:
          in_EAX = *(char **)(in_EAX + 0x28);
        }
      } while( true );
    }
    do {
      if ((*(char **)(in_EAX + 8) == (char *)0x0) ||
         (PVar1.Texture = Texture_Get(*(_OBJ76 **)(in_EAX + 4),*(char **)(in_EAX + 8)),
         PVar1.Color == 0)) {
        PVar1.Color._1_3_ = 0;
        PVar1.Color._0_1_ = in_EAX[2];
        if (useD3D == 0) {
          __Camera_Software_Draw_polygon__
                    (Local_Camera,(POINT_3D *)(in_EAX + 0x30),(uint)(byte)in_EAX[1],PVar1,
                     (byte)in_EAX[3] & 0xffffffeb);
        }
        else {
          __Camera_Hardware_Draw_polygon__
                    (Local_Camera,(POINT_3D *)(in_EAX + 0x30),(uint)(byte)in_EAX[1],PVar1,
                     (byte)in_EAX[3] & 0xffffffeb);
        }
      }
      else {
        D3IniFlags = D3IniFlags | 0x80;
        if (useD3D == 0) {
          __Camera_Software_Draw_polygon__
                    (Local_Camera,(POINT_3D *)(in_EAX + 0x30),(uint)(byte)in_EAX[1],PVar1,
                     (byte)in_EAX[3] | 0x11);
        }
        else {
          __Camera_Hardware_Draw_polygon__
                    (Local_Camera,(POINT_3D *)(in_EAX + 0x30),(uint)(byte)in_EAX[1],PVar1,
                     (byte)in_EAX[3] | 0x11);
        }
        D3IniFlags = D3IniFlags & 0xffffff7f;
      }
      in_EAX = *(char **)(in_EAX + 0x28);
    } while (in_EAX != (char *)0x0);
  }
  return;
}
