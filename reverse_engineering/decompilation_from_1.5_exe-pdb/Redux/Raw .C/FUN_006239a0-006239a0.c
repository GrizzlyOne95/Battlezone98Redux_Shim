
undefined4 FUN_006239a0(undefined4 param_1,char *param_2)

{
  param_2[0x58] = '\x04';
  param_2[0x59] = '\0';
  param_2[0x5a] = '\0';
  param_2[0x5b] = '\0';
  param_2[0x5c] = '\t';
  param_2[0x5d] = '\0';
  param_2[0x5e] = '\0';
  param_2[0x5f] = '\0';
  sprintf(param_2,"mouse");
  sprintf(param_2 + 0xc,"Mouse");
  sprintf(param_2 + 0x4c,"mouse");
  *(undefined ***)(param_2 + 0x60) = &PTR_s_Mouse_Horizontal_Position_008ec6a4;
  *(undefined ***)(param_2 + 100) = &PTR_s_HorizPos_008ec6d8;
  *(undefined ***)(param_2 + 0x68) = &PTR_s_Left_button_008ec27c;
  *(undefined ***)(param_2 + 0x6c) = &PTR_s_LeftBtn_008ec6b4;
  *(undefined **)(param_2 + 0x70) = &DAT_02a17474;
  return 0;
}

