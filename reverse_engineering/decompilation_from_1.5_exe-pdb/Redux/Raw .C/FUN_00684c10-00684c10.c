
int __fastcall FUN_00684c10(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0x1c8) == 0) {
    local_c = 0;
  }
  else {
    local_c = *(int *)(param_1 + 0x1d4) -
              *(int *)(*(int *)(*(int *)(param_1 + 0x1c8) + 0x90) + 0x10);
  }
  return local_c;
}

