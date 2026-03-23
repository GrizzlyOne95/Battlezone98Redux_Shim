
void __fastcall FUN_005faac0(int *param_1)

{
  char cVar1;
  undefined1 local_10;
  
  cVar1 = (**(code **)(*(int *)param_1[0xd] + 0x68))();
  if ((cVar1 == '\0') && (cVar1 = (**(code **)(*(int *)param_1[0xd] + 0x6c))(), cVar1 == '\0')) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  *(undefined1 *)(param_1 + 0x12) = local_10;
  if ((*(char *)((int)param_1 + 0x49) != '\0') && ((char)param_1[0x12] == '\0')) {
    cVar1 = (**(code **)(*(int *)param_1[0xd] + 0x68))();
    if (cVar1 == '\0') {
      FUN_005f91e0(param_1[0xd],0x17,0);
    }
    else {
      FUN_005f91e0(param_1[0xd],0x16,0);
    }
  }
  switch(param_1[7]) {
  case 3:
    (**(code **)(*param_1 + 0x38))();
    break;
  case 4:
    (**(code **)(*param_1 + 0x44))();
    break;
  case 5:
    (**(code **)(*param_1 + 0x50))();
    break;
  case 6:
    (**(code **)(*param_1 + 0x5c))();
    break;
  case 7:
    (**(code **)(*param_1 + 0x68))();
    break;
  case 8:
    (**(code **)(*param_1 + 0x74))();
    break;
  case 9:
    (**(code **)(*param_1 + 0x80))();
    break;
  case 10:
    (**(code **)(*param_1 + 0x8c))();
    break;
  case 0xb:
    (**(code **)(*param_1 + 0x98))();
    break;
  case 0xc:
    (**(code **)(*param_1 + 0xa4))();
    break;
  case 0xd:
    (**(code **)(*param_1 + 0xb0))();
    break;
  case 0xe:
    (**(code **)(*param_1 + 0xbc))();
    break;
  case 0xf:
    (**(code **)(*param_1 + 200))();
    break;
  case 0x10:
    (**(code **)(*param_1 + 0xd4))();
    break;
  case 0x11:
    (**(code **)(*param_1 + 0xe0))();
  }
  *(char *)((int)param_1 + 0x49) = (char)param_1[0x12];
  return;
}

