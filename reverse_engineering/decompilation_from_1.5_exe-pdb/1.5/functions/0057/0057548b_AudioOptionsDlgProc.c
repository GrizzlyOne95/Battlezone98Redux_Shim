/*
 * Entry: 0057548b
 * Name: AudioOptionsDlgProc
 * Namespace: Global
 * Signature: int AudioOptionsDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl AudioOptionsDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellButton *pSVar1;
  ShellBitmap *pSVar2;
  ShellButton *pSVar3;
  TextLabel *pTVar4;
  OptionBox *pOVar5;
  ShellScrollBar *pSVar6;
  HDC pHVar7;
  HGDIOBJ pvVar8;
  ShellButton *this;
  ShellButton *this_00;
  int extraout_EDX;
  int extraout_EDX_00;
  ShellButton *extraout_EDX_01;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *extraout_EDX_02;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  tagPAINTSTRUCT local_44;
  uint local_4;
  
  pSVar3 = chanButton;
  local_4 = __security_cookie ^ (uint)&local_44;
  if (param_2 < 0x137) {
    if (param_2 != 0x136) {
      if (param_2 == 2) {
        CleanCurrentBackground();
        pSVar2 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar2);
          backGround = (ShellBitmap *)0x0;
        }
        pSVar3 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar3);
          ulButton = (ShellButton *)0x0;
        }
        pSVar3 = chanButton;
        if (chanButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(chanButton);
          operator_delete(pSVar3);
          chanButton = (ShellButton *)0x0;
        }
        pSVar3 = stereoButton;
        if (stereoButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(stereoButton);
          operator_delete(pSVar3);
          stereoButton = (ShellButton *)0x0;
        }
        pOVar5 = chanBox;
        if (chanBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(chanBox);
          operator_delete(pOVar5);
          chanBox = (OptionBox *)0x0;
        }
        pOVar5 = stereoBox;
        if (stereoBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(stereoBox);
          operator_delete(pOVar5);
          stereoBox = (OptionBox *)0x0;
        }
        pSVar6 = musicScroll;
        if (musicScroll != (ShellScrollBar *)0x0) {
          ShellScrollBar::~ShellScrollBar(musicScroll);
          operator_delete(pSVar6);
          musicScroll = (ShellScrollBar *)0x0;
        }
        pSVar6 = effectScroll;
        if (effectScroll != (ShellScrollBar *)0x0) {
          ShellScrollBar::~ShellScrollBar(effectScroll);
          operator_delete(pSVar6);
          effectScroll = (ShellScrollBar *)0x0;
        }
        pSVar6 = voiceScroll;
        if (voiceScroll != (ShellScrollBar *)0x0) {
          ShellScrollBar::~ShellScrollBar(voiceScroll);
          operator_delete(pSVar6);
          voiceScroll = (ShellScrollBar *)0x0;
        }
        pTVar4 = chanLabel;
        if (chanLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(chanLabel);
          operator_delete(pTVar4);
          chanLabel = (TextLabel *)0x0;
        }
        pTVar4 = stereoLabel;
        if (stereoLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(stereoLabel);
          operator_delete(pTVar4);
          stereoLabel = (TextLabel *)0x0;
        }
        pTVar4 = musicLabel;
        if (musicLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(musicLabel);
          operator_delete(pTVar4);
          musicLabel = (TextLabel *)0x0;
        }
        pTVar4 = voiceLabel;
        if (voiceLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(voiceLabel);
          operator_delete(pTVar4);
          voiceLabel = (TextLabel *)0x0;
        }
        pTVar4 = effectLabel;
        if (effectLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(effectLabel);
          operator_delete(pTVar4);
          effectLabel = (TextLabel *)0x0;
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
              init_screen_pos(param_1);
              init_bitmap_dc(param_1);
              pSVar2 = operator_new(0x20);
              if (pSVar2 == (ShellBitmap *)0x0) {
                backGround = (ShellBitmap *)0x0;
              }
              else {
                backGround = ShellBitmap::ShellBitmap(pSVar2,"bitmap\\aoptions.bmp",0,0);
              }
              SetCurrentBackground(param_1,backGround);
              pSVar3 = operator_new(0x110);
              if (pSVar3 == (ShellButton *)0x0) {
                ulButton = (ShellButton *)0x0;
              }
              else {
                ulButton = ShellButton::ShellButton
                                     (pSVar3,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22
                                      ,1,"BACK");
              }
              ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                musicLabel = (TextLabel *)0x0;
              }
              else {
                musicLabel = TextLabel::TextLabel
                                       (pTVar4,param_1,"MUSIC VOLUME",0x87,0x47,0x96,0x13,0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                effectLabel = (TextLabel *)0x0;
              }
              else {
                effectLabel = TextLabel::TextLabel
                                        (pTVar4,param_1,"EFFECTS VOLUME",0x87,0x6f,0x96,0x13,0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                voiceLabel = (TextLabel *)0x0;
              }
              else {
                voiceLabel = TextLabel::TextLabel
                                       (pTVar4,param_1,"VOICE VOLUME",0x87,0x96,0x96,0x13,0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                chanLabel = (TextLabel *)0x0;
              }
              else {
                chanLabel = TextLabel::TextLabel
                                      (pTVar4,param_1,"SOUND CHANNELS",0x87,0xbf,0x96,0x13,0x126);
              }
              pTVar4 = operator_new(0x128);
              if (pTVar4 == (TextLabel *)0x0) {
                stereoLabel = (TextLabel *)0x0;
              }
              else {
                stereoLabel = TextLabel::TextLabel
                                        (pTVar4,param_1,"STEREO SOUND",0x87,0xe7,0x96,0x13,0x126);
              }
              pSVar3 = operator_new(0x110);
              if (pSVar3 == (ShellButton *)0x0) {
                chanButton = (ShellButton *)0x0;
              }
              else {
                chanButton = ShellButton::ShellButton
                                       (pSVar3,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0xbf,0x39,
                                        0x11,0,(char *)0x0);
              }
              ShellButton::SetSoundFile(chanButton,"cfigon.wav","cfigclk.wav");
              pSVar3 = operator_new(0x110);
              if (pSVar3 == (ShellButton *)0x0) {
                stereoButton = (ShellButton *)0x0;
              }
              else {
                stereoButton = ShellButton::ShellButton
                                         (pSVar3,param_1,shell_hInstance,0,0x9f,0xa0,0x124,0xe7,0x39
                                          ,0x11,0,(char *)0x0);
              }
              ShellButton::SetSoundFile(stereoButton,"cfigon.wav","cfigclk.wav");
              pOVar5 = operator_new(0x32ec);
              if (pOVar5 == (OptionBox *)0x0) {
                pOVar5 = (OptionBox *)0x0;
              }
              else {
                pOVar5 = OptionBox::OptionBox(pOVar5,param_1,7,0x15f,0xbf,0x46,0x13);
              }
              chanBox = pOVar5;
              OptionBox::LoadItemList(pOVar5,0,"1",1);
              OptionBox::LoadItemList(pOVar5,1,"2",2);
              OptionBox::LoadItemList(pOVar5,2,"4",4);
              OptionBox::LoadItemList(pOVar5,3,"8",8);
              OptionBox::LoadItemList(pOVar5,4,"16",0x10);
              OptionBox::LoadItemList(pOVar5,5,"32",0x20);
              OptionBox::LoadItemList(pOVar5,6,"64",0x40);
              pOVar5 = operator_new(0x32ec);
              if (pOVar5 == (OptionBox *)0x0) {
                pOVar5 = (OptionBox *)0x0;
              }
              else {
                pOVar5 = OptionBox::OptionBox(pOVar5,param_1,2,0x15f,0xe7,0x46,0x13);
              }
              stereoBox = pOVar5;
              OptionBox::LoadItemList(pOVar5,0,offOption,0);
              OptionBox::LoadItemList(pOVar5,1,onOption,1);
              OptionBox::SetCurrentValue(chanBox,(uint)(UserProfilePtr->audioControl).channels);
              OptionBox::SetOptionBox(stereoBox,(uint)(UserProfilePtr->audioControl).stereo);
              pSVar6 = operator_new(0x58);
              if (pSVar6 == (ShellScrollBar *)0x0) {
                musicScroll = (ShellScrollBar *)0x0;
              }
              else {
                musicScroll = ShellScrollBar::ShellScrollBar
                                        (pSVar6,param_1,shell_hInstance,0x10e,0x120,0x3c,0xd6,0x26,
                                         0x1b,0);
              }
              musicScroll->nCurrentPos = (uint)(UserProfilePtr->audioControl).music;
              pSVar6 = operator_new(0x58);
              if (pSVar6 == (ShellScrollBar *)0x0) {
                pSVar6 = (ShellScrollBar *)0x0;
              }
              else {
                pSVar6 = ShellScrollBar::ShellScrollBar
                                   (pSVar6,param_1,shell_hInstance,0x10e,0x120,100,0xd6,0x26,0x1b,0)
                ;
              }
              effectScroll = pSVar6;
              pSVar6->nCurrentPos = (uint)(UserProfilePtr->audioControl).sfx;
              pSVar6->nSoundEnable = 0;
              pSVar6 = operator_new(0x58);
              if (pSVar6 == (ShellScrollBar *)0x0) {
                pSVar6 = (ShellScrollBar *)0x0;
              }
              else {
                pSVar6 = ShellScrollBar::ShellScrollBar
                                   (pSVar6,param_1,shell_hInstance,0x10e,0x120,0x8b,0xd6,0x26,0x1b,0
                                   );
              }
              voiceScroll = pSVar6;
              pSVar6->nCurrentPos = (uint)(UserProfilePtr->audioControl).voice;
              pSVar6->nSoundEnable = 0;
              read_text_label("audio_options","back",ulButton->labelText);
              read_text_label("audio_options","sound_channels",chanLabel->textData);
              read_text_label("audio_options","stereo_sound",stereoLabel->textData);
              read_text_label("audio_options","music_volume",musicLabel->textData);
              read_text_label("audio_options","effects_volume",effectLabel->textData);
              read_text_label("audio_options","voice_volume",voiceLabel->textData);
              return 1;
            }
            set_cursor(0);
            SetWindowLongA((HWND)param_1,0,1);
          }
          return 1;
        }
        pHVar7 = BeginPaint((HWND)param_1,&local_44);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(chanButton,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(stereoButton,(HDC__ *)pHVar7);
        OptionBox::UpdateOptionBox(chanBox,(HDC__ *)pHVar7);
        OptionBox::UpdateOptionBox(stereoBox,(HDC__ *)pHVar7);
        ShellScrollBar::UpdateScroll(musicScroll,(HDC__ *)pHVar7);
        ShellScrollBar::UpdateScroll(effectScroll,(HDC__ *)pHVar7);
        ShellScrollBar::UpdateScroll(voiceScroll,(HDC__ *)pHVar7);
        TextLabel::DrawLabelText(musicLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        TextLabel::DrawLabelText(effectLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        TextLabel::DrawLabelText(voiceLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        TextLabel::DrawLabelText(chanLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        TextLabel::DrawLabelText(stereoLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        EndPaint((HWND)param_1,&local_44);
      }
      return 0;
    }
    iVar12 = 4;
  }
  else {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        uVar9 = param_4 & 0xffff;
        iVar13 = 0;
        iVar11 = 1;
        uVar10 = (uint)param_4 >> 0x10;
        iVar12 = ShellButton::CheckRollOver(chanButton,uVar9,uVar10);
        ShellButton::SetButtonMode(this_01,iVar12,iVar11,iVar13);
        iVar13 = 0;
        iVar11 = 1;
        iVar12 = ShellButton::CheckRollOver(stereoButton,uVar9,uVar10);
        ShellButton::SetButtonMode(this_02,iVar12,iVar11,iVar13);
        iVar13 = 0;
        iVar11 = 1;
        iVar12 = ShellButton::CheckRollOver(ulButton,uVar9,uVar10);
        pSVar3 = extraout_EDX_02;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          uVar10 = param_4 & 0xffff;
          uVar9 = (uint)param_4 >> 0x10;
          iVar12 = ShellButton::CheckRollOver(chanButton,uVar10,uVar9);
          if (iVar12 != 0) {
            ShellButton::SetButtonMode(this,1,0,0);
            iVar12 = OptionBox::ToggleOptionBox(chanBox);
            (UserProfilePtr->audioControl).channels = (uchar)iVar12;
            SetGASMaxObjects((uint)(UserProfilePtr->audioControl).channels);
            return 0;
          }
          iVar12 = ShellButton::CheckRollOver(stereoButton,uVar10,uVar9);
          if (iVar12 != 0) {
            ShellButton::SetButtonMode(this_00,1,0,0);
            iVar12 = OptionBox::ToggleOptionBox(stereoBox);
            (UserProfilePtr->audioControl).stereo = (uchar)iVar12;
            return 0;
          }
          iVar12 = ShellButton::CheckRollOver(ulButton,uVar10,uVar9);
          if (iVar12 == 0) {
            iVar12 = ShellScrollBar::CheckButtons(musicScroll,uVar10,uVar9);
            if (-1 < iVar12) {
              (UserProfilePtr->audioControl).music = (uchar)musicScroll->nCurrentPos;
              SetGASMasterVolumes((uint)(UserProfilePtr->audioControl).music,
                                  (uint)(UserProfilePtr->audioControl).sfx,
                                  (uint)(UserProfilePtr->audioControl).voice);
              return 0;
            }
            iVar12 = ShellScrollBar::CheckButtons(effectScroll,uVar10,uVar9);
            if (iVar12 < 0) {
              iVar12 = ShellScrollBar::CheckButtons(voiceScroll,uVar10,uVar9);
              if (iVar12 < 0) {
                return 0;
              }
              (UserProfilePtr->audioControl).voice = (uchar)voiceScroll->nCurrentPos;
              SetGASMasterVolumes((uint)(UserProfilePtr->audioControl).music,
                                  (uint)(UserProfilePtr->audioControl).sfx,
                                  (uint)(UserProfilePtr->audioControl).voice);
              TestVoice((uint)(UserProfilePtr->audioControl).voice);
            }
            else {
              (UserProfilePtr->audioControl).sfx = (uchar)effectScroll->nCurrentPos;
              SetGASMasterVolumes((uint)(UserProfilePtr->audioControl).music,
                                  (uint)(UserProfilePtr->audioControl).sfx,
                                  (uint)(UserProfilePtr->audioControl).voice);
              TestSFX((uint)(UserProfilePtr->audioControl).sfx);
            }
            NextGAS(0);
            return 0;
          }
          SaveUserProfile();
          Shell_EndDialog(param_1,1);
          return 0;
        }
        uVar9 = param_4 & 0xffff;
        iVar12 = ShellButton::CheckRollOver(chanButton,uVar9,(uint)param_4 >> 0x10);
        pSVar1 = stereoButton;
        if ((iVar12 == 0) &&
           (iVar12 = ShellButton::CheckRollOver(stereoButton,uVar9,extraout_EDX), pSVar3 = pSVar1,
           iVar12 == 0)) {
          iVar12 = ShellButton::CheckRollOver(ulButton,uVar9,extraout_EDX_00);
          if (iVar12 == 0) {
            return 0;
          }
          iVar13 = 0;
          iVar11 = 1;
          iVar12 = 2;
          pSVar3 = extraout_EDX_01;
        }
        else {
          iVar13 = 0;
          iVar11 = 1;
          iVar12 = 2;
        }
      }
      ShellButton::SetButtonMode(pSVar3,iVar12,iVar11,iVar13);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar12 = 5;
  }
  pvVar8 = GetStockObject(iVar12);
  return (int)pvVar8;
}
