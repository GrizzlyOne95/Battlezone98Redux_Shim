
void __thiscall FUN_0043dd30(int param_1,int param_2,int param_3)

{
  undefined2 uVar1;
  uint local_230;
  uint local_22c;
  int local_228;
  int local_224;
  uint local_220;
  int local_21c;
  int local_218;
  uint local_214;
  int local_210;
  int local_20c;
  char local_208 [512];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_224 = 0;
  local_230 = 0;
  local_228 = 0;
  local_220 = 0;
  local_20c = param_1;
  if (*(int *)(param_1 + 0x60) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
    local_218 = FUN_0043d6c0(*(undefined4 *)(local_20c + 0x60),0);
    if (local_218 < 0) {
      LeaveCriticalSection((LPCRITICAL_SECTION)(local_20c + 0x10));
    }
    else {
      if (*(uint *)(local_20c + 0x40) < *(uint *)(local_20c + 0x3c)) {
        local_21c = *(int *)(local_20c + 0x3c) - *(int *)(local_20c + 0x40);
      }
      else {
        local_21c = *(int *)(local_20c + 0x4c) -
                    (*(int *)(local_20c + 0x40) - *(int *)(local_20c + 0x3c));
      }
      local_218 = (**(code **)(**(int **)(local_20c + 0x60) + 0x2c))
                            (*(undefined4 *)(local_20c + 0x60),*(undefined4 *)(local_20c + 0x40),
                             local_21c,&local_224,&local_230,&local_228,&local_220,0);
      if (local_218 < 0) {
        LeaveCriticalSection((LPCRITICAL_SECTION)(local_20c + 0x10));
      }
      else {
        local_22c = local_230 >> 1;
        local_210 = 0;
        for (local_214 = 0; (local_210 < param_3 && (local_214 < local_22c));
            local_214 = local_214 + 1) {
          uVar1 = FUN_0043d670(*(undefined4 *)(param_2 + local_210 * 4));
          *(undefined2 *)(local_224 + local_214 * 2) = uVar1;
          local_210 = local_210 + 1;
        }
        local_22c = local_220 >> 1;
        for (local_214 = 0; (local_210 < param_3 && (local_214 < local_22c));
            local_214 = local_214 + 1) {
          uVar1 = FUN_0043d670(*(undefined4 *)(param_2 + local_210 * 4));
          *(undefined2 *)(local_228 + local_214 * 2) = uVar1;
          local_210 = local_210 + 1;
        }
        *(int *)(local_20c + 0x40) = *(int *)(local_20c + 0x40) + local_210 * 2;
        *(int *)(local_20c + 0x54) = *(int *)(local_20c + 0x54) + local_210 * 2;
        if (param_3 * 2 - local_21c != 0 && local_21c <= param_3 * 2) {
          sprintf(local_208,"Buffer Overrun: %ld Input, %ld Played, adding %d bytes, %d available\n"
                  ,*(undefined4 *)(local_20c + 0x54),*(undefined4 *)(local_20c + 0x58),param_3 << 1,
                  local_21c);
          OutputDebugStringA(local_208);
        }
        if (*(uint *)(local_20c + 0x4c) <= *(uint *)(local_20c + 0x40)) {
          *(int *)(local_20c + 0x40) = *(int *)(local_20c + 0x40) - *(int *)(local_20c + 0x4c);
        }
        (**(code **)(**(int **)(local_20c + 0x60) + 0x4c))
                  (*(undefined4 *)(local_20c + 0x60),local_224,local_230,local_228,local_220);
        if (*(char *)(local_20c + 0x3a) != '\0') {
          *(undefined1 *)(local_20c + 0x3a) = 0;
          local_218 = (**(code **)(**(int **)(local_20c + 0x60) + 0x30))
                                (*(undefined4 *)(local_20c + 0x60),0,0,1);
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)(local_20c + 0x10));
      }
    }
  }
  FUN_0083e885();
  return;
}

