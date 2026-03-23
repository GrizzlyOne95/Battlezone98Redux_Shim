
void FUN_007800c0(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  char *local_14;
  undefined4 *local_10;
  char *local_c;
  
  local_14 = param_1;
  local_c = (char *)&DAT_02cc40c0;
  do {
    cVar1 = *local_14;
    *local_c = cVar1;
    local_14 = local_14 + 1;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  pcVar3 = strrchr((char *)&DAT_02cc40c0,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  local_10 = (undefined4 *)&DAT_02cc40bf;
  puVar2 = local_10;
  do {
    local_10 = puVar2;
    puVar2 = (undefined4 *)((int)local_10 + 1);
  } while (*(char *)((int)local_10 + 1) != '\0');
  *(undefined4 *)((int)local_10 + 1) = 0x6e72742e;
  *(undefined1 *)((int)local_10 + 5) = 0;
  return;
}

