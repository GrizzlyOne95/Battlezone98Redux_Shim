
void FUN_00435400(UINT param_1,uint param_2,uint param_3)

{
  short sVar1;
  int iVar2;
  BOOL BVar3;
  tagMSG local_28;
  uint local_c;
  int local_8;
  
  while( true ) {
    local_8 = param_1 - 0x200;
    sVar1 = (short)(param_2 >> 0x10);
    switch(local_8) {
    case 0:
      iVar2 = FUN_004344a0();
      if (iVar2 == 2) {
        DAT_02cebca0 = 0;
        DAT_02cebca4 = 0;
        local_c = (uint)((param_2 & 1) != 0);
        FUN_0041e7f0(param_3 & 0xffff,param_3 >> 0x10,local_c);
      }
      else {
        DAT_02cebca0 = (param_3 & 0xffff) - (DAT_02cecf00 >> 1);
        DAT_02cebca4 = (param_3 >> 0x10) - (DAT_02cecf04 >> 1);
      }
      break;
    case 1:
      DAT_02cebca8 = DAT_02cebca8 & 0xfffffffe;
      DAT_02cebcac = DAT_02cebcac | 1;
      iVar2 = FUN_004344a0();
      if (iVar2 == 2) {
        FUN_0041e7b0(param_3 & 0xffff,param_3 >> 0x10);
      }
      break;
    case 2:
      DAT_02cebca8 = DAT_02cebca8 | 1;
      iVar2 = FUN_004344a0();
      if (iVar2 == 2) {
        FUN_0041e760(param_3 & 0xffff,param_3 >> 0x10,0,0);
      }
      break;
    case 4:
      DAT_02cebca8 = DAT_02cebca8 & 0xfffffffb;
      DAT_02cebcac = DAT_02cebcac | 4;
      break;
    case 5:
      DAT_02cebca8 = DAT_02cebca8 | 4;
      break;
    case 7:
      DAT_02cebca8 = DAT_02cebca8 & 0xfffffffd;
      DAT_02cebcac = DAT_02cebcac | 2;
      break;
    case 8:
      DAT_02cebca8 = DAT_02cebca8 | 2;
      break;
    case 10:
      if (sVar1 < 1) {
        if ((int)param_2 < 0) {
          DAT_02cebcac = DAT_02cebcac | 0x20;
          DAT_02cebca8 = DAT_02cebca8 | 0x20;
        }
      }
      else {
        DAT_02cebcac = DAT_02cebcac | 0x40;
        DAT_02cebca8 = DAT_02cebca8 | 0x40;
      }
      break;
    case 0xb:
      if ((param_2 >> 0x10 & 1) != 0) {
        DAT_02cebca8 = DAT_02cebca8 & 0xfffffff7;
        DAT_02cebcac = DAT_02cebcac | 8;
      }
      if ((param_2 >> 0x10 & 2) != 0) {
        DAT_02cebca8 = DAT_02cebca8 & 0xffffffef;
        DAT_02cebcac = DAT_02cebcac | 0x10;
      }
      break;
    case 0xc:
      if ((param_2 >> 0x10 & 1) != 0) {
        DAT_02cebca8 = DAT_02cebca8 | 8;
      }
      if ((param_2 >> 0x10 & 2) != 0) {
        DAT_02cebca8 = DAT_02cebca8 | 0x10;
      }
      break;
    case 0xe:
      if (sVar1 < 1) {
        if ((int)param_2 < 0) {
          DAT_02cebcac = DAT_02cebcac | 0x80;
          DAT_02cebca8 = DAT_02cebca8 | 0x80;
        }
      }
      else {
        DAT_02cebcac = DAT_02cebcac | 0x100;
        DAT_02cebca8 = DAT_02cebca8 | 0x100;
      }
    }
    BVar3 = PeekMessageA(&local_28,(HWND)0x0,0x200,0x20e,1);
    if (BVar3 == 0) break;
    TranslateMessage(&local_28);
    param_1 = local_28.message;
    param_2 = local_28.wParam;
    param_3 = local_28.lParam;
  }
  return;
}

