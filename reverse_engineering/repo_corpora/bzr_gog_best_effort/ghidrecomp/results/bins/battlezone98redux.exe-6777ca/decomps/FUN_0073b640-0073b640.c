
void __thiscall
FUN_0073b640(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_0073add0(param_1);
  (**(code **)(*piVar1 + 0x1c))(param_2,param_3,param_4);
  FUN_007d6a70("galaxy::api::User()->SignIn(steamAppTicket, steamAppTicketLength, personaName);\n");
  return;
}

