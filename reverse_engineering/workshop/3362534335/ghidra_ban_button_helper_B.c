
void FUN_1000e1f0(void)

{
  undefined4 uVar1;
  void *pvVar2;
  
  uVar1 = DAT_1002af5c;
  pvVar2 = operator_new(0x1ec);
  memset(pvVar2,0,0x1ec);
  DAT_1002af44 = pvVar2;
  DAT_1002af44 = (void *)(*DAT_1002ae60)("Ban User",0xc2040000,0x446b8000,0x42400000,0x42400000,0,
                                         uVar1,0,0);
  (*DAT_1002ae68)("MultiplayerModeButton_off.png");
  (*DAT_1002ae6c)("MultiplayerModeButton_over.png");
  (*DAT_1002ae70)("MultiplayerModeButton_on.png");
  (*DAT_1002ae74)(&DAT_10024c38);
  (*DAT_1002ae80)(&LAB_1000e190);
  (*DAT_1002ae84)(FUN_1000e170);
  (*DAT_1002ae5c)(DAT_1002af44,0);
  pvVar2 = operator_new(0x930);
  memset(pvVar2,0,0x930);
  DAT_1002af48 = pvVar2;
  DAT_1002af48 = (void *)(*DAT_1002ae64)("Lobby",0x43870000,0x447a0000,0x43a90000,0x422c0000,0x20,
                                         uVar1,0,0);
  (*DAT_1002ae78)("Ban highlighted player");
  (*DAT_1002ae7c)(0);
  (*DAT_1002ae5c)(DAT_1002af48,0);
  return;
}

