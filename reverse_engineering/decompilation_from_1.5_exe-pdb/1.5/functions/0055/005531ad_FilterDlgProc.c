/*
 * Entry: 005531ad
 * Name: FilterDlgProc
 * Namespace: Global
 * Signature: int FilterDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl FilterDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND hWnd;
  ShellBitmap *pSVar1;
  ShellButton *pSVar2;
  HDC pHVar3;
  int iVar4;
  HGDIOBJ pvVar5;
  uint uVar6;
  char **ppcVar7;
  int iVar8;
  tagPOINT *lpPoint;
  int iVar9;
  tagPOINT local_64;
  tagRECT local_5c;
  ShellButton **local_4c;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 == 2) {
        ReleaseCapture();
        pSVar1 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar1);
        }
        uVar6 = 0;
        do {
          pSVar2 = *(ShellButton **)((int)filterButton + uVar6);
          if (pSVar2 != (ShellButton *)0x0) {
            ShellButton::~ShellButton(pSVar2);
            operator_delete(pSVar2);
          }
          *(undefined4 *)((int)filterButton + uVar6) = 0;
          uVar6 = uVar6 + 4;
        } while (uVar6 < 0x24);
      }
      else {
        if (param_2 != 0xf) {
          uVar6 = 5;
          if (param_2 != 0x14) {
            if (param_2 == 0x20) {
              set_cursor(0);
              SetWindowLongA((HWND)param_1,0,1);
            }
            else {
              if (param_2 != 0x110) {
                return 0;
              }
              SetFontRecursive(param_1);
              GetClientRect((HWND)shell_hwnd,&local_5c);
              local_64.x = local_5c.left + 0x62;
              local_64.y = local_5c.top + 0x28;
              lpPoint = &local_64;
              hWnd = GetWindow((HWND)param_1,4);
              ClientToScreen(hWnd,lpPoint);
              local_5c.left = local_5c.left + local_64.x;
              local_5c.right = local_5c.right + local_64.x;
              local_5c.top = local_5c.top + local_64.y;
              local_5c.bottom = local_5c.bottom + local_64.y;
              MoveWindow((HWND)param_1,local_5c.left,local_5c.top,100,0xb4,1);
              pSVar1 = operator_new(0x20);
              if (pSVar1 == (ShellBitmap *)0x0) {
                backGround = (ShellBitmap *)0x0;
              }
              else {
                backGround = ShellBitmap::ShellBitmap(pSVar1,"bitmap\\filterdn.bmp",0,0);
              }
              ppcVar7 = &mapFilter[0].label;
              local_4c = filterButton;
              do {
                pSVar2 = operator_new(0x110);
                if (pSVar2 == (ShellButton *)0x0) {
                  pSVar2 = (ShellButton *)0x0;
                }
                else {
                  pSVar2 = ShellButton::ShellButton
                                     (pSVar2,param_1,shell_hInstance,0x81c,0x81b,0x81b,4,uVar6,0x5c,
                                      0xc,1,((MapFilterInfo *)(ppcVar7 + -1))->name);
                }
                *local_4c = pSVar2;
                read_text_label("multi_three",*ppcVar7,pSVar2->labelText);
                local_4c = local_4c + 1;
                uVar6 = uVar6 + 0xd;
                ppcVar7 = ppcVar7 + 3;
              } while (uVar6 < 0x7a);
            }
          }
          return 1;
        }
        pHVar3 = BeginPaint((HWND)param_1,&local_48);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar3);
        uVar6 = 0;
        do {
          ShellButton::UpdateButton(*(ShellButton **)((int)filterButton + uVar6),(HDC__ *)pHVar3);
          uVar6 = uVar6 + 4;
        } while (uVar6 < 0x24);
        EndPaint((HWND)param_1,&local_48);
      }
      return 0;
    }
  }
  else {
    if (param_2 == 0x136) goto LAB_0055346a;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        local_4c = (ShellButton **)((uint)param_4 >> 0x10);
        uVar6 = 0;
        do {
          iVar9 = 0;
          iVar8 = 1;
          iVar4 = ShellButton::CheckRollOver
                            (*(ShellButton **)((int)filterButton + uVar6),param_4 & 0xffff,
                             (uint)local_4c & 0xffff);
          ShellButton::SetButtonMode(*(ShellButton **)((int)filterButton + uVar6),iVar4,iVar8,iVar9)
          ;
          uVar6 = uVar6 + 4;
        } while (uVar6 < 0x24);
        return 0;
      }
      if (param_2 != 0x202) {
        return 0;
      }
      uVar6 = 0;
      local_4c = (ShellButton **)((uint)param_4 >> 0x10);
      do {
        iVar4 = ShellButton::CheckRollOver
                          (filterButton[uVar6],param_4 & 0xffff,(uint)local_4c & 0xffff);
        if (iVar4 != 0) {
          nCurrentMultiMap = uVar6;
          Shell_EndDialog(param_1,1);
          return 0;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < 9);
      return 0;
    }
  }
  SetTextColor((HDC)param_3,0xff00);
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_0055346a:
  pvVar5 = GetStockObject(4);
  return (int)pvVar5;
}
