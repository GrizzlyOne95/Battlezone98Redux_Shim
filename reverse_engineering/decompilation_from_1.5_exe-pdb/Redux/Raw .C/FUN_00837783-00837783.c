
byte FUN_00837783(char *param_1,int param_2)

{
  char *pcVar1;
  byte bVar2;
  
  pcVar1 = strchr(param_1,99);
  bVar2 = pcVar1 != (char *)0x0;
  pcVar1 = strchr(param_1,0x72);
  if (pcVar1 != (char *)0x0) {
    bVar2 = bVar2 | 2;
  }
  pcVar1 = strchr(param_1,0x6c);
  if (pcVar1 != (char *)0x0) {
    bVar2 = bVar2 | 4;
  }
  if (0 < param_2) {
    bVar2 = bVar2 | 8;
  }
  return bVar2;
}

