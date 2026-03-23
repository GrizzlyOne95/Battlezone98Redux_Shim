
void __thiscall FUN_00728d40(int param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  FUN_006d0c90();
  uVar1 = FUN_006d0d10();
  puVar2 = (undefined1 *)forward<>(1,uVar1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = *param_2;
  }
  FUN_0045ba10(*(undefined4 *)(param_1 + 4));
  return;
}

