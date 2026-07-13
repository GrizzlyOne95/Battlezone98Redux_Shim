
char * __fastcall FUN_00572790(undefined4 param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  
  uVar1 = FUN_00572810(param_1);
  switch(uVar1) {
  case 0:
    pcVar2 = "Initial";
    break;
  case 1:
    pcVar2 = "Player Creation";
    break;
  case 2:
    pcVar2 = "Created Player";
    break;
  case 3:
    pcVar2 = "Spawning";
    break;
  case 4:
    pcVar2 = "Running";
    break;
  case 5:
    pcVar2 = "Shutdown";
    break;
  case 6:
    pcVar2 = "Error";
    break;
  default:
    pcVar2 = "Unknown";
  }
  return pcVar2;
}

