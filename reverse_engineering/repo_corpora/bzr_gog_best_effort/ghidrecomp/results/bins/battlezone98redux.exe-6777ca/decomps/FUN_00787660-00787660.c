
void FUN_00787660(char *param_1,char *param_2,char *param_3,int param_4)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char *local_140;
  int local_13c;
  char *local_138;
  char *local_134;
  char *local_130;
  char *local_12c;
  char *local_128;
  char *local_124;
  char *local_120;
  char *local_110;
  char local_109;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_124 = param_1;
  do {
    cVar1 = *local_124;
    local_124 = local_124 + 1;
  } while (cVar1 != '\0');
  if ((int)local_124 - (int)(param_1 + 1) < 0xff) {
    local_128 = param_2;
    do {
      cVar1 = *local_128;
      local_128 = local_128 + 1;
    } while (cVar1 != '\0');
    if ((int)local_128 - (int)(param_2 + 1) < 0xff) {
      local_108[0] = '[';
      local_108[1] = '\0';
      local_120 = param_1;
      do {
        cVar1 = *local_120;
        local_120 = local_120 + 1;
      } while (cVar1 != '\0');
      local_12c = &local_109;
      do {
        pcVar2 = local_12c + 1;
        local_12c = local_12c + 1;
      } while (*pcVar2 != '\0');
      pcVar2 = param_1;
      for (uVar3 = (uint)((int)local_120 - (int)param_1) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)local_12c = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        local_12c = local_12c + 4;
      }
      for (uVar3 = (int)local_120 - (int)param_1 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *local_12c = *pcVar2;
        pcVar2 = pcVar2 + 1;
        local_12c = local_12c + 1;
      }
      local_134 = &local_109;
      do {
        pcVar2 = local_134 + 1;
        local_134 = local_134 + 1;
      } while (*pcVar2 != '\0');
      local_134[0] = ']';
      local_134[1] = '\0';
      _strupr(local_108);
      pcVar2 = strstr((char *)DAT_009454d4,local_108);
      if ((pcVar2 != (char *)0x0) &&
         (pcVar2 = pcVar2 + ((int)local_124 - (int)(param_1 + 1)) + 2,
         pcVar2 < (char *)(DAT_009454d4 + DAT_009454d0))) {
        local_140 = strstr(pcVar2,"[");
        if (local_140 == (char *)0x0) {
          local_140 = (char *)(DAT_009454d4 + DAT_009454d0);
        }
        local_138 = param_2;
        local_130 = local_108;
        do {
          local_109 = *local_138;
          *local_130 = local_109;
          local_138 = local_138 + 1;
          local_130 = local_130 + 1;
        } while (local_109 != '\0');
        _strupr(local_108);
        local_110 = strstr(pcVar2,local_108);
        if ((local_110 != (char *)0x0) && (local_110 < local_140)) {
          local_110 = local_110 + ((int)local_128 - (int)(param_2 + 1)) + 1;
          pcVar2 = (char *)(DAT_009454d4 + DAT_009454d0);
          for (local_13c = 1;
              ((local_110 < pcVar2 && (*local_110 != '\n')) && (local_13c < param_4));
              local_13c = local_13c + 1) {
            *param_3 = *local_110;
            param_3 = param_3 + 1;
            local_110 = local_110 + 1;
          }
          *param_3 = '\0';
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

