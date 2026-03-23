
void __fastcall FUN_0043e100(int param_1)

{
  undefined4 uVar1;
  size_t local_22c;
  size_t local_228;
  void *local_224;
  void *local_220;
  int local_21c;
  int local_218;
  uint local_214;
  char local_20e;
  char local_20d;
  int local_20c;
  char local_208 [512];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_220 = (void *)0x0;
  local_224 = (void *)0x0;
  local_20e = '\0';
  local_20c = param_1;
  local_218 = FUN_0043d6c0(*(undefined4 *)(param_1 + 0x60),&local_20e);
  if (-1 < local_218) {
    if (local_20e == '\0') {
      local_218 = (**(code **)(**(int **)(local_20c + 0x60) + 0x10))
                            (*(undefined4 *)(local_20c + 0x60),&local_214,0);
      if (-1 < local_218) {
        local_20d = '\0';
        if (local_214 < *(uint *)(local_20c + 0x3c)) {
          local_21c = (*(int *)(local_20c + 0x4c) - *(int *)(local_20c + 0x3c)) + local_214;
          if ((*(uint *)(local_20c + 0x40) <= local_214) ||
             (*(uint *)(local_20c + 0x3c) < *(uint *)(local_20c + 0x40))) {
            local_20d = '\x01';
          }
        }
        else {
          local_21c = local_214 - *(int *)(local_20c + 0x3c);
          if ((local_214 <= *(uint *)(local_20c + 0x40)) &&
             (*(uint *)(local_20c + 0x40) < *(uint *)(local_20c + 0x3c))) {
            local_20d = '\x01';
          }
        }
        uVar1 = *(undefined4 *)(local_20c + 0x3c);
        *(int *)(local_20c + 0x58) = *(int *)(local_20c + 0x58) + local_21c;
        *(uint *)(local_20c + 0x3c) = local_214;
        if (*(uint *)(local_20c + 0x54) < *(uint *)(local_20c + 0x58)) {
          sprintf(local_208,"Buffer underrun: %ld Input, %ld Played\n",
                  *(undefined4 *)(local_20c + 0x54),*(undefined4 *)(local_20c + 0x58));
          OutputDebugStringA(local_208);
        }
        local_218 = (**(code **)(**(int **)(local_20c + 0x60) + 0x2c))
                              (*(undefined4 *)(local_20c + 0x60),uVar1,local_21c,&local_220,
                               &local_22c,&local_224,&local_228,0);
        if (-1 < local_218) {
          if (local_22c != 0) {
            memset(local_220,0,local_22c);
          }
          if (local_228 != 0) {
            memset(local_224,0,local_228);
          }
          if (local_20d != '\0') {
            (**(code **)(**(int **)(local_20c + 0x60) + 0x48))(*(undefined4 *)(local_20c + 0x60));
            *(undefined1 *)(local_20c + 0x3a) = 1;
            (**(code **)(**(int **)(local_20c + 0x60) + 0x34))(*(undefined4 *)(local_20c + 0x60),0);
            *(undefined4 *)(local_20c + 0x3c) = 0;
            *(undefined4 *)(local_20c + 0x40) = 0;
          }
          (**(code **)(**(int **)(local_20c + 0x60) + 0x4c))
                    (*(undefined4 *)(local_20c + 0x60),local_220,local_22c,local_224,local_228);
        }
      }
    }
    else {
      FUN_0043e420();
    }
  }
  FUN_0083e885();
  return;
}

