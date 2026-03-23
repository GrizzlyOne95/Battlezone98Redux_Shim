
void __thiscall FUN_00715820(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_10 [8];
  int local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0xa24) == 2) {
    *(undefined4 *)(param_1 + 0xa24) = 6;
    FUN_00715290(param_2);
  }
  else {
    FUN_006d08b0(0x400,"write_http_response_error called in invalid state");
    uVar1 = make_error_code(local_10,9);
    FUN_006daf10(uVar1);
  }
  return;
}

