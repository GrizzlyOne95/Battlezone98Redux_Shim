
/* WARNING: Removing unreachable block (ram,0x00618cea) */

void FUN_00618c10(undefined4 param_1,int param_2,char *param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  BOOL BVar4;
  RAWINPUTDEVICE local_124;
  int local_118;
  undefined4 local_114;
  DWORD local_110;
  DWORD local_10c;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00822830();
  uVar1 = FUN_00765ca0();
  FUN_0081e0c0("Starting BattleZone 98 Redux, Version %s, %s\n","2.2.301",uVar1);
  DAT_009183d8 = 0;
  uVar2 = _controlfp(0,0);
  _controlfp(0x1000000,0x3000000);
  FUN_004fe800(&DAT_02cf3000,uVar2,0);
  memset(&DAT_02cecee0,0,0x90);
  DAT_02cecec0 = param_1;
  FUN_008205e0();
  FUN_0081c650();
  strncpy(local_108,param_3,0xff);
  local_118 = FUN_004344a0();
  local_114 = 0;
  DAT_00915540 = 0;
  uVar1 = FUN_004344a0();
  FUN_004344b0(uVar1);
  iVar3 = FUN_007d5120(param_3);
  if (iVar3 == 0) {
    FUN_007d6c70("BattleZone found incorrect command line arguments");
  }
  iVar3 = FUN_004344a0();
  if (local_118 != iVar3) {
    FUN_0081c650();
  }
  FUN_00482880();
  FUN_00764d80();
  if (DAT_009183cc != 0) {
    FUN_007d6080();
  }
  DAT_009467b4 = 0;
  uVar2 = FUN_0056f760(0);
  srand(uVar2);
  FUN_0081eb30();
  FUN_005d4280();
  if (param_2 != 0) {
    FUN_007d64a0("BattleZone is already running");
                    /* WARNING: Subroutine does not return */
    exit(0x70);
  }
  DAT_02cecf70 = (int)malloc(0x400000);
  if ((void *)DAT_02cecf70 == (void *)0x0) {
    FUN_007d64a0("Unable Allocate Virtual Memory, aborting Program...");
  }
  memset(&DAT_02cecee0,0,0x90);
  FUN_00437480(param_1,"Battlezone 98 Redux (2.2.301)");
  iVar3 = FUN_00618b60(&DAT_02cecee0);
  if (iVar3 != 0) {
    FUN_007d6c70("BattleZone Init_Graphic_System");
  }
  DAT_02cf44a0 = DAT_009183fc;
  FUN_007c6910();
  FUN_0061a140(1);
  iVar3 = (*DAT_02cecf6c)(&DAT_02cecee0);
  if (iVar3 == 0) {
    FUN_007d6c70("BattleZone Init_Graphic_System");
  }
  FUN_00820ec0();
  FUN_0081df00();
  FUN_0068b0e0();
  DAT_0091552c = FUN_006898f0("char.0");
  FUN_0061a140(1);
  FUN_00434740(*(undefined4 *)(PTR_DAT_008fe1b8 + 8),*(undefined4 *)(PTR_DAT_008fe1b8 + 0xc));
  if (DAT_00918424 != 0) {
    local_124.usUsagePage = 1;
    local_124.usUsage = 2;
    local_124.dwFlags = 0;
    local_124.hwndTarget = (HWND)0x0;
    DAT_00918424 = RegisterRawInputDevices(&local_124,1,0xc);
  }
  DAT_00918428 = GetForegroundWindow();
  if (DAT_00918428 != DAT_02cf44a0) {
    BVar4 = SetForegroundWindow(DAT_02cf44a0);
    if (BVar4 == 0) {
      if (DAT_00918428 == (HWND)0x0) {
        DAT_00918428 = FindWindowA("Battlezone 98 Redux (2.2.301)",(LPCSTR)0x0);
      }
      local_110 = GetWindowThreadProcessId(DAT_00918428,(LPDWORD)0x0);
      local_10c = GetWindowThreadProcessId(DAT_02cf44a0,(LPDWORD)0x0);
      AttachThreadInput(local_110,local_10c,1);
      SetForegroundWindow(DAT_02cf44a0);
      AttachThreadInput(local_110,local_10c,0);
    }
    BringWindowToTop(DAT_02cf44a0);
  }
  FUN_00764f50();
  GetClientRect(DAT_02cf44a0,(LPRECT)&DAT_02ceceb0);
  if (DAT_0091556c == 0) {
    FUN_00434170(2);
  }
  FUN_00820fb0();
  FUN_008205e0();
  if (DAT_009183f4 != 0) {
    *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 1;
  }
  FUN_004d41b0();
  FUN_00439f10();
  FUN_0083e885();
  return;
}

