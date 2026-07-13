/*
 * Entry: 00576e49
 * Name: SaveDlgProc
 * Namespace: Global
 * Signature: int SaveDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

int __cdecl SaveDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellButton *pSVar1;
  ShellButton *pSVar2;
  HWND pHVar3;
  ShellBitmap *pSVar4;
  ShellButton *pSVar5;
  TextLabel *pTVar6;
  HDC pHVar7;
  HGDIOBJ pvVar8;
  ShellButton *extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  ShellButton *this;
  ShellButton *this_00;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton **ppSVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int nHeight;
  int iVar14;
  BOOL bRepaint;
  char *lpString;
  ShellButton **local_160;
  RECT local_15c;
  ShellButton **local_14c;
  tagPAINTSTRUCT local_148;
  CHAR local_108 [40];
  undefined1 local_e0 [216];
  uint local_8;
  
  pSVar5 = ulButton;
  local_8 = __security_cookie ^ (uint)local_e0;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 == 2) {
        CleanCurrentBackground();
        SnapShotBackground();
        pSVar4 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar4);
          backGround = (ShellBitmap *)0x0;
        }
        pSVar5 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar5);
          ulButton = (ShellButton *)0x0;
        }
        pSVar5 = okButton;
        if (okButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(okButton);
          operator_delete(pSVar5);
          okButton = (ShellButton *)0x0;
        }
        pSVar5 = cancelButton;
        if (cancelButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(cancelButton);
          operator_delete(pSVar5);
          cancelButton = (ShellButton *)0x0;
        }
        ppSVar9 = slotArray;
        do {
          pSVar5 = *ppSVar9;
          if (pSVar5 != (ShellButton *)0x0) {
            ShellButton::~ShellButton(pSVar5);
            operator_delete(pSVar5);
            *ppSVar9 = (ShellButton *)0x0;
          }
          pTVar6 = message;
          ppSVar9 = ppSVar9 + 1;
        } while ((int)ppSVar9 < 0xc8fc2c);
        if (message != (TextLabel *)0x0) {
          TextLabel::~TextLabel(message);
          operator_delete(pTVar6);
          message = (TextLabel *)0x0;
          return 0;
        }
        return 0;
      }
      if (param_2 == 0xf) {
        pHVar7 = BeginPaint((HWND)param_1,&local_148);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(okButton,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar7);
        ppSVar9 = slotArray;
        do {
          ShellButton::UpdateButton(*ppSVar9,(HDC__ *)pHVar7);
          ppSVar9 = ppSVar9 + 1;
        } while ((int)ppSVar9 < 0xc8fc2c);
        TextLabel::DrawLabelText(message,(HDC__ *)pHVar7,(char *)0x0,0);
        EndPaint((HWND)param_1,&local_148);
        return 1;
      }
      if (param_2 == 0x14) {
        return 1;
      }
      if (param_2 == 0x20) {
        set_cursor(0);
        SetWindowLongA((HWND)param_1,0,1);
        return 1;
      }
      if (param_2 == 0x110) {
        nDisplayEdit = 0;
        nOverWrite = 0;
        init_screen_pos(param_1);
        init_bitmap_dc(param_1);
        nType = param_4;
        pSVar4 = operator_new(0x20);
        if (pSVar4 == (ShellBitmap *)0x0) {
          backGround = (ShellBitmap *)0x0;
        }
        else {
          backGround = ShellBitmap::ShellBitmap(pSVar4,"bitmap\\saveload.bmp",0,0);
        }
        SetCurrentBackground(param_1,backGround);
        currentSlot = (ShellButton *)0x0;
        nCurrentSlotIndex = 0;
        pSVar5 = operator_new(0x110);
        if (pSVar5 == (ShellButton *)0x0) {
          ulButton = (ShellButton *)0x0;
        }
        else {
          ulButton = ShellButton::ShellButton
                               (pSVar5,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                                "BACK");
        }
        ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
        pSVar5 = operator_new(0x110);
        if (pSVar5 == (ShellButton *)0x0) {
          okButton = (ShellButton *)0x0;
        }
        else {
          okButton = ShellButton::ShellButton
                               (pSVar5,param_1,shell_hInstance,0x831,0x832,0x830,0x17f,0x105,0x62,
                                0x22,1,"Ok");
        }
        ShellButton::HideButton(okButton,0);
        pSVar5 = operator_new(0x110);
        if (pSVar5 == (ShellButton *)0x0) {
          cancelButton = (ShellButton *)0x0;
        }
        else {
          cancelButton = ShellButton::ShellButton
                                   (pSVar5,param_1,shell_hInstance,0x831,0x832,0x830,0x1ec,0x105,
                                    0x62,0x22,1,"Cancel");
        }
        ShellButton::HideButton(cancelButton,0);
        local_160 = slotArray;
        local_14c = (ShellButton **)0x50;
        do {
          pSVar5 = operator_new(0x110);
          if (pSVar5 == (ShellButton *)0x0) {
            pSVar5 = (ShellButton *)0x0;
          }
          else {
            pSVar5 = ShellButton::ShellButton
                               (pSVar5,param_1,shell_hInstance,0x834,0x833,0x833,0x3c,(int)local_14c
                                ,0x9c,0x1a,1,"Empty");
          }
          local_14c = (ShellButton **)((int)local_14c + 0x1e);
          *local_160 = pSVar5;
          local_160 = local_160 + 1;
        } while ((int)local_14c < 0x17c);
        pTVar6 = operator_new(0x128);
        if (pTVar6 == (TextLabel *)0x0) {
          message = (TextLabel *)0x0;
        }
        else {
          message = TextLabel::TextLabel
                              (pTVar6,param_1,"Enter the game description",0x17b,0xa4,0xd8,0x28,0);
        }
        TextLabel::HideLabelText(message,0);
        ppSVar9 = slotArray;
        do {
          read_text_label("multi_error","Empty",(*ppSVar9)->labelText);
          ppSVar9 = ppSVar9 + 1;
        } while ((int)ppSVar9 < 0xc8fc2c);
        read_text_label("missions","back",ulButton->labelText);
        read_text_label("save_load","game_desc",message->textData);
        read_text_label("multi_popup","ok_button",okButton->labelText);
        read_text_label("multi_popup","cancel_button",cancelButton->labelText);
        iVar14 = 0;
        do {
          ppSVar9 = slotArray + iVar14;
          iVar14 = iVar14 + 1;
          GetSaveDesc(iVar14,*ppSVar9);
        } while (iVar14 < 10);
        bRepaint = 1;
        nHeight = 0x14;
        iVar13 = 0x82;
        iVar12 = 0xd2;
        iVar14 = 0x1a7;
        pHVar3 = GetDlgItem((HWND)param_1,0x427);
        MoveWindow(pHVar3,iVar14,iVar12,iVar13,nHeight,bRepaint);
        iVar14 = 0;
        pHVar3 = GetDlgItem((HWND)param_1,0x427);
        ShowWindow(pHVar3,iVar14);
        return 1;
      }
      if (param_2 != 0x111) {
        return 0;
      }
      if ((param_3 & 0xffff) != 1) {
        return 0;
      }
      pSVar5 = okButton;
      if (okButton->nButtonVisible == 0) {
        return 0;
      }
joined_r0x005775ac:
      if (nOverWrite == 0) {
        GetDlgItemTextA((HWND)param_1,0x427,local_108,0x100);
        if (currentSlot == (ShellButton *)0x0) {
          nDisplayEdit = 0;
          return 0;
        }
        iVar14 = GetSaveDesc(nCurrentSlotIndex,currentSlot);
        if (iVar14 != 0) {
          TextLabel::SetLabelText(message,"Overwrite existing game?");
          read_text_label("save_load","overwrite",message->textData);
          TextLabel::DrawLabelText(message,(char *)0x0,0);
          iVar14 = 0;
          pHVar3 = GetDlgItem((HWND)param_1,0x427);
          ShowWindow(pHVar3,iVar14);
          nDisplayEdit = 0;
          nOverWrite = 1;
          return 0;
        }
        ShellButton::SetLabelText(currentSlot,local_108);
        ShellButton::ShowButton(currentSlot,0);
        ShellButton::UpdateButton(currentSlot);
        save_bzone_game(nType,nCurrentSlotIndex,local_108);
        SetDlgItemTextA((HWND)param_1,0x427,"");
        iVar14 = 0;
        pHVar3 = GetDlgItem((HWND)param_1,0x427);
        ShowWindow(pHVar3,iVar14);
        TextLabel::HideLabelText(message,1);
      }
      else {
        nOverWrite = 0;
        ShellButton::SetButtonMode(pSVar5,2,1,0);
        GetDlgItemTextA((HWND)param_1,0x427,local_108,0x100);
        ShellButton::SetLabelText(currentSlot,local_108);
        ShellButton::ShowButton(currentSlot,1);
        delete_bzone_game(nCurrentSlotIndex);
        save_bzone_game(nType,nCurrentSlotIndex,local_108);
        SetDlgItemTextA((HWND)param_1,0x427,"");
        iVar14 = 0;
        pHVar3 = GetDlgItem((HWND)param_1,0x427);
        ShowWindow(pHVar3,iVar14);
        TextLabel::HideLabelText(message,1);
        pTVar6 = message;
        TextLabel::SetLabelText(message,"Enter the game description");
        read_text_label("save_load","game_desc",pTVar6->textData);
      }
      ShellButton::HideButton(okButton,0);
      ShellButton::HideButton(cancelButton,0);
LAB_005770b5:
      local_15c.bottom = 400;
      local_15c.right = 0x280;
      local_15c.top = 100;
      local_15c.left = 0x140;
      InvalidateRect((HWND)param_1,&local_15c,0);
      ShellButton::UpdateButton(okButton);
      ShellButton::UpdateButton(cancelButton);
      nDisplayEdit = 0;
      return 0;
    }
  }
  else {
    if (param_2 == 0x136) goto LAB_00577826;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        uVar10 = param_4 & 0xffff;
        iVar13 = 0;
        iVar12 = 1;
        uVar11 = (uint)param_4 >> 0x10;
        iVar14 = ShellButton::CheckRollOver(ulButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this,iVar14,iVar12,iVar13);
        iVar13 = 0;
        iVar12 = 1;
        iVar14 = ShellButton::CheckRollOver(okButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this_00,iVar14,iVar12,iVar13);
        iVar13 = 0;
        iVar12 = 1;
        iVar14 = ShellButton::CheckRollOver(cancelButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this_01,iVar14,iVar12,iVar13);
        local_14c = slotArray;
        do {
          iVar13 = 0;
          iVar12 = 1;
          iVar14 = ShellButton::CheckRollOver(*local_14c,uVar10,uVar11);
          ShellButton::SetButtonMode(this_02,iVar14,iVar12,iVar13);
          local_14c = local_14c + 1;
        } while ((int)local_14c < 0xc8fc2c);
        return 0;
      }
      if (param_2 == 0x201) {
        uVar10 = param_4 & 0xffff;
        iVar14 = ShellButton::CheckRollOver(ulButton,uVar10,(uint)param_4 >> 0x10);
        pSVar2 = okButton;
        if (((iVar14 == 0) &&
            (iVar14 = ShellButton::CheckRollOver(okButton,uVar10,extraout_EDX_01),
            pSVar1 = cancelButton, pSVar5 = pSVar2, iVar14 == 0)) &&
           (iVar14 = ShellButton::CheckRollOver(cancelButton,uVar10,extraout_EDX_02),
           pSVar5 = pSVar1, iVar14 == 0)) {
          iVar12 = 0;
          iVar14 = extraout_EDX_03;
          while (iVar14 = ShellButton::CheckRollOver(slotArray[iVar12],uVar10,iVar14), iVar14 == 0)
          {
            iVar12 = iVar12 + 1;
            iVar14 = extraout_EDX_04;
            if (9 < iVar12) {
              return 0;
            }
          }
          pSVar5 = slotArray[iVar12];
        }
        ShellButton::SetButtonMode(pSVar5,2,1,0);
        return 0;
      }
      if (param_2 != 0x202) {
        return 0;
      }
      uVar10 = param_4 & 0xffff;
      uVar11 = (uint)param_4 >> 0x10;
      iVar14 = ShellButton::CheckRollOver(ulButton,uVar10,uVar11);
      if (iVar14 != 0) {
        Shell_EndDialog(param_1,0);
        return 0;
      }
      iVar14 = ShellButton::CheckRollOver(okButton,uVar10,uVar11);
      pSVar5 = extraout_EDX;
      if (iVar14 == 0) {
        iVar14 = ShellButton::CheckRollOver(cancelButton,uVar10,uVar11);
        if (iVar14 == 0) {
          iVar14 = 0;
          do {
            iVar14 = ShellButton::CheckRollOver(slotArray[iVar14],uVar10,uVar11);
            if (iVar14 != 0) {
              currentSlot = slotArray[extraout_EDX_00];
              nCurrentSlotIndex = extraout_EDX_00 + 1;
              TextLabel::ShowLabelText(message,1);
              iVar14 = 1;
              pHVar3 = GetDlgItem((HWND)param_1,0x427);
              ShowWindow(pHVar3,iVar14);
              iVar14 = GetSaveDesc(nCurrentSlotIndex,currentSlot);
              if (iVar14 != 0) {
                lpString = currentSlot->labelText;
                pHVar3 = GetDlgItem((HWND)param_1,0x427);
                SetWindowTextA(pHVar3,lpString);
                nDisplayEdit = 1;
              }
              ShellButton::ShowButton(okButton,1);
              ShellButton::ShowButton(cancelButton,1);
              return 0;
            }
            iVar14 = extraout_EDX_00 + 1;
          } while (iVar14 < 10);
          return 0;
        }
        nOverWrite = 0;
        TextLabel::HideLabelText(message,1);
        pTVar6 = message;
        TextLabel::SetLabelText(message,"Enter the game description");
        read_text_label("save_load","game_desc",pTVar6->textData);
        ShellButton::HideButton(okButton,0);
        ShellButton::HideButton(cancelButton,0);
        SetDlgItemTextA((HWND)param_1,0x427,"");
        iVar14 = 0;
        pHVar3 = GetDlgItem((HWND)param_1,0x427);
        ShowWindow(pHVar3,iVar14);
        goto LAB_005770b5;
      }
      goto joined_r0x005775ac;
    }
  }
  SetTextColor((HDC)param_3,0xff00);
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_00577826:
  pvVar8 = GetStockObject(4);
  return (int)pvVar8;
}
