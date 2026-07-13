/*
 * Entry: 00541e51
 * Name: Radar_Quads
 * Namespace: Global
 * Signature: void Radar_Quads(_GRAPHIC_BUFFER * param_1, RADAR_MESH * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Radar_Quads(_GRAPHIC_BUFFER *param_1,RADAR_MESH *param_2)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  RADAR_MESH *pRVar4;
  RADAR_MESH *pRVar5;
  byte *pbVar6;
  byte *pbVar7;
  int unaff_EDI;
  int iVar8;
  POINT_3D local_4334;
  float local_431c;
  float local_4318;
  undefined4 local_4314;
  undefined4 local_4310;
  undefined4 local_430c;
  float local_4308;
  float local_4304;
  float local_4300;
  undefined4 local_42fc;
  undefined4 local_42f8;
  undefined4 local_42f4;
  float local_42f0;
  float local_42ec;
  float local_42e8;
  undefined4 local_42e4;
  undefined4 local_42e0;
  undefined4 local_42dc;
  float local_42d8;
  undefined1 local_408c [88];
  byte *local_4034;
  RADAR_MESH *local_4030;
  RADAR_MESH *local_402c;
  int local_4028;
  RADAR_MESH *local_4024;
  int local_4020;
  byte *local_401c;
  int local_4018;
  int local_4014;
  uint local_4010;
  int local_400c;
  byte local_4008 [16384];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_408c;
  local_4028 = Set_Rounding(unaff_EDI);
  iVar8 = param_2->dx;
  iVar1 = param_2->dy;
  local_4020 = iVar8;
  Render_RadarBackdrop();
  local_401c = local_4008;
  local_4010 = param_2->wz;
  for (local_4014 = iVar1; 0 < local_4014; local_4014 = local_4014 + -1) {
    local_4018 = param_2->wx;
    local_400c = iVar8;
    while (0 < local_400c) {
      bVar3 = GetLuma256(local_4018,local_4010);
      local_400c = local_400c + -1;
      local_4018 = local_4018 + 1;
      *local_401c = bVar3;
      local_401c = local_401c + 1;
    }
    local_4010 = local_4010 + 1;
  }
  pbVar2 = local_4008;
  local_4014 = iVar1;
joined_r0x00541f05:
  do {
    pRVar4 = param_2;
    pbVar6 = pbVar2;
    local_4014 = local_4014 + -1;
    if (local_4014 < 1) {
      Set_Rounding(unaff_EDI);
      return;
    }
    local_402c = (RADAR_MESH *)(pRVar4->mesh + iVar8);
    local_4034 = pbVar6 + iVar8;
    pRVar5 = local_402c;
    pbVar7 = local_4034;
    local_400c = iVar8;
    while( true ) {
      local_400c = local_400c + -1;
      if ((pRVar4->mesh[0].x != 0) && (pRVar5->mesh[0].x != 0)) goto LAB_00542087;
      pbVar2 = local_4034;
      param_2 = local_402c;
      if (local_400c < 1) break;
      pRVar4 = (RADAR_MESH *)(pRVar4->mesh + 1);
      pRVar5 = (RADAR_MESH *)(pRVar5->mesh + 1);
      pbVar6 = pbVar6 + 1;
      pbVar7 = pbVar7 + 1;
    }
  } while( true );
LAB_00542087:
  pbVar2 = local_4034;
  param_2 = local_402c;
  if (local_400c < 1) goto joined_r0x00541f05;
  local_4024 = (RADAR_MESH *)(pRVar4->mesh + 1);
  local_4018 = local_4024->mesh[0].x;
  param_2 = local_402c;
  if (local_4018 == 0) goto joined_r0x00541f05;
  local_4030 = (RADAR_MESH *)(pRVar5->mesh + 1);
  local_401c = (byte *)local_4030->mesh[0].x;
  param_2 = local_402c;
  if (local_401c == (byte *)0x0) goto joined_r0x00541f05;
  local_42ec = (float)pRVar4->mesh[0].x;
  bVar3 = *pbVar6;
  pbVar6 = pbVar6 + 1;
  local_42e8 = (float)pRVar4->mesh[0].y;
  local_42e4 = 0x3f800000;
  local_42e0 = 0;
  local_42dc = 0;
  local_42d8 = (float)bVar3 * 0.00390625;
  local_4304 = (float)local_4018;
  local_4300 = (float)pRVar4->mesh[1].y;
  local_42fc = 0x3f800000;
  local_42f8 = 0x3f800000;
  local_42f4 = 0;
  local_4010 = (uint)*pbVar7;
  local_42f0 = (float)*pbVar6 * 0.00390625;
  local_431c = (float)(int)local_401c;
  local_4318 = (float)pRVar5->mesh[1].y;
  local_4314 = 0x3f800000;
  local_4310 = 0x3f800000;
  local_430c = 0x3f800000;
  local_4308 = (float)pbVar7[1] * 0.00390625;
  local_4334.Vector.x = (float)pRVar5->mesh[0].x;
  local_4334.Vector.y = (float)pRVar5->mesh[0].y;
  local_4334.Vector.z = 1.0;
  local_4334.Texel.v = 1.0;
  local_4334.Texel.u = 0.0;
  local_4334.Texel.field2_0x8.luma = (float)local_4010 * 0.00390625;
  D3D_Gouraud_Quad(&local_4334,4,(POLYGON_SKIN)0xf6);
  local_400c = local_400c + 1;
  pRVar4 = local_4024;
  pRVar5 = local_4030;
  pbVar7 = pbVar7 + 1;
  iVar8 = local_4020;
  goto LAB_00542087;
}
