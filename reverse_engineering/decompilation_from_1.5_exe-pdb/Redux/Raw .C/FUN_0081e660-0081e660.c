
int __fastcall FUN_0081e660(int param_1)

{
  undefined4 uVar1;
  undefined1 local_18 [8];
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1 == 0) {
    local_c = 0;
  }
  else {
    local_c = param_1 + 0x10;
  }
  local_8 = param_1;
  uVar1 = FUN_0081e9e0(local_18);
  FUN_006dba70(local_c,uVar1);
  if (local_8 == 0) {
    local_10 = 0;
  }
  else {
    local_10 = local_8 + 0x10;
  }
  return local_10;
}

