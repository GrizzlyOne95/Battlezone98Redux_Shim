
void __thiscall FUN_00416970(int param_1,int param_2,uint param_3,int param_4)

{
  size_t _Size;
  int iVar1;
  uint local_c;
  
  local_c = 0;
  do {
    _Size = param_3 - local_c;
    if ((*(int *)(param_1 + 0x28) == 0) || (*(int *)(param_1 + 0x24) != 0)) {
      memset((void *)(param_2 + local_c),0,_Size);
      local_c = local_c + _Size;
    }
    else {
      iVar1 = ov_read(*(undefined4 *)(param_1 + 0x2c),param_2 + local_c,_Size,0,2,1,param_1 + 0x30);
      if (iVar1 < 1) {
        if (iVar1 == 0) {
          if (param_4 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 1;
          }
          else {
            iVar1 = ov_raw_seek(*(undefined4 *)(param_1 + 0x2c),0,0);
            if (iVar1 != 0) {
              FUN_007d6a70("  ::Reset() got error %d\n",iVar1);
              *(undefined4 *)(param_1 + 0x24) = 1;
            }
          }
        }
        else {
          ov_clear(*(undefined4 *)(param_1 + 0x2c));
          *(undefined4 *)(param_1 + 0x28) = 0;
          *(undefined4 *)(param_1 + 0x24) = 1;
        }
      }
      else {
        local_c = local_c + iVar1;
        *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + iVar1;
      }
    }
  } while (local_c < param_3);
  return;
}

