
undefined4 __thiscall FUN_0049d150(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_0046fc10();
    if (*(int *)(param_1 + 0x228) == 0) {
      if (iVar3 == 0) {
        uVar2 = 0;
      }
      else if (iVar3 == 1) {
        cVar1 = FUN_0049c5c0();
        if (cVar1 == '\0') {
          iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
          if (*(int *)(iVar3 + 0x1c) == 2) {
            iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar3 + 0x14) == 0x4745495a) {
              uVar2 = 0;
            }
            else {
              uVar2 = 0x12;
            }
          }
          else {
            iVar3 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar3 + 0x14) == 0x54555252) {
              uVar2 = 0x12;
            }
            else {
              uVar2 = 0;
            }
          }
        }
        else {
          uVar2 = 0;
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

