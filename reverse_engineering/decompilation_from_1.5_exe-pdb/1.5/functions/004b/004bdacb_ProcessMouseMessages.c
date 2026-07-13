/*
 * Entry: 004bdacb
 * Name: ProcessMouseMessages
 * Namespace: Global
 * Signature: void ProcessMouseMessages(uint param_1, uint param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessMouseMessages(uint param_1,uint param_2,long param_3)

{
  short sVar1;
  BOOL BVar2;
  tagMSG local_20;
  
  while( true ) {
    sVar1 = (short)(param_2 >> 0x10);
    switch(param_1) {
    case 0x200:
      deltaX = (param_3 & 0xffffU) - (Device.Client_Width >> 1);
      deltaY = ((uint)param_3 >> 0x10) - (Device.Client_Height >> 1);
      break;
    case 0x201:
      discreteClrMap = discreteClrMap & 0xfffffffe;
      discreteSetMap = discreteSetMap | 1;
      break;
    case 0x202:
      discreteClrMap = discreteClrMap | 1;
      break;
    case 0x204:
      discreteClrMap = discreteClrMap & 0xfffffffb;
      discreteSetMap = discreteSetMap | 4;
      break;
    case 0x205:
      discreteClrMap = discreteClrMap | 4;
      break;
    case 0x207:
      discreteClrMap = discreteClrMap & 0xfffffffd;
      discreteSetMap = discreteSetMap | 2;
      break;
    case 0x208:
      discreteClrMap = discreteClrMap | 2;
      break;
    case 0x20a:
      if (sVar1 == 0 || (int)param_2 < 0) {
        if ((int)param_2 < 0) {
          discreteSetMap = discreteSetMap | 0x20;
          discreteClrMap = discreteClrMap | 0x20;
        }
      }
      else {
        discreteSetMap = discreteSetMap | 0x40;
        discreteClrMap = discreteClrMap | 0x40;
      }
      break;
    case 0x20b:
      if ((param_2 >> 0x10 & 1) != 0) {
        discreteClrMap = discreteClrMap & 0xfffffff7;
        discreteSetMap = discreteSetMap | 8;
      }
      if ((param_2 & 0x20000) != 0) {
        discreteClrMap = discreteClrMap & 0xffffffef;
        discreteSetMap = discreteSetMap | 0x10;
      }
      break;
    case 0x20c:
      if ((param_2 >> 0x10 & 1) != 0) {
        discreteClrMap = discreteClrMap | 8;
      }
      if ((param_2 & 0x20000) != 0) {
        discreteClrMap = discreteClrMap | 0x10;
      }
      break;
    case 0x20e:
      if (sVar1 == 0 || (int)param_2 < 0) {
        if ((int)param_2 < 0) {
          discreteSetMap = discreteSetMap | 0x80;
          discreteClrMap = discreteClrMap | 0x80;
        }
      }
      else {
        discreteSetMap = discreteSetMap | 0x100;
        discreteClrMap = discreteClrMap | 0x100;
      }
    }
    BVar2 = PeekMessageA(&local_20,(HWND)0x0,0x200,0x20e,1);
    if (BVar2 == 0) break;
    TranslateMessage(&local_20);
    param_2 = local_20.wParam;
    param_3 = local_20.lParam;
    param_1 = local_20.message;
  }
  return;
}
