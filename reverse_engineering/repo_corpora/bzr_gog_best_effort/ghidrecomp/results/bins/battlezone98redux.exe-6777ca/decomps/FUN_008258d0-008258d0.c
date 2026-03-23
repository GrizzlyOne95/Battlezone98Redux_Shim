
void FUN_008258d0(undefined4 param_1,int param_2,char *param_3)

{
  undefined4 *puVar1;
  char *pcVar2;
  undefined4 *local_4cc;
  char *local_4c4;
  undefined1 local_4c0 [951];
  undefined4 uStack_109;
  undefined1 local_104 [252];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  memset(local_4c0,0,0x3b8);
  *(undefined1 **)(param_2 + 4) = local_4c0;
  pcVar2 = strrchr(param_3,0x5c);
  local_4c4 = strrchr(param_3,0x2f);
  if (local_4c4 < pcVar2) {
    local_4c4 = pcVar2;
  }
  if (local_4c4 == (char *)0x0) {
    local_4c4 = param_3;
  }
  else {
    local_4c4 = local_4c4 + 1;
  }
  strncpy((char *)((int)&uStack_109 + 1),local_4c4,0x100);
  pcVar2 = strrchr((char *)((int)&uStack_109 + 1),0x2e);
  if (pcVar2 != (char *)0x0) {
    *pcVar2 = '\0';
  }
  puVar1 = &uStack_109;
  do {
    local_4cc = puVar1;
    puVar1 = (undefined4 *)((int)local_4cc + 1);
  } while (*(char *)((int)local_4cc + 1) != '\0');
  *(undefined4 *)((int)local_4cc + 1) = 0x6664762e;
  *(undefined1 *)((int)local_4cc + 5) = 0;
  FUN_00826780((int)&uStack_109 + 1,&DAT_008fe3b8,0xe,param_2);
  FUN_0083e885();
  return;
}

