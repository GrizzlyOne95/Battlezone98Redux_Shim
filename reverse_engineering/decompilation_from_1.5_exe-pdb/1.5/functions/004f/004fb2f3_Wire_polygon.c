/*
 * Entry: 004fb2f3
 * Name: Wire_polygon
 * Namespace: Global
 * Signature: void Wire_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Wire_polygon(_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  double dVar1;
  double dVar2;
  float fVar3;
  long local_24;
  double local_1c;
  long local_14;
  double local_c;
  
  fVar3 = (float)Float2Int;
  local_c = (double)(param_2[param_3 + -1].Vector.x + fVar3);
  local_1c = (double)(param_2[param_3 + -1].Vector.y + fVar3);
  if (0 < param_3) {
    while( true ) {
      dVar1 = (double)((param_2->Vector).x + fVar3);
      local_24 = SUB84(dVar1,0);
      dVar2 = (double)(fVar3 + (param_2->Vector).y);
      local_14 = SUB84(dVar2,0);
      Graphic_Line(param_1,local_c._0_4_,local_1c._0_4_,local_24,local_14,param_4.Color & 0xff,
                   SOLID_PIXELS);
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
      if (param_3 == 0) break;
      fVar3 = (float)Float2Int;
      local_1c = dVar2;
      local_c = dVar1;
    }
  }
  return;
}
