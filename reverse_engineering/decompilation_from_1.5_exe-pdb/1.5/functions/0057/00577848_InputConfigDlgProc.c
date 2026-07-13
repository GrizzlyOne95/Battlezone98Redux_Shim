/*
 * Entry: 00577848
 * Name: InputConfigDlgProc
 * Namespace: Global
 * Signature: int InputConfigDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl InputConfigDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  char *pcVar1;
  char *pcVar2;
  undefined4 uVar3;
  ShellButton *pSVar4;
  ShellButton *pSVar5;
  HDC pHVar6;
  KeyConfig *this;
  ShellBitmap *pSVar7;
  ShellButton *pSVar8;
  TextLabel *pTVar9;
  int iVar10;
  char *pcVar11;
  HGDIOBJ pvVar12;
  KeyConfig *extraout_ECX;
  ShellButton *this_00;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *this_03;
  ShellButton *this_04;
  ShellButton *this_05;
  ShellButton *this_06;
  ShellButton *this_07;
  ShellButton *this_08;
  ShellButton *this_09;
  ShellButton *this_10;
  ShellButton *this_11;
  KeyConfig *this_12;
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
  int extraout_EDX_16;
  int extraout_EDX_17;
  int extraout_EDX_18;
  int extraout_EDX_19;
  int extraout_EDX_20;
  int extraout_EDX_21;
  int extraout_EDX_22;
  int extraout_EDX_23;
  int extraout_EDX_24;
  int extraout_EDX_25;
  int extraout_EDX_26;
  ShellButton *extraout_EDX_27;
  ShellButton *this_13;
  ShellButton *this_14;
  ShellButton *this_15;
  ShellButton *this_16;
  ShellButton *this_17;
  ShellButton *this_18;
  ShellButton *this_19;
  ShellButton *this_20;
  ShellButton *this_21;
  ShellButton *this_22;
  ShellButton *this_23;
  ShellButton *this_24;
  ShellButton *this_25;
  ShellButton *this_26;
  ShellButton *extraout_EDX_28;
  uint uVar13;
  char *pcVar14;
  uint uVar15;
  char *pcVar16;
  int iVar17;
  int iVar18;
  HWND__ *local_68;
  tagPAINTSTRUCT local_64;
  char local_24 [32];
  uint local_4;
  
  pSVar8 = ulButton;
  local_4 = __security_cookie ^ (uint)&local_68;
  local_68 = param_1;
  if (param_2 < 0x111) {
    if (param_2 == 0x110) {
      init_screen_pos(param_1);
      init_bitmap_dc(param_1);
      this = operator_new(0xc994);
      if (this == (KeyConfig *)0x0) {
        myConfig = (KeyConfig *)0x0;
      }
      else {
        this->nKeyCount = 0;
        KeyConfig::set_defaults(this);
        myConfig = extraout_ECX;
      }
      pSVar7 = operator_new(0x20);
      if (pSVar7 == (ShellBitmap *)0x0) {
        backGround = (ShellBitmap *)0x0;
      }
      else {
        backGround = ShellBitmap::ShellBitmap(pSVar7,"bitmap\\coptions.bmp",0,0);
      }
      SetCurrentBackground(param_1,backGround);
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        ulButton = (ShellButton *)0x0;
      }
      else {
        ulButton = ShellButton::ShellButton
                             (pSVar8,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                              "BACK");
      }
      ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        lrButton = (ShellButton *)0x0;
      }
      else {
        lrButton = ShellButton::ShellButton
                             (pSVar8,param_1,shell_hInstance,0xc4,0xc3,0xc5,0x1b9,0x1bd,199,0x22,1,
                              "JOYSTICK");
      }
      ShellButton::SetLabelPos(lrButton,0x1fb,0x1c4,0x58,0x17);
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        turboButton = (ShellButton *)0x0;
      }
      else {
        turboButton = ShellButton::ShellButton
                                (pSVar8,param_1,shell_hInstance,0,0xf6,0xfc,0x103,0x18,0x76,0x5a,1,
                                 "Forward");
      }
      ShellButton::SetLabelPos(turboButton,0x10a,0x1f,0x6c,0x1e);
      ShellButton::SetSoundFile(turboButton,"cfigon.wav","cfigclk.wav");
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        turboBox = (TextLabel *)0x0;
      }
      else {
        turboBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x10a,0x3e,0x6c,0x19,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        forwardButton = (ShellButton *)0x0;
      }
      else {
        forwardButton =
             ShellButton::ShellButton
                       (pSVar8,param_1,shell_hInstance,0,0xeb,0xfa,0x6a,0x179,0x6f,0x46,1,"Slow");
      }
      ShellButton::SetSoundFile(forwardButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_00,0x71,0x199,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        forwardBox = (TextLabel *)0x0;
      }
      else {
        forwardBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x71,0x17c,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        backButton = (ShellButton *)0x0;
      }
      else {
        backButton = ShellButton::ShellButton
                               (pSVar8,param_1,shell_hInstance,0,0xed,0xec,0x103,0x180,0x76,0x5a,1,
                                "Back");
      }
      ShellButton::SetSoundFile(backButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_01,0x10a,0x1b5,0x6c,0x1e);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        backBox = (TextLabel *)0x0;
      }
      else {
        backBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x10a,0x19b,0x6c,0x19,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        sLeftButton = (ShellButton *)0x0;
      }
      else {
        sLeftButton = ShellButton::ShellButton
                                (pSVar8,param_1,shell_hInstance,0,0xf2,0xf1,0x1b,0xca,0x95,0x47,1,
                                 "Strafe Left");
      }
      ShellButton::SetSoundFile(sLeftButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_02,0x22,0xd1,0x56,0x1e);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        sLeftBox = (TextLabel *)0x0;
      }
      else {
        sLeftBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x22,0xf0,0x56,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        sRightButton = (ShellButton *)0x0;
      }
      else {
        sRightButton = ShellButton::ShellButton
                                 (pSVar8,param_1,shell_hInstance,0,0xf3,0xfb,0x1d0,0xca,0x95,0x47,1,
                                  "Strafe Right");
      }
      ShellButton::SetSoundFile(sRightButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_03,0x208,0xd1,0x56,0x1e);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        sRightBox = (TextLabel *)0x0;
      }
      else {
        sRightBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x208,0xf0,0x56,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        jumpButton = (ShellButton *)0x0;
      }
      else {
        jumpButton = ShellButton::ShellButton
                               (pSVar8,param_1,shell_hInstance,0,0xef,0xee,0x1a7,0x179,0x6f,0x46,1,
                                "Jump");
      }
      ShellButton::SetSoundFile(jumpButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_04,0x1a9,0x199,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        jumpBox = (TextLabel *)0x0;
      }
      else {
        jumpBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x1a9,0x17c,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        pUpButton = (ShellButton *)0x0;
      }
      else {
        pUpButton = ShellButton::ShellButton
                              (pSVar8,param_1,shell_hInstance,0,0xf5,0xf4,0x6a,0x20,0x6f,0x46,1,
                               "Pitch Up");
      }
      ShellButton::SetSoundFile(pUpButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_05,0x71,0x27,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        pUpBox = (TextLabel *)0x0;
      }
      else {
        pUpBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x71,0x47,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        pDownButton = (ShellButton *)0x0;
      }
      else {
        pDownButton = ShellButton::ShellButton
                                (pSVar8,param_1,shell_hInstance,0,0xf8,0xf7,0x1a7,0x20,0x6f,0x46,1,
                                 "Pitch Down");
      }
      ShellButton::SetSoundFile(pDownButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_06,0x1a9,0x27,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        pDownBox = (TextLabel *)0x0;
      }
      else {
        pDownBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x1a9,0x47,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        pLeftButton = (ShellButton *)0x0;
      }
      else {
        pLeftButton = ShellButton::ShellButton
                                (pSVar8,param_1,shell_hInstance,0,0xf5,0xf4,0x25,0x68,0x6f,0x46,1,
                                 "Turn Left");
      }
      ShellButton::SetSoundFile(pLeftButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_07,0x2c,0x6f,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        pLeftBox = (TextLabel *)0x0;
      }
      else {
        pLeftBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x2c,0x8f,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        pRightButton = (ShellButton *)0x0;
      }
      else {
        pRightButton = ShellButton::ShellButton
                                 (pSVar8,param_1,shell_hInstance,0,0xf8,0xf7,0x1ec,0x68,0x6f,0x46,1,
                                  "Turn Right");
      }
      ShellButton::SetSoundFile(pRightButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_08,0x1ee,0x6f,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        pRightBox = (TextLabel *)0x0;
      }
      else {
        pRightBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x1ee,0x8f,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        fireButton = (ShellButton *)0x0;
      }
      else {
        fireButton = ShellButton::ShellButton
                               (pSVar8,param_1,shell_hInstance,0,0xeb,0xfa,0x25,0x131,0x6f,0x46,1,
                                "Fire");
      }
      ShellButton::SetSoundFile(fireButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_09,0x2c,0x151,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        fireBox = (TextLabel *)0x0;
      }
      else {
        fireBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x2c,0x134,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        sWeaponButton = (ShellButton *)0x0;
      }
      else {
        sWeaponButton =
             ShellButton::ShellButton
                       (pSVar8,param_1,shell_hInstance,0,0xef,0xee,0x1ec,0x131,0x6f,0x46,1,
                        "Shift Weapon");
      }
      ShellButton::SetSoundFile(sWeaponButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_10,0x1ee,0x151,0x66,0x1f);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        sWeaponBox = (TextLabel *)0x0;
      }
      else {
        sWeaponBox = TextLabel::TextLabel(pTVar9,param_1,"NULL",0x1ee,0x134,0x66,0x1c,0);
      }
      pSVar8 = operator_new(0x110);
      if (pSVar8 == (ShellButton *)0x0) {
        defaultButton = (ShellButton *)0x0;
      }
      else {
        defaultButton =
             ShellButton::ShellButton
                       (pSVar8,param_1,shell_hInstance,0,0x105,0x106,0xee,4,0xa6,0xf,1,
                        "Default Settings");
      }
      ShellButton::SetSoundFile(defaultButton,"cfigon.wav","cfigclk.wav");
      ShellButton::SetLabelPos(this_11,0x11a,6,0x51,0xc);
      hInputConfig = param_1;
      bWaitForKey = 0;
      currentBox = (void *)0x0;
      messageOne = (void *)0x0;
      messageTwo = (void *)0x0;
      read_input_map_key("throttle_up",local_24);
      KeyConfig::set_key(myConfig,"throttle_up",local_24);
      TextLabel::SetLabelText(forwardBox,local_24);
      read_text_label("keyboard",local_24,forwardBox->textData);
      read_input_map_key("throttle_down",local_24);
      KeyConfig::set_key(myConfig,"throttle_down",local_24);
      TextLabel::SetLabelText(backBox,local_24);
      read_text_label("keyboard",local_24,backBox->textData);
      read_input_map_key("strafe_right",local_24);
      KeyConfig::set_key(myConfig,"strafe_right",local_24);
      TextLabel::SetLabelText(sRightBox,local_24);
      read_text_label("keyboard",local_24,sRightBox->textData);
      read_input_map_key("strafe_left",local_24);
      KeyConfig::set_key(myConfig,"strafe_left",local_24);
      TextLabel::SetLabelText(sLeftBox,local_24);
      read_text_label("keyboard",local_24,sLeftBox->textData);
      read_input_map_key("jump",local_24);
      KeyConfig::set_key(myConfig,"jump",local_24);
      TextLabel::SetLabelText(jumpBox,local_24);
      read_text_label("keyboard",local_24,jumpBox->textData);
      read_input_map_key("turbo",local_24);
      KeyConfig::set_key(myConfig,"turbo",local_24);
      TextLabel::SetLabelText(turboBox,local_24);
      read_text_label("keyboard",local_24,turboBox->textData);
      read_input_map_key("pitch_down",local_24);
      KeyConfig::set_key(myConfig,"pitch_down",local_24);
      TextLabel::SetLabelText(pUpBox,local_24);
      read_text_label("keyboard",local_24,pUpBox->textData);
      read_input_map_key("pitch_up",local_24);
      KeyConfig::set_key(myConfig,"pitch_up",local_24);
      TextLabel::SetLabelText(pDownBox,local_24);
      read_text_label("keyboard",local_24,pDownBox->textData);
      read_input_map_key("steer_right",local_24);
      KeyConfig::set_key(myConfig,"steer_right",local_24);
      TextLabel::SetLabelText(pRightBox,local_24);
      read_text_label("keyboard",local_24,pRightBox->textData);
      read_input_map_key("steer_left",local_24);
      KeyConfig::set_key(myConfig,"steer_left",local_24);
      TextLabel::SetLabelText(pLeftBox,local_24);
      read_text_label("keyboard",local_24,pLeftBox->textData);
      read_input_map_key("weapon_fire",local_24);
      KeyConfig::set_key(myConfig,"weapon_fire",local_24);
      TextLabel::SetLabelText(fireBox,local_24);
      read_text_label("keyboard",local_24,fireBox->textData);
      read_input_map_key("weapon_cycle",local_24);
      KeyConfig::set_key(myConfig,"weapon_cycle",local_24);
      TextLabel::SetLabelText(sWeaponBox,local_24);
      read_text_label("keyboard",local_24,sWeaponBox->textData);
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        message1 = (TextLabel *)0x0;
      }
      else {
        message1 = TextLabel::TextLabel
                             (pTVar9,local_68,"Hit the key you wish to set...",0xfa,0xd2,0x8c,0x1e,0
                             );
      }
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        message2 = (TextLabel *)0x0;
      }
      else {
        message2 = TextLabel::TextLabel
                             (pTVar9,local_68,"That key already set, choose another...",0xd2,0xf0,
                              0xf0,0x1e,0);
      }
      pTVar9 = operator_new(0x128);
      if (pTVar9 == (TextLabel *)0x0) {
        message3 = (TextLabel *)0x0;
      }
      else {
        message3 = TextLabel::TextLabel
                             (pTVar9,local_68,"Joystick not supported for Demo",0xfa,0x10e,0x8c,0x1e
                              ,0);
      }
      TextLabel::HideLabelText(message1,1);
      TextLabel::HideLabelText(message2,1);
      TextLabel::HideLabelText(message3,1);
      messageOne = message1;
      messageTwo = message2;
      read_text_label("input_config","back_exit",ulButton->labelText);
      read_text_label("input_config","slow",forwardButton->labelText);
      read_text_label("input_config","back",backButton->labelText);
      read_text_label("input_config","strafe_right",sRightButton->labelText);
      read_text_label("input_config","strafe_left",sLeftButton->labelText);
      read_text_label("input_config","forward",turboButton->labelText);
      read_text_label("input_config","jump",jumpButton->labelText);
      read_text_label("input_config","pitch_up",pUpButton->labelText);
      read_text_label("input_config","pitch_down",pDownButton->labelText);
      read_text_label("input_config","turn_right",pRightButton->labelText);
      read_text_label("input_config","turn_left",pLeftButton->labelText);
      read_text_label("input_config","fire",fireButton->labelText);
      read_text_label("input_config","shift_weapon",sWeaponButton->labelText);
      read_text_label("input_config","default_settings",defaultButton->labelText);
      read_text_label("input_config","message_one",message1->textData);
      read_text_label("input_config","message_two",message2->textData);
      read_text_label("input_config","message_three",message3->textData);
      SetFocus((HWND)local_68);
      return 0;
    }
    if (param_2 == 2) {
      messageOne = (void *)0x0;
      messageTwo = (void *)0x0;
      currentBox = (void *)0x0;
      CleanCurrentBackground();
      pSVar7 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar7);
        backGround = (ShellBitmap *)0x0;
      }
      pSVar8 = ulButton;
      if (ulButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(ulButton);
        operator_delete(pSVar8);
        ulButton = (ShellButton *)0x0;
      }
      pSVar8 = lrButton;
      if (lrButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(lrButton);
        operator_delete(pSVar8);
        lrButton = (ShellButton *)0x0;
      }
      pSVar8 = forwardButton;
      if (forwardButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(forwardButton);
        operator_delete(pSVar8);
        forwardButton = (ShellButton *)0x0;
      }
      pSVar8 = backButton;
      if (backButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(backButton);
        operator_delete(pSVar8);
        backButton = (ShellButton *)0x0;
      }
      pSVar8 = sLeftButton;
      if (sLeftButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(sLeftButton);
        operator_delete(pSVar8);
        sLeftButton = (ShellButton *)0x0;
      }
      pSVar8 = sRightButton;
      if (sRightButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(sRightButton);
        operator_delete(pSVar8);
        sRightButton = (ShellButton *)0x0;
      }
      pSVar8 = jumpButton;
      if (jumpButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(jumpButton);
        operator_delete(pSVar8);
        jumpButton = (ShellButton *)0x0;
      }
      pSVar8 = turboButton;
      if (turboButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(turboButton);
        operator_delete(pSVar8);
        turboButton = (ShellButton *)0x0;
      }
      pSVar8 = pUpButton;
      if (pUpButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(pUpButton);
        operator_delete(pSVar8);
        pUpButton = (ShellButton *)0x0;
      }
      pSVar8 = pDownButton;
      if (pDownButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(pDownButton);
        operator_delete(pSVar8);
        pDownButton = (ShellButton *)0x0;
      }
      pSVar8 = pLeftButton;
      if (pLeftButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(pLeftButton);
        operator_delete(pSVar8);
        pLeftButton = (ShellButton *)0x0;
      }
      pSVar8 = pRightButton;
      if (pRightButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(pRightButton);
        operator_delete(pSVar8);
        pRightButton = (ShellButton *)0x0;
      }
      pSVar8 = fireButton;
      if (fireButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(fireButton);
        operator_delete(pSVar8);
        fireButton = (ShellButton *)0x0;
      }
      pSVar8 = sWeaponButton;
      if (sWeaponButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(sWeaponButton);
        operator_delete(pSVar8);
        sWeaponButton = (ShellButton *)0x0;
      }
      pSVar8 = defaultButton;
      if (defaultButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(defaultButton);
        operator_delete(pSVar8);
        defaultButton = (ShellButton *)0x0;
      }
      pTVar9 = forwardBox;
      if (forwardBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(forwardBox);
        operator_delete(pTVar9);
        forwardBox = (TextLabel *)0x0;
      }
      pTVar9 = backBox;
      if (backBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(backBox);
        operator_delete(pTVar9);
        backBox = (TextLabel *)0x0;
      }
      pTVar9 = sLeftBox;
      if (sLeftBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(sLeftBox);
        operator_delete(pTVar9);
        sLeftBox = (TextLabel *)0x0;
      }
      pTVar9 = sRightBox;
      if (sRightBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(sRightBox);
        operator_delete(pTVar9);
        sRightBox = (TextLabel *)0x0;
      }
      pTVar9 = jumpBox;
      if (jumpBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(jumpBox);
        operator_delete(pTVar9);
        jumpBox = (TextLabel *)0x0;
      }
      pTVar9 = turboBox;
      if (turboBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(turboBox);
        operator_delete(pTVar9);
        turboBox = (TextLabel *)0x0;
      }
      pTVar9 = pUpBox;
      if (pUpBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(pUpBox);
        operator_delete(pTVar9);
        pUpBox = (TextLabel *)0x0;
      }
      pTVar9 = pDownBox;
      if (pDownBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(pDownBox);
        operator_delete(pTVar9);
        pDownBox = (TextLabel *)0x0;
      }
      pTVar9 = pLeftBox;
      if (pLeftBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(pLeftBox);
        operator_delete(pTVar9);
        pLeftBox = (TextLabel *)0x0;
      }
      pTVar9 = pRightBox;
      if (pRightBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(pRightBox);
        operator_delete(pTVar9);
        pRightBox = (TextLabel *)0x0;
      }
      pTVar9 = fireBox;
      if (fireBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(fireBox);
        operator_delete(pTVar9);
        fireBox = (TextLabel *)0x0;
      }
      pTVar9 = sWeaponBox;
      if (sWeaponBox != (TextLabel *)0x0) {
        TextLabel::~TextLabel(sWeaponBox);
        operator_delete(pTVar9);
        sWeaponBox = (TextLabel *)0x0;
      }
      pTVar9 = message1;
      if (message1 != (TextLabel *)0x0) {
        TextLabel::~TextLabel(message1);
        operator_delete(pTVar9);
        message1 = (TextLabel *)0x0;
      }
      pTVar9 = message2;
      if (message2 != (TextLabel *)0x0) {
        TextLabel::~TextLabel(message2);
        operator_delete(pTVar9);
        message2 = (TextLabel *)0x0;
      }
      pTVar9 = message3;
      if (message3 != (TextLabel *)0x0) {
        TextLabel::~TextLabel(message3);
        operator_delete(pTVar9);
        message3 = (TextLabel *)0x0;
      }
      if (myConfig != (KeyConfig *)0x0) {
        operator_delete(myConfig);
        myConfig = (KeyConfig *)0x0;
      }
      hInputConfig = (HWND__ *)0x0;
      return 0;
    }
    if (param_2 == 8) {
      bWaitForKey = 0;
      return 0;
    }
    if (param_2 == 0xf) {
      pHVar6 = BeginPaint((HWND)param_1,&local_64);
      ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(lrButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(defaultButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(forwardButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(backButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(sLeftButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(sRightButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(jumpButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(turboButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(pUpButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(pDownButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(pLeftButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(pRightButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(fireButton,(HDC__ *)pHVar6);
      ShellButton::UpdateButton(sWeaponButton,(HDC__ *)pHVar6);
      TextLabel::DrawLabelText(forwardBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(backBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(sLeftBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(sRightBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(jumpBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(turboBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(pUpBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(pDownBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(pLeftBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(pRightBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(sWeaponBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(fireBox,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(message1,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(message2,(HDC__ *)pHVar6,(char *)0x0,0);
      TextLabel::DrawLabelText(message3,(HDC__ *)pHVar6,(char *)0x0,0);
      EndPaint((HWND)param_1,&local_64);
    }
    else if (param_2 != 0x14) {
      if (param_2 != 0x20) {
        if (param_2 != 0x100) {
          return 0;
        }
        if (bWaitForKey == 0) {
          return 0;
        }
        nCurrentScanKey = param_4 >> 0x10 & 0xff;
        nCurrentScanKey = check_extended_codes(nCurrentScanKey,param_4);
        get_key_name_from_scan_code(nCurrentScanKey,keyNameBuffer);
        SetKeyInput(keyNameBuffer);
        return 0;
      }
      set_cursor(0);
      SetWindowLongA((HWND)param_1,0,1);
    }
    return 1;
  }
  if (param_2 == 0x136) {
    iVar10 = 4;
LAB_005797cc:
    pvVar12 = GetStockObject(iVar10);
    return (int)pvVar12;
  }
  if (param_2 == 0x138) {
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar10 = 5;
    goto LAB_005797cc;
  }
  if (param_2 == 0x200) {
    if (bWaitForKey != 0) {
      return 0;
    }
    uVar13 = param_4 & 0xffff;
    iVar18 = 0;
    iVar17 = 1;
    uVar15 = (uint)param_4 >> 0x10;
    iVar10 = ShellButton::CheckRollOver(defaultButton,uVar13,uVar15);
    ShellButton::SetButtonMode(this_13,iVar10,iVar17,iVar18);
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(forwardButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_14,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(forwardBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(backButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_15,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(backBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(sLeftButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_16,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(sLeftBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(sRightButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_17,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(sRightBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(jumpButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_18,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(jumpBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(turboButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_19,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(turboBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(pUpButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_20,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(pUpBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(pDownButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_21,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(pDownBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(pLeftButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_22,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(pLeftBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(pRightButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_23,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(pRightBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(fireButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_24,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(fireBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(sWeaponButton,uVar13,uVar15);
    iVar10 = ShellButton::SetButtonMode(this_25,iVar10,iVar17,iVar18);
    if (iVar10 != 0) {
      TextLabel::DrawLabelText(sWeaponBox,(char *)0x0,0);
    }
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(ulButton,uVar13,uVar15);
    ShellButton::SetButtonMode(this_26,iVar10,iVar17,iVar18);
    iVar18 = 0;
    iVar17 = 1;
    iVar10 = ShellButton::CheckRollOver(lrButton,uVar13,uVar15);
    pSVar8 = extraout_EDX_28;
LAB_005797a7:
    ShellButton::SetButtonMode(pSVar8,iVar10,iVar17,iVar18);
    return 0;
  }
  if (param_2 == 0x201) {
    if (bWaitForKey != 0) {
      return 0;
    }
    uVar13 = param_4 & 0xffff;
    iVar10 = ShellButton::CheckRollOver(ulButton,uVar13,(uint)param_4 >> 0x10);
    pSVar4 = lrButton;
    if (((((iVar10 == 0) &&
          (iVar10 = ShellButton::CheckRollOver(lrButton,uVar13,extraout_EDX_13),
          pSVar5 = forwardButton, pSVar8 = pSVar4, iVar10 == 0)) &&
         (iVar10 = ShellButton::CheckRollOver(forwardButton,uVar13,extraout_EDX_14),
         pSVar4 = backButton, pSVar8 = pSVar5, iVar10 == 0)) &&
        ((((iVar10 = ShellButton::CheckRollOver(backButton,uVar13,extraout_EDX_15),
           pSVar5 = sLeftButton, pSVar8 = pSVar4, iVar10 == 0 &&
           (iVar10 = ShellButton::CheckRollOver(sLeftButton,uVar13,extraout_EDX_16),
           pSVar4 = sRightButton, pSVar8 = pSVar5, iVar10 == 0)) &&
          ((iVar10 = ShellButton::CheckRollOver(sRightButton,uVar13,extraout_EDX_17),
           pSVar5 = jumpButton, pSVar8 = pSVar4, iVar10 == 0 &&
           ((iVar10 = ShellButton::CheckRollOver(jumpButton,uVar13,extraout_EDX_18),
            pSVar4 = turboButton, pSVar8 = pSVar5, iVar10 == 0 &&
            (iVar10 = ShellButton::CheckRollOver(turboButton,uVar13,extraout_EDX_19),
            pSVar5 = pUpButton, pSVar8 = pSVar4, iVar10 == 0)))))) &&
         (iVar10 = ShellButton::CheckRollOver(pUpButton,uVar13,extraout_EDX_20),
         pSVar4 = pDownButton, pSVar8 = pSVar5, iVar10 == 0)))) &&
       ((((iVar10 = ShellButton::CheckRollOver(pDownButton,uVar13,extraout_EDX_21),
          pSVar5 = pLeftButton, pSVar8 = pSVar4, iVar10 == 0 &&
          (iVar10 = ShellButton::CheckRollOver(pLeftButton,uVar13,extraout_EDX_22),
          pSVar4 = pRightButton, pSVar8 = pSVar5, iVar10 == 0)) &&
         (iVar10 = ShellButton::CheckRollOver(pRightButton,uVar13,extraout_EDX_23),
         pSVar5 = fireButton, pSVar8 = pSVar4, iVar10 == 0)) &&
        ((iVar10 = ShellButton::CheckRollOver(fireButton,uVar13,extraout_EDX_24),
         pSVar4 = sWeaponButton, pSVar8 = pSVar5, iVar10 == 0 &&
         (iVar10 = ShellButton::CheckRollOver(sWeaponButton,uVar13,extraout_EDX_25), pSVar8 = pSVar4
         , iVar10 == 0)))))) {
      iVar10 = ShellButton::CheckRollOver(defaultButton,uVar13,extraout_EDX_26);
      if (iVar10 == 0) {
        return 0;
      }
      iVar18 = 0;
      iVar17 = 1;
      iVar10 = 2;
      pSVar8 = extraout_EDX_27;
    }
    else {
      iVar18 = 0;
      iVar17 = 1;
      iVar10 = 2;
    }
    goto LAB_005797a7;
  }
  if (param_2 != 0x202) {
    return 0;
  }
  if (bWaitForKey != 0) {
    return 0;
  }
  uVar13 = param_4 & 0xffff;
  iVar10 = ShellButton::CheckRollOver(ulButton,uVar13,(uint)param_4 >> 0x10);
  if (iVar10 != 0) {
    SaveUserProfile();
    Shell_EndDialog(param_1,1);
    return 0;
  }
  iVar10 = ShellButton::CheckRollOver(lrButton,uVar13,extraout_EDX);
  if (iVar10 != 0) {
    ShowWindow((HWND)param_1,0);
    EnableWindow((HWND)param_1,0);
    do_joystick();
    SetCurrentBackground(param_1,backGround);
    Shell_EndDialog(param_1,1);
    return 0;
  }
  iVar10 = ShellButton::CheckRollOver(defaultButton,uVar13,extraout_EDX_00);
  if (iVar10 != 0) {
    KeyConfig::set_defaults(myConfig);
    KeyConfig::write_key(this_12,"throttle_up");
    KeyConfig::write_key(myConfig,"throttle_down");
    KeyConfig::write_key(myConfig,"strafe_left");
    KeyConfig::write_key(myConfig,"strafe_right");
    KeyConfig::write_key(myConfig,"jump");
    KeyConfig::write_key(myConfig,"turbo");
    KeyConfig::write_key(myConfig,"pitch_up");
    KeyConfig::write_key(myConfig,"pitch_down");
    KeyConfig::write_key(myConfig,"steer_left");
    KeyConfig::write_key(myConfig,"steer_right");
    KeyConfig::write_key(myConfig,"weapon_fire");
    KeyConfig::write_key(myConfig,"weapon_cycle");
    read_input_map_key("throttle_up",local_24);
    TextLabel::SetLabelText(forwardBox,local_24);
    read_text_label("keyboard",local_24,forwardBox->textData);
    read_input_map_key("throttle_down",local_24);
    TextLabel::SetLabelText(backBox,local_24);
    read_text_label("keyboard",local_24,backBox->textData);
    read_input_map_key("strafe_right",local_24);
    TextLabel::SetLabelText(sRightBox,local_24);
    read_text_label("keyboard",local_24,sRightBox->textData);
    read_input_map_key("strafe_left",local_24);
    TextLabel::SetLabelText(sLeftBox,local_24);
    read_text_label("keyboard",local_24,sLeftBox->textData);
    read_input_map_key("jump",local_24);
    TextLabel::SetLabelText(jumpBox,local_24);
    read_text_label("keyboard",local_24,jumpBox->textData);
    read_input_map_key("turbo",local_24);
    TextLabel::SetLabelText(turboBox,local_24);
    read_text_label("keyboard",local_24,turboBox->textData);
    read_input_map_key("pitch_down",local_24);
    TextLabel::SetLabelText(pUpBox,local_24);
    read_text_label("keyboard",local_24,pUpBox->textData);
    read_input_map_key("pitch_up",local_24);
    TextLabel::SetLabelText(pDownBox,local_24);
    read_text_label("keyboard",local_24,pDownBox->textData);
    read_input_map_key("steer_right",local_24);
    TextLabel::SetLabelText(pRightBox,local_24);
    read_text_label("keyboard",local_24,pRightBox->textData);
    read_input_map_key("steer_left",local_24);
    TextLabel::SetLabelText(pLeftBox,local_24);
    read_text_label("keyboard",local_24,pLeftBox->textData);
    read_input_map_key("weapon_fire",local_24);
    TextLabel::SetLabelText(fireBox,local_24);
    read_text_label("keyboard",local_24,fireBox->textData);
    read_input_map_key("weapon_cycle",local_24);
    TextLabel::SetLabelText(sWeaponBox,local_24);
    read_text_label("keyboard",local_24,sWeaponBox->textData);
    TextLabel::DrawLabelText(forwardBox,(char *)0x0,0);
    TextLabel::DrawLabelText(backBox,(char *)0x0,0);
    TextLabel::DrawLabelText(sLeftBox,(char *)0x0,0);
    TextLabel::DrawLabelText(sRightBox,(char *)0x0,0);
    TextLabel::DrawLabelText(jumpBox,(char *)0x0,0);
    TextLabel::DrawLabelText(turboBox,(char *)0x0,0);
    TextLabel::DrawLabelText(pUpBox,(char *)0x0,0);
    TextLabel::DrawLabelText(pDownBox,(char *)0x0,0);
    TextLabel::DrawLabelText(pLeftBox,(char *)0x0,0);
    TextLabel::DrawLabelText(pRightBox,(char *)0x0,0);
    TextLabel::DrawLabelText(sWeaponBox,(char *)0x0,0);
    TextLabel::DrawLabelText(fireBox,(char *)0x0,0);
    return 0;
  }
  iVar10 = ShellButton::CheckRollOver(forwardButton,uVar13,extraout_EDX_01);
  if (iVar10 != 0) {
    PromptKeyInput(&forwardBox);
    pcVar11 = "throttle_up";
LAB_0057937e:
    currentCommandName._0_4_ = *(undefined4 *)pcVar11;
    currentCommandName._4_4_ = *(undefined4 *)(pcVar11 + 4);
    currentCommandName._8_4_ = *(undefined4 *)(pcVar11 + 8);
    goto LAB_005793bb;
  }
  iVar10 = ShellButton::CheckRollOver(backButton,uVar13,extraout_EDX_02);
  if (iVar10 != 0) {
    PromptKeyInput(&backBox);
    pcVar11 = "throttle_down";
    builtin_strncpy(currentCommandName,"throttle",8);
    pcVar16 = currentCommandName + 8;
    pcVar14 = "_down";
LAB_005792a3:
    *(undefined4 *)pcVar16 = *(undefined4 *)pcVar14;
    *(undefined2 *)(pcVar16 + 4) = *(undefined2 *)(pcVar14 + 4);
    goto LAB_005793bb;
  }
  iVar10 = ShellButton::CheckRollOver(sLeftButton,uVar13,extraout_EDX_03);
  if (iVar10 != 0) {
    PromptKeyInput(&sLeftBox);
    pcVar11 = "strafe_left";
    goto LAB_0057937e;
  }
  iVar10 = ShellButton::CheckRollOver(sRightButton,uVar13,extraout_EDX_04);
  if (iVar10 == 0) {
    iVar10 = ShellButton::CheckRollOver(jumpButton,uVar13,extraout_EDX_05);
    if (iVar10 != 0) {
      PromptKeyInput(&jumpBox);
      pcVar11 = "jump";
      pcVar14 = "jump";
      pcVar16 = currentCommandName;
      goto LAB_005793b7;
    }
    iVar10 = ShellButton::CheckRollOver(turboButton,uVar13,extraout_EDX_06);
    if (iVar10 != 0) {
      PromptKeyInput(&turboBox);
      pcVar11 = "turbo";
      pcVar14 = "turbo";
      pcVar16 = currentCommandName;
      goto LAB_005792a3;
    }
    iVar10 = ShellButton::CheckRollOver(pUpButton,uVar13,extraout_EDX_07);
    if (iVar10 != 0) {
      PromptKeyInput(&pUpBox);
      uVar3 = currentCommandName._8_4_;
      builtin_strncpy(currentCommandName,"pitch_down",0xb);
      currentCommandName[0xb] = SUB41(uVar3,3);
      pcVar11 = "pitch_down";
      goto LAB_005793bb;
    }
    iVar10 = ShellButton::CheckRollOver(pDownButton,uVar13,extraout_EDX_08);
    if (iVar10 != 0) {
      PromptKeyInput(&pDownBox);
      builtin_strncpy(currentCommandName,"pitch_up",8);
      currentCommandName._8_4_ = currentCommandName._8_4_ & 0xffffff00;
      pcVar11 = "pitch_up";
      goto LAB_005793bb;
    }
    iVar10 = ShellButton::CheckRollOver(pLeftButton,uVar13,extraout_EDX_09);
    if (iVar10 == 0) {
      iVar10 = ShellButton::CheckRollOver(pRightButton,uVar13,extraout_EDX_10);
      if (iVar10 == 0) {
        iVar10 = ShellButton::CheckRollOver(fireButton,uVar13,extraout_EDX_11);
        if (iVar10 == 0) {
          iVar10 = ShellButton::CheckRollOver(sWeaponButton,uVar13,extraout_EDX_12);
          if (iVar10 == 0) {
            return 0;
          }
          PromptKeyInput(&sWeaponBox);
          pcVar11 = "weapon_cycle";
          goto LAB_005793ae;
        }
        PromptKeyInput(&fireBox);
        pcVar11 = "weapon_fire";
      }
      else {
        PromptKeyInput(&pRightBox);
        pcVar11 = "steer_right";
      }
      goto LAB_0057937e;
    }
    PromptKeyInput(&pLeftBox);
    uVar3 = currentCommandName._8_4_;
    pcVar11 = "steer_left";
    builtin_strncpy(currentCommandName,"steer_left",10);
    pcVar2 = currentCommandName + 10;
    pcVar1 = "";
    currentCommandName._10_2_ = SUB42(uVar3,2);
  }
  else {
    PromptKeyInput(&sRightBox);
    pcVar11 = "strafe_right";
LAB_005793ae:
    currentCommandName._0_4_ = *(undefined4 *)pcVar11;
    pcVar16 = currentCommandName + 8;
    pcVar14 = pcVar11 + 8;
    currentCommandName._4_4_ = *(undefined4 *)(pcVar11 + 4);
LAB_005793b7:
    pcVar2 = pcVar16 + 4;
    pcVar1 = pcVar14 + 4;
    *(undefined4 *)pcVar16 = *(undefined4 *)pcVar14;
  }
  *pcVar2 = *pcVar1;
LAB_005793bb:
  KeyConfig::clear_key(myConfig,pcVar11);
  bWaitForKey = 1;
  return 0;
}
