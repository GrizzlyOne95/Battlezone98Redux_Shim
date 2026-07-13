/*
 * Entry: 00575eee
 * Name: PlayOptionsDlgProc
 * Namespace: Global
 * Signature: int PlayOptionsDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PlayOptionsDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellButton *pSVar1;
  ShellButton *pSVar2;
  ShellBitmap *pSVar3;
  TextLabel *pTVar4;
  ShellScrollBar *pSVar5;
  ShellButton *pSVar6;
  OptionBox *pOVar7;
  HDC pHVar8;
  HGDIOBJ pvVar9;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int extraout_EDX_05;
  int extraout_EDX_06;
  int extraout_EDX_07;
  int extraout_EDX_08;
  int extraout_EDX_09;
  int extraout_EDX_10;
  int extraout_EDX_11;
  ShellButton *extraout_EDX_12;
  ShellButton *this;
  ShellButton *this_00;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *this_03;
  ShellButton *this_04;
  ShellButton *extraout_EDX_13;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  tagPAINTSTRUCT local_44;
  uint local_4;
  
  pSVar6 = diffButton;
  local_4 = __security_cookie ^ (uint)&local_44;
  if (param_2 < 0x137) {
    if (param_2 != 0x136) {
      if (param_2 == 2) {
        CleanCurrentBackground();
        pSVar3 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar3);
          backGround = (ShellBitmap *)0x0;
        }
        pSVar6 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar6);
          ulButton = (ShellButton *)0x0;
        }
        pSVar6 = diffButton;
        if (diffButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(diffButton);
          operator_delete(pSVar6);
          diffButton = (ShellButton *)0x0;
        }
        pSVar6 = specialButton;
        if (specialButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(specialButton);
          operator_delete(pSVar6);
          specialButton = (ShellButton *)0x0;
        }
        pSVar6 = autoButton;
        if (autoButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(autoButton);
          operator_delete(pSVar6);
          autoButton = (ShellButton *)0x0;
        }
        pSVar6 = targetButton;
        if (targetButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(targetButton);
          operator_delete(pSVar6);
          targetButton = (ShellButton *)0x0;
        }
        pSVar6 = reverseButton;
        if (reverseButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(reverseButton);
          operator_delete(pSVar6);
          reverseButton = (ShellButton *)0x0;
        }
        pSVar6 = helpButton;
        if (helpButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(helpButton);
          operator_delete(pSVar6);
          helpButton = (ShellButton *)0x0;
        }
        pOVar7 = diffBox;
        if (diffBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(diffBox);
          operator_delete(pOVar7);
          diffBox = (OptionBox *)0x0;
        }
        pOVar7 = specialBox;
        if (specialBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(specialBox);
          operator_delete(pOVar7);
          specialBox = (OptionBox *)0x0;
        }
        pOVar7 = autoBox;
        if (autoBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(autoBox);
          operator_delete(pOVar7);
          autoBox = (OptionBox *)0x0;
        }
        pOVar7 = targetBox;
        if (targetBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(targetBox);
          operator_delete(pOVar7);
          targetBox = (OptionBox *)0x0;
        }
        pOVar7 = reverseBox;
        if (reverseBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(reverseBox);
          operator_delete(pOVar7);
          reverseBox = (OptionBox *)0x0;
        }
        pOVar7 = helpBox;
        if (helpBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(helpBox);
          operator_delete(pOVar7);
          helpBox = (OptionBox *)0x0;
        }
        pTVar4 = diffLabel;
        if (diffLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(diffLabel);
          operator_delete(pTVar4);
          diffLabel = (TextLabel *)0x0;
        }
        pTVar4 = specialLabel;
        if (specialLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(specialLabel);
          operator_delete(pTVar4);
          specialLabel = (TextLabel *)0x0;
        }
        pTVar4 = autoLabel;
        if (autoLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(autoLabel);
          operator_delete(pTVar4);
          autoLabel = (TextLabel *)0x0;
        }
        pTVar4 = targetLabel;
        if (targetLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(targetLabel);
          operator_delete(pTVar4);
          targetLabel = (TextLabel *)0x0;
        }
        pTVar4 = reverseLabel;
        if (reverseLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(reverseLabel);
          operator_delete(pTVar4);
          reverseLabel = (TextLabel *)0x0;
        }
        pTVar4 = mouseLabel;
        if (mouseLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(mouseLabel);
          operator_delete(pTVar4);
          mouseLabel = (TextLabel *)0x0;
        }
        pTVar4 = helpLabel;
        if (helpLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(helpLabel);
          operator_delete(pTVar4);
          helpLabel = (TextLabel *)0x0;
        }
        pSVar5 = mouseScroll;
        if (mouseScroll != (ShellScrollBar *)0x0) {
          ShellScrollBar::~ShellScrollBar(mouseScroll);
          operator_delete(pSVar5);
          mouseScroll = (ShellScrollBar *)0x0;
        }
      }
      else {
        if (param_2 != 0xf) {
          if (param_2 != 0x14) {
            if (param_2 != 0x20) {
              if (param_2 != 0x110) {
                return 0;
              }
              init_option_box();
              nCallMode = param_4;
              init_screen_pos(param_1);
              init_bitmap_dc(param_1);
              pSVar3 = operator_new(0x20);
              if (pSVar3 == (ShellBitmap *)0x0) {
                backGround = (ShellBitmap *)0x0;
              }
              else {
                backGround = ShellBitmap::ShellBitmap(pSVar3,"bitmap\\poptions.bmp",0,0);
              }
              SetCurrentBackground(param_1,backGround);
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                diffLabel = (TextLabel *)0x0;
              }
              else {
                diffLabel = TextLabel::TextLabel
                                      (pTVar4,param_1,"GAME DIFFICULTY",0x87,0x6f,0x96,0x13,0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                specialLabel = (TextLabel *)0x0;
              }
              else {
                specialLabel = TextLabel::TextLabel
                                         (pTVar4,param_1,"SPECIAL ITEM TRIGGER",0x87,0x96,0x96,0x13,
                                          0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                autoLabel = (TextLabel *)0x0;
              }
              else {
                autoLabel = TextLabel::TextLabel
                                      (pTVar4,param_1,"AUTOMATIC LEVELING",0x87,0xbf,0x96,0x13,0x126
                                      );
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                targetLabel = (TextLabel *)0x0;
              }
              else {
                targetLabel = TextLabel::TextLabel
                                        (pTVar4,param_1,"TARGET LEAD POSITION",0x87,0xe7,0x96,0x13,
                                         0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                reverseLabel = (TextLabel *)0x0;
              }
              else {
                reverseLabel = TextLabel::TextLabel
                                         (pTVar4,param_1,"REVERSE MOUSE (UP//DOWN)",0x87,0x10e,0x96,
                                          0x13,0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                mouseLabel = (TextLabel *)0x0;
              }
              else {
                mouseLabel = TextLabel::TextLabel
                                       (pTVar4,param_1,"MOUSE SENSITIVITY",0x87,0x136,0x96,0x13,
                                        0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                helpLabel = (TextLabel *)0x0;
              }
              else {
                helpLabel = TextLabel::TextLabel
                                      (pTVar4,param_1,"STRATEGY HELP",0x87,0x15f,0x96,0x13,0x126);
              }
              pSVar5 = operator_new(0x58);
              if (pSVar5 == (ShellScrollBar *)0x0) {
                pSVar5 = (ShellScrollBar *)0x0;
              }
              else {
                pSVar5 = ShellScrollBar::ShellScrollBar
                                   (pSVar5,param_1,shell_hInstance,0x10e,0x121,299,0xd6,0x26,0x1b,0)
                ;
              }
              pSVar5->nRange = 6;
              mouseScroll = pSVar5;
              pSVar5->nSectionSize = pSVar5->nLength / 6;
              pSVar5->nCurrentPos = (UserProfilePtr->config).mIndex;
              pSVar6 = operator_new(0x110);
              if (pSVar6 == (ShellButton *)0x0) {
                ulButton = (ShellButton *)0x0;
              }
              else {
                ulButton = ShellButton::ShellButton
                                     (pSVar6,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22
                                      ,1,"BACK");
              }
              ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
              pSVar6 = operator_new(0x110);
              if (pSVar6 == (ShellButton *)0x0) {
                diffButton = (ShellButton *)0x0;
              }
              else {
                diffButton = ShellButton::ShellButton
                                       (pSVar6,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0x6f,0x39,
                                        0x11,0,(char *)0x0);
              }
              ShellButton::SetSoundFile(diffButton,"cfigon.wav","cfigclk.wav");
              pSVar6 = operator_new(0x110);
              if (pSVar6 == (ShellButton *)0x0) {
                specialButton = (ShellButton *)0x0;
              }
              else {
                specialButton =
                     ShellButton::ShellButton
                               (pSVar6,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0x96,0x39,0x11,0,
                                (char *)0x0);
              }
              ShellButton::SetSoundFile(specialButton,"cfigon.wav","cfigclk.wav");
              pSVar6 = operator_new(0x110);
              if (pSVar6 == (ShellButton *)0x0) {
                autoButton = (ShellButton *)0x0;
              }
              else {
                autoButton = ShellButton::ShellButton
                                       (pSVar6,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0xbf,0x39,
                                        0x11,0,(char *)0x0);
              }
              ShellButton::SetSoundFile(autoButton,"cfigon.wav","cfigclk.wav");
              pSVar6 = operator_new(0x110);
              if (pSVar6 == (ShellButton *)0x0) {
                targetButton = (ShellButton *)0x0;
              }
              else {
                targetButton = ShellButton::ShellButton
                                         (pSVar6,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0xe7,0x39
                                          ,0x11,0,(char *)0x0);
              }
              ShellButton::SetSoundFile(targetButton,"cfigon.wav","cfigclk.wav");
              pSVar6 = operator_new(0x110);
              if (pSVar6 == (ShellButton *)0x0) {
                reverseButton = (ShellButton *)0x0;
              }
              else {
                reverseButton =
                     ShellButton::ShellButton
                               (pSVar6,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0x10e,0x39,0x11,0,
                                (char *)0x0);
              }
              ShellButton::SetSoundFile(reverseButton,"cfigon.wav","cfigclk.wav");
              pSVar6 = operator_new(0x110);
              if (pSVar6 == (ShellButton *)0x0) {
                helpButton = (ShellButton *)0x0;
              }
              else {
                helpButton = ShellButton::ShellButton
                                       (pSVar6,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0x15f,0x39,
                                        0x11,0,(char *)0x0);
              }
              ShellButton::SetSoundFile(helpButton,"cfigon.wav","cfigclk.wav");
              pOVar7 = operator_new(0x32ec);
              if (pOVar7 == (OptionBox *)0x0) {
                pOVar7 = (OptionBox *)0x0;
              }
              else {
                pOVar7 = OptionBox::OptionBox(pOVar7,param_1,5,0x15f,0x6f,0x46,0x13);
              }
              diffBox = pOVar7;
              OptionBox::LoadItemList(pOVar7,0,veryeasyOption,0);
              OptionBox::LoadItemList(pOVar7,1,easyOption,1);
              OptionBox::LoadItemList(pOVar7,2,medOption,2);
              OptionBox::LoadItemList(pOVar7,3,hardOption,3);
              OptionBox::LoadItemList(pOVar7,4,veryhardOption,4);
              pOVar7 = operator_new(0x32ec);
              if (pOVar7 == (OptionBox *)0x0) {
                specialBox = (OptionBox *)0x0;
              }
              else {
                specialBox = OptionBox::OptionBox(pOVar7,param_1,2,0x15f,0x96,0x46,0x13);
              }
              OptionBox::LoadItemList(specialBox,0,offOption,0);
              OptionBox::LoadItemList(specialBox,1,onOption,1);
              pOVar7 = operator_new(0x32ec);
              if (pOVar7 == (OptionBox *)0x0) {
                autoBox = (OptionBox *)0x0;
              }
              else {
                autoBox = OptionBox::OptionBox(pOVar7,param_1,2,0x15f,0xbf,0x46,0x13);
              }
              OptionBox::LoadItemList(autoBox,0,offOption,0);
              OptionBox::LoadItemList(autoBox,1,onOption,1);
              pOVar7 = operator_new(0x32ec);
              if (pOVar7 == (OptionBox *)0x0) {
                targetBox = (OptionBox *)0x0;
              }
              else {
                targetBox = OptionBox::OptionBox(pOVar7,param_1,2,0x15f,0xe7,0x46,0x13);
              }
              OptionBox::LoadItemList(targetBox,0,offOption,0);
              OptionBox::LoadItemList(targetBox,1,onOption,1);
              pOVar7 = operator_new(0x32ec);
              if (pOVar7 == (OptionBox *)0x0) {
                reverseBox = (OptionBox *)0x0;
              }
              else {
                reverseBox = OptionBox::OptionBox(pOVar7,param_1,2,0x15f,0x10e,0x46,0x13);
              }
              OptionBox::LoadItemList(reverseBox,0,offOption,0);
              OptionBox::LoadItemList(reverseBox,1,onOption,1);
              pOVar7 = operator_new(0x32ec);
              if (pOVar7 == (OptionBox *)0x0) {
                pOVar7 = (OptionBox *)0x0;
              }
              else {
                pOVar7 = OptionBox::OptionBox(pOVar7,param_1,2,0x15f,0x15f,0x46,0x13);
              }
              helpBox = pOVar7;
              OptionBox::LoadItemList(pOVar7,0,offOption,0);
              OptionBox::LoadItemList(pOVar7,1,onOption,1);
              OptionBox::SetOptionBox(diffBox,(UserProfilePtr->config).difficulty);
              OptionBox::SetOptionBox(specialBox,(uint)UserProfilePtr->playOption >> 10 & 1);
              OptionBox::SetOptionBox(autoBox,(uint)UserProfilePtr->playOption >> 4 & 1);
              OptionBox::SetOptionBox(targetBox,(uint)UserProfilePtr->playOption >> 5 & 1);
              OptionBox::SetOptionBox(reverseBox,(uint)UserProfilePtr->playOption >> 6 & 1);
              OptionBox::SetOptionBox(helpBox,(uint)UserProfilePtr->playOption >> 7 & 1);
              read_text_label("play_options","back",ulButton->labelText);
              read_text_label("play_options","game_difficulty",diffLabel->textData);
              read_text_label("play_options","special_item_trigger",specialLabel->textData);
              read_text_label("play_options","automatic_leveling",autoLabel->textData);
              read_text_label("play_options","target_lead_position",targetLabel->textData);
              read_text_label("play_options","reverse_mouse",reverseLabel->textData);
              read_text_label("play_options","mouse_sensitivity",mouseLabel->textData);
              read_text_label("play_options","strategy_help",helpLabel->textData);
              return 1;
            }
            set_cursor(0);
            SetWindowLongA((HWND)param_1,0,1);
          }
          return 1;
        }
        pHVar8 = BeginPaint((HWND)param_1,&local_44);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(diffButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(specialButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(autoButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(targetButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(reverseButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(helpButton,(HDC__ *)pHVar8);
        OptionBox::UpdateOptionBox(diffBox,(HDC__ *)pHVar8);
        OptionBox::UpdateOptionBox(specialBox,(HDC__ *)pHVar8);
        OptionBox::UpdateOptionBox(autoBox,(HDC__ *)pHVar8);
        OptionBox::UpdateOptionBox(targetBox,(HDC__ *)pHVar8);
        OptionBox::UpdateOptionBox(reverseBox,(HDC__ *)pHVar8);
        ShellScrollBar::UpdateScroll(mouseScroll,(HDC__ *)pHVar8);
        OptionBox::UpdateOptionBox(helpBox,(HDC__ *)pHVar8);
        TextLabel::DrawLabelText(diffLabel,(HDC__ *)pHVar8,(char *)0x0,0);
        TextLabel::DrawLabelText(specialLabel,(HDC__ *)pHVar8,(char *)0x0,0);
        TextLabel::DrawLabelText(autoLabel,(HDC__ *)pHVar8,(char *)0x0,0);
        TextLabel::DrawLabelText(targetLabel,(HDC__ *)pHVar8,(char *)0x0,0);
        TextLabel::DrawLabelText(reverseLabel,(HDC__ *)pHVar8,(char *)0x0,0);
        TextLabel::DrawLabelText(mouseLabel,(HDC__ *)pHVar8,(char *)0x0,0);
        TextLabel::DrawLabelText(helpLabel,(HDC__ *)pHVar8,(char *)0x0,0);
        EndPaint((HWND)param_1,&local_44);
      }
      return 0;
    }
    iVar13 = 4;
  }
  else {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        uVar10 = param_4 & 0xffff;
        iVar14 = 0;
        iVar12 = 1;
        uVar11 = (uint)param_4 >> 0x10;
        iVar13 = ShellButton::CheckRollOver(diffButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(specialButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this_00,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(autoButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this_01,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(targetButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this_02,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(reverseButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this_03,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(helpButton,uVar10,uVar11);
        ShellButton::SetButtonMode(this_04,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(ulButton,uVar10,uVar11);
        pSVar6 = extraout_EDX_13;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          uVar10 = param_4 & 0xffff;
          iVar13 = ShellButton::CheckRollOver(diffButton,uVar10,(uint)param_4 >> 0x10);
          pSVar1 = specialButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar6,1,0,0);
            difficultySetting = OptionBox::ToggleOptionBox(diffBox);
            (UserProfilePtr->config).difficulty = difficultySetting;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(specialButton,uVar10,extraout_EDX);
          pSVar6 = autoButton;
          if (iVar13 == 0) {
            iVar13 = ShellButton::CheckRollOver(autoButton,uVar10,extraout_EDX_00);
            pSVar1 = targetButton;
            if (iVar13 == 0) {
              iVar13 = ShellButton::CheckRollOver(targetButton,uVar10,extraout_EDX_01);
              pSVar6 = reverseButton;
              if (iVar13 == 0) {
                iVar13 = ShellButton::CheckRollOver(reverseButton,uVar10,extraout_EDX_02);
                pSVar1 = helpButton;
                if (iVar13 == 0) {
                  iVar13 = ShellButton::CheckRollOver(helpButton,uVar10,extraout_EDX_03);
                  if (iVar13 == 0) {
                    iVar13 = ShellButton::CheckRollOver(ulButton,uVar10,extraout_EDX_04);
                    if (iVar13 != 0) {
                      SaveUserProfile();
                      Shell_EndDialog(param_1,1);
                      return 0;
                    }
                    iVar13 = ShellScrollBar::CheckButtons(mouseScroll,uVar10,extraout_EDX_05);
                    if (iVar13 < 0) {
                      return 0;
                    }
                    (UserProfilePtr->config).mIndex = mouseScroll->nCurrentPos;
                    return 0;
                  }
                  ShellButton::SetButtonMode(pSVar1,1,0,0);
                  UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x80;
                  pOVar7 = helpBox;
                }
                else {
                  ShellButton::SetButtonMode(pSVar6,1,0,0);
                  UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x40;
                  pOVar7 = reverseBox;
                }
              }
              else {
                ShellButton::SetButtonMode(pSVar1,1,0,0);
                UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x20;
                pOVar7 = targetBox;
              }
            }
            else {
              ShellButton::SetButtonMode(pSVar6,1,0,0);
              UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x10;
              pOVar7 = autoBox;
            }
          }
          else {
            ShellButton::SetButtonMode(pSVar1,1,0,0);
            UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x400;
            pOVar7 = specialBox;
          }
          OptionBox::ToggleOptionBox(pOVar7);
          return 0;
        }
        uVar10 = param_4 & 0xffff;
        iVar13 = ShellButton::CheckRollOver(diffButton,uVar10,(uint)param_4 >> 0x10);
        pSVar1 = specialButton;
        if ((((iVar13 == 0) &&
             (iVar13 = ShellButton::CheckRollOver(specialButton,uVar10,extraout_EDX_06),
             pSVar2 = autoButton, pSVar6 = pSVar1, iVar13 == 0)) &&
            (iVar13 = ShellButton::CheckRollOver(autoButton,uVar10,extraout_EDX_07),
            pSVar1 = targetButton, pSVar6 = pSVar2, iVar13 == 0)) &&
           (((iVar13 = ShellButton::CheckRollOver(targetButton,uVar10,extraout_EDX_08),
             pSVar2 = reverseButton, pSVar6 = pSVar1, iVar13 == 0 &&
             (iVar13 = ShellButton::CheckRollOver(reverseButton,uVar10,extraout_EDX_09),
             pSVar1 = helpButton, pSVar6 = pSVar2, iVar13 == 0)) &&
            (iVar13 = ShellButton::CheckRollOver(helpButton,uVar10,extraout_EDX_10), pSVar6 = pSVar1
            , iVar13 == 0)))) {
          iVar13 = ShellButton::CheckRollOver(ulButton,uVar10,extraout_EDX_11);
          if (iVar13 == 0) {
            return 0;
          }
          iVar14 = 0;
          iVar12 = 1;
          iVar13 = 2;
          pSVar6 = extraout_EDX_12;
        }
        else {
          iVar14 = 0;
          iVar12 = 1;
          iVar13 = 2;
        }
      }
      ShellButton::SetButtonMode(pSVar6,iVar13,iVar12,iVar14);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar13 = 5;
  }
  pvVar9 = GetStockObject(iVar13);
  return (int)pvVar9;
}
