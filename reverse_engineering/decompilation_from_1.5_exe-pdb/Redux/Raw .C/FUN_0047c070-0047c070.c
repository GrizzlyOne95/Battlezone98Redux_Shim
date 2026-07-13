
undefined4 __fastcall FUN_0047c070(undefined4 param_1)

{
  int iVar1;
  undefined3 uVar2;
  undefined1 local_5;
  
  local_5 = 0x61;
  iVar1 = FUN_00417c70(param_1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0xec) == 0) {
      iVar1 = (*(code *)**(undefined4 **)(iVar1 + 0x18))();
      local_5 = *(undefined1 *)(iVar1 + 0xcc);
      uVar2 = (undefined3)((uint)iVar1 >> 8);
    }
    else {
      local_5 = *(undefined1 *)(*(int *)(iVar1 + 0xec) + 0xcc);
      uVar2 = (undefined3)((uint)iVar1 >> 8);
    }
  }
  return CONCAT31(uVar2,local_5);
}

