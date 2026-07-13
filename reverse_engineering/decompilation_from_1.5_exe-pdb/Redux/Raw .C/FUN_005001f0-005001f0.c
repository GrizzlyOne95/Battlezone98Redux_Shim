
bool FUN_005001f0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  undefined4 local_8;
  
  uVar1 = FUN_004ff750(param_1,1);
  iVar2 = FUN_00462630(uVar1);
  if (iVar2 != 0) {
    iVar3 = (*(code *)**(undefined4 **)(iVar2 + 0x18))();
    local_8 = *(undefined4 *)(iVar3 + 0x14);
    local_c = (undefined1)((uint)local_8 >> 0x18);
    local_b = (undefined1)((uint)local_8 >> 0x10);
    local_a = (undefined1)((uint)local_8 >> 8);
    local_9 = (undefined1)local_8;
    FUN_0082cd08(param_1,&local_c,4);
  }
  return iVar2 != 0;
}

