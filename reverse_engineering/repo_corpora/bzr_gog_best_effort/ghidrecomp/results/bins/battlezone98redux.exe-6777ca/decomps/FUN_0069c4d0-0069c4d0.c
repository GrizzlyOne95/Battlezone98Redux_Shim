
void FUN_0069c4d0(undefined4 param_1,char *param_2)

{
  bool bVar1;
  undefined1 local_b94 [4];
  int local_b90;
  char *local_b8c;
  undefined4 local_b88;
  uint local_b84;
  uint local_b80;
  int local_b7c;
  uint local_b78;
  int local_b74;
  char *local_b70;
  uint local_b6c;
  int local_b68;
  byte *local_b64;
  byte *local_b60;
  char *local_b5c;
  char *local_b58;
  int local_b54;
  char *local_b50;
  char local_b4c;
  byte local_b4b;
  byte local_b4a;
  char local_b49;
  undefined1 local_b48 [240];
  undefined1 local_a58 [120];
  undefined1 local_9e0 [8];
  int iStack_9d8;
  undefined1 local_968 [400];
  byte local_7d8 [2000];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b6c = 0;
  local_b88 = param_1;
  local_b58 = param_2;
  local_b8c = param_2 + 1;
  do {
    local_b4c = *local_b58;
    local_b58 = local_b58 + 1;
  } while (local_b4c != '\0');
  local_b90 = (int)local_b58 - (int)local_b8c;
  local_b50 = malloc(local_b90 + 1);
  local_b70 = param_2;
  local_b5c = local_b50;
  do {
    local_b49 = *local_b70;
    *local_b5c = local_b49;
    local_b70 = local_b70 + 1;
    local_b5c = local_b5c + 1;
  } while (local_b49 != '\0');
  FUN_0069a180(&local_b50,FUN_00699250,local_b50);
  FUN_0069bb80(local_b50,local_b94,local_9e0,local_b48,local_968,local_a58);
  local_b74 = FUN_006998c0(local_b88,local_968);
  if (local_b74 == 0) {
    free(local_b50);
  }
  else {
    local_b7c = *(int *)(local_b74 + 0x18);
    local_b68 = *(int *)(local_b7c + 4) * iStack_9d8;
    local_b54 = *(int *)(local_b7c + 8);
    while (local_b6c == 0) {
      if (local_b54 == 0) {
        free(local_b50);
        goto LAB_0069c7c4;
      }
      local_b64 = local_7d8;
      local_b60 = *(byte **)(local_b54 + 4);
      do {
        local_b4b = *local_b60;
        bVar1 = local_b4b < *local_b64;
        if (local_b4b != *local_b64) {
LAB_0069c731:
          local_b78 = -(uint)bVar1 | 1;
          goto LAB_0069c73c;
        }
        if (local_b4b == 0) break;
        local_b4a = local_b60[1];
        bVar1 = local_b4a < local_b64[1];
        if (local_b4a != local_b64[1]) goto LAB_0069c731;
        local_b60 = local_b60 + 2;
        local_b64 = local_b64 + 2;
      } while (local_b4a != 0);
      local_b78 = 0;
LAB_0069c73c:
      local_b84 = local_b78;
      local_b80 = (uint)(local_b78 == 0);
      local_b6c = local_b80;
      if (local_b80 == 0) {
        local_b68 = local_b68 + *(int *)(local_b54 + 8);
        local_b54 = *(int *)(local_b54 + 0xc);
      }
    }
    free(local_b50);
  }
LAB_0069c7c4:
  FUN_0083e885();
  return;
}

