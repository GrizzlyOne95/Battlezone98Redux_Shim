
void __thiscall FUN_006f2fa0(int *param_1,int *param_2)

{
  undefined4 uVar1;
  undefined1 local_14 [8];
  undefined1 local_c [4];
  int *local_8;
  
  local_8 = param_1;
  if (*param_1 == *param_2) {
    uVar1 = FUN_006d0d10();
    FUN_00447eb0(uVar1);
    FUN_006ff200(local_c);
  }
  else {
    uVar1 = FUN_006d4bb0();
    _Vector_iterator<>(local_8,uVar1);
    FUN_006ff240(local_14);
  }
  return;
}

