
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00616c60(void)

{
  int iVar1;
  float10 fVar2;
  
  _DAT_02a13da8 = 0;
  _DAT_02a13dac = 0;
  _DAT_02a13db0 = 0;
  _DAT_02a13db4 = 0;
  DAT_02a13db8 = 0.0;
  DAT_02a13dbc = 0.0;
  _DAT_02a13dc0 = 0.0;
  _DAT_02a13dc4 = 0.0;
  _DAT_02a13dc8 = 0;
  FUN_00787a30(&DAT_008ea4c4,"BackdropTexture",&DAT_008a1ad8,&DAT_02a13da8,0x10,&DAT_02cc40c0);
  if (DAT_02a13da8 == '\0') {
    FUN_00616e00();
  }
  else {
    iVar1 = FUN_00787ac0(&DAT_008ea4c4,"BackdropDistance",400,&DAT_02cc40c0);
    DAT_02a13db8 = (float)iVar1;
    iVar1 = FUN_00787ac0(&DAT_008ea4c4,"BackdropHeight",0x32,&DAT_02cc40c0);
    DAT_02a13dbc = (float)iVar1;
    iVar1 = FUN_00787ac0(&DAT_008ea4c4,"BackdropBase",0,&DAT_02cc40c0);
    _DAT_02a13dc4 = (float)iVar1;
    _DAT_02a13dc8 = FUN_00787ac0(&DAT_008ea4c4,"BackdropType",0,&DAT_02cc40c0);
    fVar2 = (float10)FUN_00417910(DAT_02a13db8 * DAT_02a13db8 +
                                  DAT_02a13dbc * 0.5 * DAT_02a13dbc * 0.5);
    _DAT_02a13dc0 = (float)fVar2 * 2.0;
    fVar2 = (float10)FUN_004d9610(0xbf800000);
    _DAT_02a13dcc = 0.5 / (float)fVar2;
  }
  return;
}

