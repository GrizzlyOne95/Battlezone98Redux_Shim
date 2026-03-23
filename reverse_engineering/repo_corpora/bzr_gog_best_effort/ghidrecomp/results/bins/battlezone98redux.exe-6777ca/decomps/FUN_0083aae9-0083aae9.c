
void FUN_0083aae9(undefined4 param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined1 local_28c [16];
  int local_27c;
  undefined4 local_250;
  int local_244 [143];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_250 = param_3;
  pcVar3 = param_4;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar2 = FUN_008309f4(param_1,param_4,(int)pcVar3 - (int)(param_4 + 1));
  FUN_00839037(param_1,local_28c,param_2,uVar2);
  FUN_0083abfa(local_28c,local_244);
  *(undefined1 *)(local_244[0] + 0x4a) = 2;
  FUN_00838ffd(local_28c);
  FUN_00839bcd(local_28c);
  if (local_27c != 0x11f) {
    FUN_0083a05e(local_28c,0x11f);
  }
  FUN_00839c1c(local_28c);
  FUN_0083e885();
  return;
}

