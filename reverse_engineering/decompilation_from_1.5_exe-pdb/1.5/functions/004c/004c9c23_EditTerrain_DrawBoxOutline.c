/*
 * Entry: 004c9c23
 * Name: EditTerrain::DrawBoxOutline
 * Namespace: EditTerrain
 * Signature: void DrawBoxOutline(EditTerrain * this, _GRAPHIC_BUFFER * param_1, int param_2, int param_3, float param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
EditTerrain::DrawBoxOutline
          (EditTerrain *this,_GRAPHIC_BUFFER *param_1,int param_2,int param_3,float param_4,
          int param_5)

{
  long extraout_EAX;
  long extraout_EAX_00;
  
  _ftol2_sse();
  Graphic_Line(param_1,param_2,param_3,extraout_EAX,param_3,param_5,SOLID_PIXELS);
  _ftol2_sse();
  Graphic_Line(param_1,extraout_EAX,param_3,extraout_EAX,extraout_EAX_00,param_5,SOLID_PIXELS);
  Graphic_Line(param_1,extraout_EAX,extraout_EAX_00,param_2,extraout_EAX_00,param_5,SOLID_PIXELS);
  Graphic_Line(param_1,param_2,extraout_EAX_00,param_2,param_3,param_5,SOLID_PIXELS);
  return;
}
