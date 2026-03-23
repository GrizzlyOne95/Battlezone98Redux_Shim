
byte * __thiscall
FUN_006ba120(byte *param_1,byte param_2,uint param_3,int param_4,char param_5,char param_6,
            char param_7,char param_8,char param_9)

{
  byte local_5;
  
  *param_1 = 0;
  param_1[1] = 0;
  if (param_5 != '\0') {
    *param_1 = *param_1 | 0x80;
  }
  if (param_7 != '\0') {
    *param_1 = *param_1 | 0x40;
  }
  if (param_8 != '\0') {
    *param_1 = *param_1 | 0x20;
  }
  if (param_9 != '\0') {
    *param_1 = *param_1 | 0x10;
  }
  *param_1 = *param_1 | param_2 & 0xf;
  if (param_6 != '\0') {
    param_1[1] = param_1[1] | 0x80;
  }
  if ((param_4 == 0) && (param_3 < 0x7e)) {
    local_5 = (byte)param_3;
  }
  else if ((param_4 == 0) && (param_3 < 0x10000)) {
    local_5 = 0x7e;
  }
  else {
    local_5 = 0x7f;
  }
  param_1[1] = param_1[1] | local_5;
  return param_1;
}

