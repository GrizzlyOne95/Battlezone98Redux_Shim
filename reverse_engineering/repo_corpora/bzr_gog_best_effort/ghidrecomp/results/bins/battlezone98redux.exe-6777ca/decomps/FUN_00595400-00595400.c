
undefined1 * __thiscall FUN_00595400(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  if (param_2 == 0) {
    puVar1 = &DAT_00874be8;
  }
  else {
    puVar1 = (undefined1 *)FUN_004623e0(param_1);
    if (puVar1 == (undefined1 *)0x0) {
      iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
      sprintf(&DAT_02cc3154,"label(NULL) odf(%s)",iVar2 + 0x38);
      puVar1 = &DAT_02cc3154;
    }
  }
  return puVar1;
}

