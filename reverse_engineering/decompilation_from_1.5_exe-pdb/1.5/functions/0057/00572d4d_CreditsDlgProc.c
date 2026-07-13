/*
 * Entry: 00572d4d
 * Name: CreditsDlgProc
 * Namespace: Global
 * Signature: int CreditsDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl CreditsDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellBitmap *pSVar1;
  ShellButton *pSVar2;
  TextLabel *pTVar3;
  TextWindow *pTVar4;
  HDC pHVar5;
  HGDIOBJ pvVar6;
  int iVar7;
  ShellButton *extraout_EDX;
  ShellButton *extraout_EDX_00;
  char *pcVar8;
  bool bVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  DWORD DStack_1f54c;
  tagPAINTSTRUCT tStack_1f548;
  char acStack_1f508 [128000];
  CHAR local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 < 0x137) {
    if (param_2 != 0x136) {
      if (param_2 == 2) {
        CleanCurrentBackground();
        pSVar1 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar1);
          backGround = (ShellBitmap *)0x0;
        }
        pSVar2 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar2);
          ulButton = (ShellButton *)0x0;
        }
        pTVar3 = message;
        if (message != (TextLabel *)0x0) {
          TextLabel::~TextLabel(message);
          operator_delete(pTVar3);
          message = (TextLabel *)0x0;
        }
        pTVar4 = credits;
        if (credits == (TextWindow *)0x0) {
          return 0;
        }
        TextWindow::~TextWindow(credits);
        operator_delete(pTVar4);
        credits = (TextWindow *)0x0;
        return 0;
      }
      if (param_2 == 0xf) {
        pHVar5 = BeginPaint((HWND)param_1,&tStack_1f548);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar5);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar5);
        TextLabel::DrawLabelText(message,(HDC__ *)pHVar5,(char *)0x0,0);
        (**(code **)credits->_padding_)(pHVar5,0);
        EndPaint((HWND)param_1,&tStack_1f548);
      }
      else if (param_2 != 0x14) {
        if (param_2 == 0x20) {
          set_cursor(0);
          SetWindowLongA((HWND)param_1,0,1);
        }
        else {
          if (param_2 != 0x110) {
            return 0;
          }
          GetUserNameA(local_108,&DStack_1f54c);
          init_screen_pos(param_1);
          init_bitmap_dc(param_1);
          pSVar1 = operator_new(0x20);
          if (pSVar1 == (ShellBitmap *)0x0) {
            backGround = (ShellBitmap *)0x0;
          }
          else {
            backGround = ShellBitmap::ShellBitmap(pSVar1,"bitmap\\death.bmp",0,0);
          }
          SetCurrentBackground(param_1,backGround);
          pSVar2 = operator_new(0x110);
          if (pSVar2 == (ShellButton *)0x0) {
            ulButton = (ShellButton *)0x0;
          }
          else {
            ulButton = ShellButton::ShellButton
                                 (pSVar2,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                                  "BACK");
          }
          ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
          GetMissionDesc("credits.des",acStack_1f508);
          pTVar3 = operator_new(0x128);
          if (pTVar3 == (TextLabel *)0x0) {
            message = (TextLabel *)0x0;
          }
          else {
            message = TextLabel::TextLabel
                                (pTVar3,param_1,"THE BATTLE ZONE TEAM",0xbf,0x32,0x102,0x1c,0);
          }
          pTVar4 = operator_new(0x1f438);
          if (pTVar4 == (TextWindow *)0x0) {
            credits = (TextWindow *)0x0;
          }
          else {
            credits = TextWindow::TextWindow(pTVar4,param_1,acStack_1f508,0x3f,0x50,0x202,400,0);
          }
          iVar7 = 9;
          bVar9 = true;
          pcVar11 = local_108;
          pcVar8 = "agoldman";
          do {
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            bVar9 = *pcVar11 == *pcVar8;
            pcVar11 = pcVar11 + 1;
            pcVar8 = pcVar8 + 1;
          } while (bVar9);
          if (bVar9) {
            pcVar11 = "ANDREW AND HIS CREW";
          }
          else {
            iVar7 = 9;
            bVar9 = true;
            pcVar11 = local_108;
            pcVar8 = "gcollins";
            do {
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              bVar9 = *pcVar11 == *pcVar8;
              pcVar11 = pcVar11 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              pcVar11 = "GEORGE AND HIS POSSE";
            }
            else {
              iVar7 = 7;
              bVar9 = true;
              pcVar11 = local_108;
              pcVar8 = "gsutty";
              do {
                if (iVar7 == 0) break;
                iVar7 = iVar7 + -1;
                bVar9 = *pcVar11 == *pcVar8;
                pcVar11 = pcVar11 + 1;
                pcVar8 = pcVar8 + 1;
              } while (bVar9);
              if (!bVar9) {
                return 1;
              }
              pcVar11 = "GRAPHICS SOFTWARE LABS RULES";
            }
          }
          TextLabel::SetLabelText(message,pcVar11);
        }
      }
      return 1;
    }
    iVar7 = 4;
  }
  else {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        iVar12 = 0;
        iVar10 = 1;
        iVar7 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
        pSVar2 = extraout_EDX_00;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          iVar7 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
          if (iVar7 == 0) {
            return 0;
          }
          Shell_EndDialog(param_1,1);
          return 0;
        }
        iVar7 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
        if (iVar7 == 0) {
          return 0;
        }
        iVar12 = 0;
        iVar10 = 1;
        iVar7 = 2;
        pSVar2 = extraout_EDX;
      }
      ShellButton::SetButtonMode(pSVar2,iVar7,iVar10,iVar12);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar7 = 5;
  }
  pvVar6 = GetStockObject(iVar7);
  return (int)pvVar6;
}
