/*
 * Entry: 0057406b
 * Name: GraphicOptionsDlgProc
 * Namespace: Global
 * Signature: int GraphicOptionsDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GraphicOptionsDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellButton *pSVar1;
  ShellButton *pSVar2;
  ShellBitmap *pSVar3;
  ShellButton *pSVar4;
  TextLabel *pTVar5;
  OptionBox *pOVar6;
  ShellScrollBar *pSVar7;
  HDC pHVar8;
  HGDIOBJ pvVar9;
  OptionBox *extraout_ECX;
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
  int extraout_EDX_12;
  int extraout_EDX_13;
  int extraout_EDX_14;
  int extraout_EDX_15;
  ShellButton *extraout_EDX_16;
  ShellButton *this;
  ShellButton *this_00;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *this_03;
  ShellButton *this_04;
  ShellButton *this_05;
  ShellButton *this_06;
  ShellButton *extraout_EDX_17;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  HWND__ *local_48;
  tagPAINTSTRUCT local_44;
  uint local_4;
  
  pSVar4 = scrResButton;
  local_4 = __security_cookie ^ (uint)&local_48;
  local_48 = param_1;
  if (param_2 < 0x137) {
    if (param_2 != 0x136) {
      if (param_2 != 2) {
        if (param_2 == 0xf) {
          pHVar8 = BeginPaint((HWND)param_1,&local_44);
          ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(scrResButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(lineskipButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(skyDetailButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(cockpitButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(hardwareButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(objDetailButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(shaDetailButton,(HDC__ *)pHVar8);
          ShellButton::UpdateButton(terDetailButton,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(scrResBox,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(lineskipBox,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(skyDetailBox,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(cockpitBox,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(hardwareBox,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(objDetailBox,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(shaDetailBox,(HDC__ *)pHVar8);
          OptionBox::UpdateOptionBox(terDetailBox,(HDC__ *)pHVar8);
          TextLabel::DrawLabelText(scrResLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(lineskipLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(skyDetailLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(cockpitLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(hardwareLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(objDetailLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(shaDetailLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(terDetailLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(monitorLabel,(HDC__ *)pHVar8,(char *)0x0,0);
          TextLabel::DrawLabelText(message,(HDC__ *)pHVar8,(char *)0x0,0);
          ShellScrollBar::UpdateScroll(brightScroll,(HDC__ *)pHVar8);
          EndPaint((HWND)param_1,&local_44);
          return 0;
        }
        if (param_2 != 0x14) {
          if (param_2 == 0x20) {
            set_cursor(0);
            SetWindowLongA((HWND)param_1,0,1);
          }
          else {
            if (param_2 != 0x110) {
              return 0;
            }
            init_option_box();
            init_screen_pos(param_1);
            init_bitmap_dc(param_1);
            pSVar3 = operator_new(0x20);
            if (pSVar3 == (ShellBitmap *)0x0) {
              backGround = (ShellBitmap *)0x0;
            }
            else {
              backGround = ShellBitmap::ShellBitmap(pSVar3,"bitmap\\goptions.bmp",0,0);
            }
            SetCurrentBackground(param_1,backGround);
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              ulButton = (ShellButton *)0x0;
            }
            else {
              ulButton = ShellButton::ShellButton
                                   (pSVar4,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1
                                    ,"BACK");
            }
            ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              hardwareLabel = (TextLabel *)0x0;
            }
            else {
              hardwareLabel =
                   TextLabel::TextLabel(pTVar5,local_48,"3D CARD",0x87,0x47,0x96,0x13,0x126);
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              scrResLabel = (TextLabel *)0x0;
            }
            else {
              scrResLabel = TextLabel::TextLabel
                                      (pTVar5,local_48,"SCREEN RESOLUTION",0x87,0x6f,0x96,0x13,0x126
                                      );
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              monitorLabel = (TextLabel *)0x0;
            }
            else {
              monitorLabel = TextLabel::TextLabel
                                       (pTVar5,local_48,"MONITOR BRIGHTNESS",0x87,0x96,0x96,0x13,
                                        0x126);
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              lineskipLabel = (TextLabel *)0x0;
            }
            else {
              lineskipLabel =
                   TextLabel::TextLabel(pTVar5,local_48,"LINE SKIP",0x87,0xbf,0x96,0x13,0x126);
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              skyDetailLabel = (TextLabel *)0x0;
            }
            else {
              skyDetailLabel =
                   TextLabel::TextLabel(pTVar5,local_48,"SKY DETAIL",0x87,0xe7,0x96,0x13,0x126);
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              terDetailLabel = (TextLabel *)0x0;
            }
            else {
              terDetailLabel =
                   TextLabel::TextLabel(pTVar5,local_48,"TERRAIN DETAIL",0x87,0x10e,0x96,0x13,0x126)
              ;
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              objDetailLabel = (TextLabel *)0x0;
            }
            else {
              objDetailLabel =
                   TextLabel::TextLabel(pTVar5,local_48,"OBJECT DETAIL",0x87,0x136,0x96,0x13,0x126);
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              cockpitLabel = (TextLabel *)0x0;
            }
            else {
              cockpitLabel = TextLabel::TextLabel
                                       (pTVar5,local_48,"COCKPIT DETAIL",0x87,0x15f,0x96,0x13,0x126)
              ;
            }
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              shaDetailLabel = (TextLabel *)0x0;
            }
            else {
              shaDetailLabel =
                   TextLabel::TextLabel(pTVar5,local_48,"SHADOW DETAIL",0x87,0x188,0x96,0x13,0x126);
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              hardwareButton = (ShellButton *)0x0;
            }
            else {
              hardwareButton =
                   ShellButton::ShellButton
                             (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0x47,0x39,0x11,0,
                              (char *)0x0);
            }
            ShellButton::SetSoundFile(hardwareButton,"cfigon.wav","cfigclk.wav");
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              scrResButton = (ShellButton *)0x0;
            }
            else {
              scrResButton = ShellButton::ShellButton
                                       (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0x6f,0x39,
                                        0x11,0,(char *)0x0);
            }
            ShellButton::SetSoundFile(scrResButton,"cfigon.wav","cfigclk.wav");
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              lineskipButton = (ShellButton *)0x0;
            }
            else {
              lineskipButton =
                   ShellButton::ShellButton
                             (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0xbf,0x39,0x11,0,
                              (char *)0x0);
            }
            ShellButton::SetSoundFile(lineskipButton,"cfigon.wav","cfigclk.wav");
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              skyDetailButton = (ShellButton *)0x0;
            }
            else {
              skyDetailButton =
                   ShellButton::ShellButton
                             (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0xe7,0x39,0x11,0,
                              (char *)0x0);
            }
            ShellButton::SetSoundFile(skyDetailButton,"cfigon.wav","cfigclk.wav");
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              terDetailButton = (ShellButton *)0x0;
            }
            else {
              terDetailButton =
                   ShellButton::ShellButton
                             (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0x10e,0x39,0x11,0,
                              (char *)0x0);
            }
            ShellButton::SetSoundFile(terDetailButton,"cfigon.wav","cfigclk.wav");
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              objDetailButton = (ShellButton *)0x0;
            }
            else {
              objDetailButton =
                   ShellButton::ShellButton
                             (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0x136,0x39,0x11,0,
                              (char *)0x0);
            }
            ShellButton::SetSoundFile(objDetailButton,"cfigon.wav","cfigclk.wav");
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              cockpitButton = (ShellButton *)0x0;
            }
            else {
              cockpitButton =
                   ShellButton::ShellButton
                             (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0x15f,0x39,0x11,0,
                              (char *)0x0);
            }
            ShellButton::SetSoundFile(cockpitButton,"cfigon.wav","cfigclk.wav");
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              shaDetailButton = (ShellButton *)0x0;
            }
            else {
              shaDetailButton =
                   ShellButton::ShellButton
                             (pSVar4,local_48,shell_hInstance,0,0x9f,0xa0,0x124,0x188,0x39,0x11,0,
                              (char *)0x0);
            }
            ShellButton::SetSoundFile(shaDetailButton,"cfigon.wav","cfigclk.wav");
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              pOVar6 = (OptionBox *)0x0;
            }
            else {
              pOVar6 = OptionBox::OptionBox(pOVar6,local_48,2,0x15f,0x47,0x46,0x13);
            }
            hardwareBox = pOVar6;
            OptionBox::LoadItemList(pOVar6,0,offOption,0);
            OptionBox::LoadItemList(pOVar6,1,onOption,1);
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              scrResBox = (OptionBox *)0x0;
            }
            else {
              scrResBox = OptionBox::OptionBox(pOVar6,local_48,0x10,0x15f,0x6f,0x46,0x13);
            }
            read_video_mode(scrResBox,0);
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              pOVar6 = (OptionBox *)0x0;
            }
            else {
              pOVar6 = OptionBox::OptionBox(pOVar6,local_48,2,0x15f,0xbf,0x46,0x13);
            }
            lineskipBox = pOVar6;
            OptionBox::LoadItemList(pOVar6,0,offOption,0);
            OptionBox::LoadItemList(pOVar6,1,onOption,1);
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              pOVar6 = (OptionBox *)0x0;
            }
            else {
              pOVar6 = OptionBox::OptionBox(pOVar6,local_48,4,0x15f,0xe7,0x46,0x13);
            }
            skyDetailBox = pOVar6;
            OptionBox::LoadItemList(pOVar6,0,flatOption,0);
            OptionBox::LoadItemList(pOVar6,1,smoothOption,1);
            OptionBox::LoadItemList(pOVar6,2,texturedOption,2);
            OptionBox::LoadItemList(pOVar6,3,fullOption,3);
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              pOVar6 = (OptionBox *)0x0;
            }
            else {
              pOVar6 = OptionBox::OptionBox(pOVar6,local_48,4,0x15f,0x10e,0x46,0x13);
            }
            terDetailBox = pOVar6;
            OptionBox::LoadItemList(pOVar6,0,flatOption,0);
            OptionBox::LoadItemList(pOVar6,1,smoothOption,1);
            OptionBox::LoadItemList(pOVar6,2,lowResOption,2);
            OptionBox::LoadItemList(pOVar6,3,hiResOption,3);
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              pOVar6 = (OptionBox *)0x0;
            }
            else {
              pOVar6 = OptionBox::OptionBox(pOVar6,local_48,4,0x15f,0x136,0x46,0x13);
            }
            objDetailBox = pOVar6;
            OptionBox::LoadItemList(pOVar6,0,flatOption,0);
            OptionBox::LoadItemList(pOVar6,1,mixedOption,1);
            OptionBox::LoadItemList(pOVar6,2,texturedOption,2);
            OptionBox::LoadItemList(pOVar6,3,hiResOption,3);
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              pOVar6 = (OptionBox *)0x0;
            }
            else {
              pOVar6 = OptionBox::OptionBox(pOVar6,local_48,3,0x15f,0x15f,0x46,0x13);
            }
            cockpitBox = pOVar6;
            OptionBox::LoadItemList(pOVar6,0,offOption,0);
            OptionBox::LoadItemList(pOVar6,1,solidOption,1);
            OptionBox::LoadItemList(pOVar6,2,texturedOption,2);
            pOVar6 = operator_new(0x32ec);
            if (pOVar6 == (OptionBox *)0x0) {
              pOVar6 = (OptionBox *)0x0;
            }
            else {
              pOVar6 = OptionBox::OptionBox(pOVar6,local_48,2,0x15f,0x188,0x46,0x13);
            }
            shaDetailBox = pOVar6;
            OptionBox::LoadItemList(pOVar6,0,offOption,0);
            OptionBox::LoadItemList(pOVar6,1,onOption,1);
            OptionBox::SetOptionBox(lineskipBox,(uint)(UserProfilePtr->graphicDetail).lineskip);
            OptionBox::SetOptionBox(skyDetailBox,(uint)(UserProfilePtr->graphicDetail).clouds);
            OptionBox::SetOptionBox(cockpitBox,(uint)(UserProfilePtr->graphicDetail).cockpit);
            OptionBox::SetOptionBox(hardwareBox,(uint)(UserProfilePtr->graphicDetail).hardware);
            OptionBox::SetOptionBox(objDetailBox,(uint)(UserProfilePtr->graphicDetail).objDetail);
            if (1 < (UserProfilePtr->graphicDetail).shadow) {
              (UserProfilePtr->graphicDetail).shadow = '\x01';
            }
            OptionBox::SetOptionBox(shaDetailBox,(uint)(UserProfilePtr->graphicDetail).shadow);
            OptionBox::SetOptionBox(terDetailBox,(uint)(UserProfilePtr->graphicDetail).terrain);
            if ((UserProfilePtr->graphicDetail).hardware == '\0') {
              lineskipButton->nButtonEnable = 1;
            }
            else {
              OptionBox::SetOptionBox(lineskipBox,0);
              (UserProfilePtr->graphicDetail).lineskip = '\0';
              lineskipButton->nButtonEnable = 0;
            }
            pSVar7 = operator_new(0x58);
            if (pSVar7 == (ShellScrollBar *)0x0) {
              brightScroll = (ShellScrollBar *)0x0;
            }
            else {
              brightScroll = ShellScrollBar::ShellScrollBar
                                       (pSVar7,local_48,shell_hInstance,0x10e,0x120,0x8b,0xd6,0x26,
                                        0x1b,0);
            }
            brightScroll->nCurrentPos = (uint)(UserProfilePtr->graphicDetail).brightness;
            pTVar5 = operator_new(0x128);
            if (pTVar5 == (TextLabel *)0x0) {
              message = (TextLabel *)0x0;
            }
            else {
              message = TextLabel::TextLabel
                                  (pTVar5,local_48,
                                   "Exit and Restart the game for changes to take effect.",0x9e,0x10
                                   ,0x14f,0x19,0);
            }
            TextLabel::HideLabelText(message,1);
            read_text_label("graphic_options","back",ulButton->labelText);
            read_text_label("graphic_options","hardware",hardwareLabel->textData);
            read_text_label("graphic_options","screen_resolution",scrResLabel->textData);
            read_text_label("graphic_options","monitor_brightness",monitorLabel->textData);
            read_text_label("graphic_options","line_skip",lineskipLabel->textData);
            read_text_label("graphic_options","sky_detail",skyDetailLabel->textData);
            read_text_label("graphic_options","terrain_detail",terDetailLabel->textData);
            read_text_label("graphic_options","object_detail",objDetailLabel->textData);
            read_text_label("graphic_options","cockpit_detail",cockpitLabel->textData);
            read_text_label("graphic_options","shadow_detail",shaDetailLabel->textData);
            read_text_label("graphic_options","message",message->textData);
          }
        }
        return 1;
      }
      CleanCurrentBackground();
      pSVar3 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar3);
        backGround = (ShellBitmap *)0x0;
      }
      pSVar4 = ulButton;
      if (ulButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(ulButton);
        operator_delete(pSVar4);
        ulButton = (ShellButton *)0x0;
      }
      pSVar7 = brightScroll;
      if (brightScroll != (ShellScrollBar *)0x0) {
        ShellScrollBar::~ShellScrollBar(brightScroll);
        operator_delete(pSVar7);
        brightScroll = (ShellScrollBar *)0x0;
      }
      pSVar4 = scrResButton;
      if (scrResButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(scrResButton);
        operator_delete(pSVar4);
        scrResButton = (ShellButton *)0x0;
      }
      pSVar4 = lineskipButton;
      if (lineskipButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(lineskipButton);
        operator_delete(pSVar4);
        lineskipButton = (ShellButton *)0x0;
      }
      pSVar4 = skyDetailButton;
      if (skyDetailButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(skyDetailButton);
        operator_delete(pSVar4);
        skyDetailButton = (ShellButton *)0x0;
      }
      pSVar4 = cockpitButton;
      if (cockpitButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(cockpitButton);
        operator_delete(pSVar4);
        cockpitButton = (ShellButton *)0x0;
      }
      pSVar4 = hardwareButton;
      if (hardwareButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(hardwareButton);
        operator_delete(pSVar4);
        hardwareButton = (ShellButton *)0x0;
      }
      pSVar4 = objDetailButton;
      if (objDetailButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(objDetailButton);
        operator_delete(pSVar4);
        objDetailButton = (ShellButton *)0x0;
      }
      pSVar4 = shaDetailButton;
      if (shaDetailButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(shaDetailButton);
        operator_delete(pSVar4);
        shaDetailButton = (ShellButton *)0x0;
      }
      pSVar4 = terDetailButton;
      if (terDetailButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(terDetailButton);
        operator_delete(pSVar4);
        terDetailButton = (ShellButton *)0x0;
      }
      pOVar6 = scrResBox;
      if (scrResBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(scrResBox);
        operator_delete(pOVar6);
        scrResBox = (OptionBox *)0x0;
      }
      pOVar6 = lineskipBox;
      if (lineskipBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(lineskipBox);
        operator_delete(pOVar6);
        lineskipBox = (OptionBox *)0x0;
      }
      pOVar6 = skyDetailBox;
      if (skyDetailBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(skyDetailBox);
        operator_delete(pOVar6);
        skyDetailBox = (OptionBox *)0x0;
      }
      pOVar6 = cockpitBox;
      if (cockpitBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(cockpitBox);
        operator_delete(pOVar6);
        cockpitBox = (OptionBox *)0x0;
      }
      pOVar6 = hardwareBox;
      if (hardwareBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(hardwareBox);
        operator_delete(pOVar6);
        hardwareBox = (OptionBox *)0x0;
      }
      pOVar6 = objDetailBox;
      if (objDetailBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(objDetailBox);
        operator_delete(pOVar6);
        objDetailBox = (OptionBox *)0x0;
      }
      pOVar6 = shaDetailBox;
      if (shaDetailBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(shaDetailBox);
        operator_delete(pOVar6);
        shaDetailBox = (OptionBox *)0x0;
      }
      pOVar6 = terDetailBox;
      if (terDetailBox != (OptionBox *)0x0) {
        OptionBox::~OptionBox(terDetailBox);
        operator_delete(pOVar6);
        terDetailBox = (OptionBox *)0x0;
      }
      pTVar5 = scrResLabel;
      if (scrResLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(scrResLabel);
        operator_delete(pTVar5);
        scrResLabel = (TextLabel *)0x0;
      }
      pTVar5 = monitorLabel;
      if (monitorLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(monitorLabel);
        operator_delete(pTVar5);
        monitorLabel = (TextLabel *)0x0;
      }
      pTVar5 = lineskipLabel;
      if (lineskipLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(lineskipLabel);
        operator_delete(pTVar5);
        lineskipLabel = (TextLabel *)0x0;
      }
      pTVar5 = skyDetailLabel;
      if (skyDetailLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(skyDetailLabel);
        operator_delete(pTVar5);
        skyDetailLabel = (TextLabel *)0x0;
      }
      pTVar5 = cockpitLabel;
      if (cockpitLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(cockpitLabel);
        operator_delete(pTVar5);
        cockpitLabel = (TextLabel *)0x0;
      }
      pTVar5 = hardwareLabel;
      if (hardwareLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(hardwareLabel);
        operator_delete(pTVar5);
        hardwareLabel = (TextLabel *)0x0;
      }
      pTVar5 = objDetailLabel;
      if (objDetailLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(objDetailLabel);
        operator_delete(pTVar5);
        objDetailLabel = (TextLabel *)0x0;
      }
      pTVar5 = shaDetailLabel;
      if (shaDetailLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(shaDetailLabel);
        operator_delete(pTVar5);
        shaDetailLabel = (TextLabel *)0x0;
      }
      pTVar5 = terDetailLabel;
      if (terDetailLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(terDetailLabel);
        operator_delete(pTVar5);
        terDetailLabel = (TextLabel *)0x0;
      }
      pTVar5 = message;
      if (message == (TextLabel *)0x0) {
        return 0;
      }
      TextLabel::~TextLabel(message);
      operator_delete(pTVar5);
      message = (TextLabel *)0x0;
      return 0;
    }
    iVar13 = 4;
  }
  else {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        uVar11 = param_4 & 0xffff;
        iVar14 = 0;
        iVar12 = 1;
        uVar10 = (uint)param_4 >> 0x10;
        iVar13 = ShellButton::CheckRollOver(scrResButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(lineskipButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this_00,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(skyDetailButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this_01,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(cockpitButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this_02,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(hardwareButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this_03,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(objDetailButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this_04,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(shaDetailButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this_05,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(terDetailButton,uVar11,uVar10);
        ShellButton::SetButtonMode(this_06,iVar13,iVar12,iVar14);
        iVar14 = 0;
        iVar12 = 1;
        iVar13 = ShellButton::CheckRollOver(ulButton,uVar11,uVar10);
        pSVar4 = extraout_EDX_17;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          uVar10 = param_4 & 0xffff;
          iVar13 = ShellButton::CheckRollOver(scrResButton,uVar10,(uint)param_4 >> 0x10);
          pSVar2 = lineskipButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar4,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(scrResBox);
            (UserProfilePtr->graphicDetail).resolution = (uchar)iVar13;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(lineskipButton,uVar10,extraout_EDX);
          pSVar4 = skyDetailButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar2,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(lineskipBox);
            (UserProfilePtr->graphicDetail).lineskip = (uchar)iVar13;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(skyDetailButton,uVar10,extraout_EDX_00);
          pSVar2 = cockpitButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar4,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(skyDetailBox);
            (UserProfilePtr->graphicDetail).clouds = (uchar)iVar13;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(cockpitButton,uVar10,extraout_EDX_01);
          pSVar4 = hardwareButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar2,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(cockpitBox);
            (UserProfilePtr->graphicDetail).cockpit = (uchar)iVar13;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(hardwareButton,uVar10,extraout_EDX_02);
          pSVar2 = objDetailButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar4,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(hardwareBox);
            (UserProfilePtr->graphicDetail).hardware = (uchar)iVar13;
            OptionBox::CleanItemList(scrResBox);
            read_video_mode(extraout_ECX,1);
            OptionBox::SetOptionBox(hardwareBox,(uint)(UserProfilePtr->graphicDetail).hardware);
            TextLabel::ShowLabelText(message,1);
            if ((UserProfilePtr->graphicDetail).hardware != '\0') {
              OptionBox::SetOptionBox(lineskipBox,0);
              (UserProfilePtr->graphicDetail).lineskip = '\0';
              lineskipButton->nButtonEnable = 0;
              return 0;
            }
            lineskipButton->nButtonEnable = 1;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(objDetailButton,uVar10,extraout_EDX_03);
          pSVar4 = shaDetailButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar2,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(objDetailBox);
            (UserProfilePtr->graphicDetail).objDetail = (uchar)iVar13;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(shaDetailButton,uVar10,extraout_EDX_04);
          pSVar2 = terDetailButton;
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar4,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(shaDetailBox);
            (UserProfilePtr->graphicDetail).shadow = (uchar)iVar13;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(terDetailButton,uVar10,extraout_EDX_05);
          if (iVar13 != 0) {
            ShellButton::SetButtonMode(pSVar2,1,0,0);
            iVar13 = OptionBox::ToggleOptionBox(terDetailBox);
            (UserProfilePtr->graphicDetail).terrain = (uchar)iVar13;
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(ulButton,uVar10,extraout_EDX_06);
          if (iVar13 != 0) {
            SaveUserProfile();
            Shell_EndDialog(param_1,1);
            return 0;
          }
          iVar13 = ShellScrollBar::CheckButtons(brightScroll,uVar10,extraout_EDX_07);
          if (iVar13 < 0) {
            return 0;
          }
          (UserProfilePtr->graphicDetail).brightness = (uchar)brightScroll->nCurrentPos;
          D3D_Flush_Texture_Cache();
          return 0;
        }
        uVar10 = param_4 & 0xffff;
        iVar13 = ShellButton::CheckRollOver(scrResButton,uVar10,(uint)param_4 >> 0x10);
        pSVar2 = lineskipButton;
        if (((((iVar13 == 0) &&
              (iVar13 = ShellButton::CheckRollOver(lineskipButton,uVar10,extraout_EDX_08),
              pSVar1 = skyDetailButton, pSVar4 = pSVar2, iVar13 == 0)) &&
             (iVar13 = ShellButton::CheckRollOver(skyDetailButton,uVar10,extraout_EDX_09),
             pSVar2 = cockpitButton, pSVar4 = pSVar1, iVar13 == 0)) &&
            ((iVar13 = ShellButton::CheckRollOver(cockpitButton,uVar10,extraout_EDX_10),
             pSVar1 = hardwareButton, pSVar4 = pSVar2, iVar13 == 0 &&
             (iVar13 = ShellButton::CheckRollOver(hardwareButton,uVar10,extraout_EDX_11),
             pSVar2 = objDetailButton, pSVar4 = pSVar1, iVar13 == 0)))) &&
           ((iVar13 = ShellButton::CheckRollOver(objDetailButton,uVar10,extraout_EDX_12),
            pSVar1 = shaDetailButton, pSVar4 = pSVar2, iVar13 == 0 &&
            ((iVar13 = ShellButton::CheckRollOver(shaDetailButton,uVar10,extraout_EDX_13),
             pSVar2 = terDetailButton, pSVar4 = pSVar1, iVar13 == 0 &&
             (iVar13 = ShellButton::CheckRollOver(terDetailButton,uVar10,extraout_EDX_14),
             pSVar4 = pSVar2, iVar13 == 0)))))) {
          iVar13 = ShellButton::CheckRollOver(ulButton,uVar10,extraout_EDX_15);
          if (iVar13 == 0) {
            return 0;
          }
          iVar14 = 0;
          iVar12 = 1;
          iVar13 = 2;
          pSVar4 = extraout_EDX_16;
        }
        else {
          iVar14 = 0;
          iVar12 = 1;
          iVar13 = 2;
        }
      }
      ShellButton::SetButtonMode(pSVar4,iVar13,iVar12,iVar14);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar13 = 5;
  }
  pvVar9 = GetStockObject(iVar13);
  return (int)pvVar9;
}
