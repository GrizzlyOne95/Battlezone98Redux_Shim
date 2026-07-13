
void __fastcall FUN_00435a50(int param_1)

{
  uint uVar1;
  HMODULE hInst;
  int iVar2;
  int iVar3;
  HANDLE dwNewLong;
  HANDLE dwNewLong_00;
  UINT UVar4;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("WINDOW");
  local_8 = 0;
  (**(code **)(**(int **)(param_1 + 0xc) + 0x6c))(local_2c,&DAT_009183fc,uVar1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  DAT_00918400 = SetWindowLongA(DAT_009183fc,-4,0x619340);
  hInst = GetModuleHandleA((LPCSTR)0x0);
  UVar4 = 0;
  iVar2 = GetSystemMetrics(0x32);
  iVar3 = GetSystemMetrics(0x31);
  dwNewLong = LoadImageA(hInst,(LPCSTR)0xc9,1,iVar3,iVar2,UVar4);
  UVar4 = 0;
  iVar2 = GetSystemMetrics(0xc);
  iVar3 = GetSystemMetrics(0xb);
  dwNewLong_00 = LoadImageA(hInst,(LPCSTR)0xc9,1,iVar3,iVar2,UVar4);
  SetClassLongA(DAT_009183fc,-0xe,(LONG)dwNewLong_00);
  SetClassLongA(DAT_009183fc,-0x22,(LONG)dwNewLong);
  SendMessageA(DAT_009183fc,0x80,0,(LPARAM)dwNewLong);
  SendMessageA(DAT_009183fc,0x80,1,(LPARAM)dwNewLong_00);
  *DAT_02cecefc = DAT_009183fc;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

