
undefined4 FUN_005b0820(undefined4 param_1,char *param_2)

{
  param_2[0x58] = '\0';
  param_2[0x59] = '\0';
  param_2[0x5a] = '\0';
  param_2[0x5b] = '\0';
  param_2[0x5c] = '\x03';
  param_2[0x5d] = '\0';
  param_2[0x5e] = '\0';
  param_2[0x5f] = '\0';
  sprintf(param_2,"program");
  sprintf(param_2 + 0xc,"Program");
  sprintf(param_2 + 0x4c,"program");
  *(undefined **)(param_2 + 0x60) = &DAT_009181b0;
  *(undefined **)(param_2 + 100) = &DAT_009181b4;
  *(undefined ***)(param_2 + 0x68) = &PTR_s_Control_Mode_Key_008e8fa0;
  *(undefined ***)(param_2 + 0x6c) = &PTR_s_ControlMode_008e8f90;
  param_2[0x70] = '\0';
  param_2[0x71] = '\0';
  param_2[0x72] = '\0';
  param_2[0x73] = '\0';
  return 0;
}

