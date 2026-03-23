
int __fastcall FUN_00462400(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0xf0) == 0) {
    local_c = *(int *)(param_1 + 0xf4) + 0xa0;
  }
  else {
    local_c = *(int *)(param_1 + 0xf0) + 8;
  }
  return local_c;
}

