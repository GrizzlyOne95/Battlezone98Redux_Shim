/*
 * Entry: 0056e696
 * Name: CardDlgProc
 * Namespace: Global
 * Signature: int CardDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CardDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  WPARAM wParam;
  
  if (param_2 == 0x110) {
    wParam = 0;
    if (0 < numCards) {
      do {
        sprintf(strbuf,"%s",cardNames[wParam]);
        SendDlgItemMessageA((HWND)param_1,0x429,0x181,wParam,0xc70568);
        wParam = wParam + 1;
      } while ((int)wParam < numCards);
    }
    SendDlgItemMessageA((HWND)param_1,0x429,0x186,wParam - 1,0);
  }
  else if ((param_2 == 0x111) && ((short)param_3 == 0x52f)) {
    boardSelected = SendDlgItemMessageA((HWND)param_1,0x429,0x188,0,0);
    Shell_EndDialog(param_1,1);
  }
  return 0;
}
