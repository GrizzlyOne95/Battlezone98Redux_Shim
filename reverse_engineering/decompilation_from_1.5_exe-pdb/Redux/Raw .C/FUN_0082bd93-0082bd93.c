
void FUN_0082bd93(undefined4 param_1,char *param_2,char *param_3,undefined4 param_4)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  undefined1 *local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined1 local_208 [512];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pcVar3 = param_3;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  local_210 = 0;
  local_214 = local_208;
  local_20c = param_1;
  pcVar2 = strstr(param_2,param_3);
  while (pcVar2 != (char *)0x0) {
    FUN_0082b81b(&local_214,param_2,(int)pcVar2 - (int)param_2);
    FUN_0082b858(&local_214,param_4);
    param_2 = pcVar2 + ((int)pcVar3 - (int)(param_3 + 1));
    pcVar2 = strstr(param_2,param_3);
  }
  FUN_0082b858(&local_214,param_2);
  FUN_0082c2cb(&local_214);
  FUN_0082d377(param_1,0xffffffff,0);
  FUN_0083e885();
  return;
}

