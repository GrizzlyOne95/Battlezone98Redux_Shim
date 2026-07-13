
bool __thiscall FUN_00462a70(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (**(code **)(*(int *)(param_3 + 0x18) + 0x30))(param_1);
  switch(*(undefined4 *)(iVar2 + 0x84)) {
  case 1:
  case 6:
    iVar2 = FUN_0045bdf0();
    if (iVar2 == 0) {
      return false;
    }
    break;
  case 2:
    iVar2 = (*(code *)**(undefined4 **)(param_3 + 0x18))();
    if (*(int *)(iVar2 + 0x14) == 0x4745495a) {
      return false;
    }
    iVar2 = (*(code *)**(undefined4 **)(param_3 + 0x18))();
    if (*(int *)(iVar2 + 0x14) == 0x41525449) {
      return true;
    }
    break;
  case 3:
    iVar2 = (*(code *)**(undefined4 **)(param_3 + 0x18))();
    if (*(int *)(iVar2 + 0x14) != 0x544f5250) {
      return false;
    }
    break;
  case 5:
  case 7:
  case 10:
    return false;
  }
  cVar1 = FUN_004db510(param_3);
  return cVar1 != '\0';
}

