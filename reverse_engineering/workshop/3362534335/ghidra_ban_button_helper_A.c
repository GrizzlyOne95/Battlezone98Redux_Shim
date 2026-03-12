
void FUN_1000df80(void)

{
  undefined4 uVar1;
  void *pvVar2;
  float in_XMM2_Da;
  float in_XMM3_Da;
  
  uVar1 = DAT_1002af4c;
  pvVar2 = operator_new(0x1ec);
  memset(pvVar2,0,0x1ec);
  DAT_1002af3c = pvVar2;
  DAT_1002af3c = (void *)(*DAT_1002ae60)("Ban User",in_XMM2_Da - 48.0,in_XMM3_Da + 96.0,0x42400000,
                                         0x42400000,0x20,uVar1,0,0);
  (*DAT_1002ae68)("MultiplayerModeButton_off.png");
  (*DAT_1002ae6c)("MultiplayerModeButton_over.png");
  (*DAT_1002ae70)("MultiplayerModeButton_on.png");
  (*DAT_1002ae74)(&DAT_10024c38);
  (*DAT_1002ae80)(FUN_1000ddd0);
  (*DAT_1002ae84)(FUN_1000ddb0);
  (*DAT_1002ae5c)(DAT_1002af3c,0);
  pvVar2 = operator_new(0x930);
  memset(pvVar2,0,0x930);
  DAT_1002af40 = pvVar2;
  DAT_1002af40 = (void *)(*DAT_1002ae64)("Lobby",0x43870000,0x44750000,0x43a90000,0x422c0000,0x8020,
                                         uVar1,0,0);
  (*DAT_1002ae78)("Ban highlighted player");
  (*DAT_1002ae7c)(0);
  (*DAT_1002ae5c)(DAT_1002af40,0);
  return;
}

