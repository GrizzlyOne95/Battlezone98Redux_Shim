
void FUN_007755b0(void)

{
  undefined4 uVar1;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  memset(&DAT_02c04198,0,0x154);
  memset(&DAT_02c042f0,0,0x1880);
  DAT_02c04198 = FUN_00787ac0(s_AnimatedSky_008f047c,"Count",0,&DAT_02cc40c0);
  DAT_02c0419c = FUN_00787ac0(s_AnimatedSky_008f047c,"Diameter",400,&DAT_02cc40c0);
  if (DAT_02c0419c < 1) {
    DAT_02c0419c = 1;
  }
  DAT_02c041a4 = FUN_00787ac0(s_AnimatedSky_008f047c,"minDelay",100,&DAT_02cc40c0);
  DAT_02c041a8 = FUN_00787ac0(s_AnimatedSky_008f047c,"maxDelay",500,&DAT_02cc40c0);
  if ((DAT_02c04198 < 1) || (0x20 < DAT_02c04198)) {
    DAT_02c04198 = 0x10;
  }
  for (local_1c = 0; local_1c < 8; local_1c = local_1c + 1) {
    sprintf(local_18,"Name%d",local_1c);
    FUN_00787a30(s_AnimatedSky_008f047c,local_18,&DAT_008a1ad8,&DAT_02c041ac + local_1c * 0x10,0x10,
                 &DAT_02cc40c0);
    uVar1 = FUN_0068bed0(&DAT_02c041ac + local_1c * 0x10);
    *(undefined4 *)(&DAT_02c042cc + local_1c * 4) = uVar1;
    sprintf(local_18,"Frames%d",local_1c);
    uVar1 = FUN_00787ac0(s_AnimatedSky_008f047c,local_18,0,&DAT_02cc40c0);
    *(undefined4 *)(&DAT_02c042ac + local_1c * 4) = uVar1;
    sprintf(local_18,"Rate%d",local_1c);
    uVar1 = FUN_00787ac0(s_AnimatedSky_008f047c,local_18,100,&DAT_02cc40c0);
    *(undefined4 *)(&DAT_02c0424c + local_1c * 4) = uVar1;
    sprintf(local_18,"Size%d",local_1c);
    uVar1 = FUN_00787ac0(s_AnimatedSky_008f047c,local_18,0x244,&DAT_02cc40c0);
    *(undefined4 *)(&DAT_02c0426c + local_1c * 4) = uVar1;
  }
  FUN_0083e885();
  return;
}

