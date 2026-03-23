
void FUN_00435240(UINT param_1,WPARAM param_2,LPARAM param_3)

{
  short sVar1;
  short sVar2;
  BOOL BVar3;
  tagMSG local_2c;
  int local_10;
  int local_c;
  int local_8;
  
  while( true ) {
    local_10 = param_1 - 0x200;
    sVar1 = (short)param_3;
    sVar2 = (short)((uint)param_3 >> 0x10);
    switch(local_10) {
    case 0:
      local_c = (int)sVar1;
      local_8 = (int)sVar2;
      FUN_005d4f90(local_c,local_8);
      break;
    case 1:
      local_c = (int)sVar1;
      local_8 = (int)sVar2;
      FUN_005d4fe0(local_c,local_8,0);
      break;
    case 2:
      local_c = (int)sVar1;
      local_8 = (int)sVar2;
      FUN_005d5030(local_c,local_8,0);
      break;
    case 4:
      local_c = (int)sVar1;
      local_8 = (int)sVar2;
      FUN_005d4fe0(local_c,local_8,1);
      break;
    case 5:
      local_c = (int)sVar1;
      local_8 = (int)sVar2;
      FUN_005d5030(local_c,local_8,1);
      break;
    case 10:
      FUN_005d4f60((int)(short)(param_2 >> 0x10));
    }
    BVar3 = PeekMessageA(&local_2c,(HWND)0x0,0x200,0x20e,1);
    if (BVar3 == 0) break;
    TranslateMessage(&local_2c);
    param_1 = local_2c.message;
    param_2 = local_2c.wParam;
    param_3 = local_2c.lParam;
  }
  return;
}

