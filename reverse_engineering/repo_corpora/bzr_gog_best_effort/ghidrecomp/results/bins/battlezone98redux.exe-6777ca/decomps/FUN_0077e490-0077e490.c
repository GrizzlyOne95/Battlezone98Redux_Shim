
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0077e490(void)

{
  int iVar1;
  float10 fVar2;
  
  DAT_009454c8 = FUN_00787ac0("NormalView","Waves",0,s_render_cfg_008f0620);
  iVar1 = FUN_00787ac0("NormalView","VisibilityScale",100,s_render_cfg_008f0620);
  DAT_008f05dc = (float)iVar1 * 0.01;
  iVar1 = FUN_00572ab0();
  if ((iVar1 != 0) && (1.5 < DAT_008f05dc)) {
    DAT_008f05dc = 1.5;
  }
  iVar1 = FUN_00787ac0("SateliteView","VisibilityRange",(int)DAT_008f05f0,s_render_cfg_008f0620);
  DAT_008f05f0 = (float)iVar1;
  DAT_008eaab0 = FUN_00787ac0("Debug",&DAT_0089d35c,DAT_008eaab0,s_render_cfg_008f0620);
  _DAT_008f05a0 = FUN_00787ac0("NormalView","FogStart",100,&DAT_02cc40c0);
  DAT_008f05a4 = FUN_00787ac0("NormalView","FogEnd",0xfa,&DAT_02cc40c0);
  iVar1 = FUN_00787ac0("NormalView","FogBreak",0x32,&DAT_02cc40c0);
  DAT_008f05a8 = (float)iVar1 * 0.01;
  iVar1 = FUN_00787ac0("NormalView","VisibilityRange",0xfa,&DAT_02cc40c0);
  DAT_008f0598 = (float)iVar1;
  iVar1 = FUN_00787ac0("NormalView","FlatRange",0xfa,&DAT_02cc40c0);
  DAT_008f059c = (float)iVar1;
  iVar1 = FUN_00787ac0("NormalView","Intensity",0x1e,&DAT_02cc40c0);
  DAT_008f05b0 = (float)iVar1 * 0.01;
  iVar1 = FUN_00787ac0("NormalView","Ambient",0,&DAT_02cc40c0);
  DAT_008f05b8 = (float)iVar1 * 0.01;
  iVar1 = FUN_00787ac0("NormalView","ShadowLuma",0x4b,&DAT_02cc40c0);
  DAT_02cd9444 = (float)iVar1 * 0.01;
  iVar1 = FUN_00787ac0("NormalView","TerrainShadowLuma",0x32,&DAT_02cc40c0);
  _DAT_02cd9448 = (float)iVar1 * 0.01;
  iVar1 = FUN_00787ac0("NormalView","carAmbient",0x37,&DAT_02cc40c0);
  DAT_02cd94e0 = (float)iVar1 * 0.01;
  fVar2 = (float10)FUN_00787b60(&DAT_0089d064,"Height",0,&DAT_02cc40c0);
  DAT_009454b0 = (float)fVar2;
  iVar1 = FUN_00787ac0("NormalView","GroundFogTop",0,&DAT_02cc40c0);
  DAT_02c0697c = iVar1 * 10;
  _DAT_02c042ec = FUN_00787ac0("NormalView","GroundFogBottom",0,&DAT_02cc40c0);
  _DAT_02c042ec = _DAT_02c042ec * 10;
  _DAT_02c06978 = FUN_00787ac0("NormalView","GroundFogStart",0x3c,&DAT_02cc40c0);
  DAT_008f0598 = DAT_008f0598 * DAT_008f05dc;
  DAT_008f05a4 = (int)((float)DAT_008f05a4 * DAT_008f05dc);
  DAT_008f059c = DAT_008f059c * DAT_008f05dc;
  if (1e+09 < DAT_008f0598) {
    DAT_008f0598 = 1e+09;
  }
  if (1e+09 < DAT_008f05f0) {
    DAT_008f05f0 = 1e+09;
  }
  if (DAT_02cd94e0 * 255.0 < (float)_DAT_008f05ec) {
    DAT_02cd94e0 = (float)_DAT_008f05ec / 255.0;
  }
  if ((DAT_02cd9444 <= 0.0) || (1.0 < DAT_02cd9444)) {
    DAT_02cd9444 = DAT_02cd94e0;
  }
  _DAT_008f0608 = DAT_008f05b0;
  _DAT_008f0610 = DAT_008f05b8;
  if (((float)_DAT_008f05a0 < DAT_008f0598 - 14.0) && (DAT_008f0598 - 14.15 < (float)DAT_008f05a4))
  {
    DAT_008f05a4 = (int)(DAT_008f0598 - 14.15);
  }
  if (DAT_008f05a8 < 0.01) {
    DAT_008f05a8 = 0.01;
  }
  if (0.99 < DAT_008f05a8) {
    DAT_008f05a8 = 0.99;
  }
  if ((0 < DAT_02c0697c - _DAT_02c042ec) && (0 < DAT_008f05a4 - _DAT_008f05a0)) {
    _DAT_02c00ef4 =
         (DAT_008f05dc * 10.0 * (float)(DAT_008f05a4 - _DAT_008f05a0)) /
         (float)(DAT_02c0697c - _DAT_02c042ec);
  }
  return;
}

