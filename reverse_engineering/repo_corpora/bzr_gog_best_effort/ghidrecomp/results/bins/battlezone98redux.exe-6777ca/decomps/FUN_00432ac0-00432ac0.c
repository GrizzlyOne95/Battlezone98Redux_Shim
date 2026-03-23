
void FUN_00432ac0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 extraout_var;
  undefined4 uVar4;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar2 = Getal(&local_5);
  uVar4 = extraout_var;
  uVar3 = Getal(&local_6);
  cVar1 = operator!=<>(uVar3,uVar2,uVar4);
  if (cVar1 != '\0') {
                    /* WARNING: Subroutine does not return */
    terminate();
  }
  FUN_00432670(param_1,param_2,param_3,param_4,param_5);
  return;
}

