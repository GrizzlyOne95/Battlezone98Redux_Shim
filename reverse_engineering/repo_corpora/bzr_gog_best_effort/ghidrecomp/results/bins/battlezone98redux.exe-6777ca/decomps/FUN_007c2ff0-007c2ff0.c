
void __thiscall FUN_007c2ff0(int param_1,char *param_2)

{
  char cVar1;
  char *local_10;
  char *local_c;
  
  local_10 = param_2;
  local_c = (char *)(param_1 + 0x16c);
  do {
    cVar1 = *local_10;
    *local_c = cVar1;
    local_10 = local_10 + 1;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  return;
}

