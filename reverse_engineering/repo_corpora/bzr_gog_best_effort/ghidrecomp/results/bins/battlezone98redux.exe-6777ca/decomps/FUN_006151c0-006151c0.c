
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006151c0(void)

{
  DAT_02cf4000 = 0;
  _DAT_02a13da4 = FUN_00787ac0(&DAT_0088b2d8,"SkyHeight",100,&DAT_02cc40c0);
  DAT_02a13d90 = FUN_00787ac0(&DAT_0088b2d8,"SkyType",0,&DAT_02cc40c0);
  _DAT_02a13dd0 = 0;
  _DAT_02a13de8 = 0;
  FUN_00787a30(&DAT_008ea4c4,"SkyTexture",&DAT_008a1ad8,&DAT_02a13d94,0x10,&DAT_02cc40c0);
  FUN_00787a30(&DAT_008ea4c4,"SunTexture",&DAT_008a1ad8,&DAT_02a13dd8,0x10,&DAT_02cc40c0);
  if (DAT_02a13dd8 != '\0') {
    DAT_02cf4000 = FUN_0068bed0(&DAT_02a13dd8);
  }
  FUN_00616c60();
  FUN_00775e80();
  FUN_007755b0();
  FUN_00776690();
  return;
}

