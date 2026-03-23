
char __thiscall FUN_00817fc0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 local_6;
  char local_5;
  
  local_6 = 0;
  uVar1 = *(undefined4 *)*param_1;
  local_5 = FUN_00818070(param_2,&local_6);
  if (local_5 == '\0') {
    cVar2 = FUN_00817ad0(param_1[4],&local_6);
    local_5 = cVar2 == '\0';
    if ((bool)local_5) {
      *(undefined4 *)*param_1 = uVar1;
    }
  }
  return local_5;
}

