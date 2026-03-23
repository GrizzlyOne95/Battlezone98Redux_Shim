
void FUN_0077d510(void)

{
  int iVar1;
  int local_8;
  
  local_8 = DAT_02cd9440;
  while (local_8 != 0) {
    iVar1 = *(int *)(local_8 + 0x7c);
    FUN_0062d200(local_8,"Terrain\\Terramap.c");
    local_8 = iVar1;
  }
  DAT_02cd9440 = 0;
  return;
}

