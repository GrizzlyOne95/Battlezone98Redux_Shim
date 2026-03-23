
bool __thiscall
FUN_007ea6f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_10 [11];
  undefined1 local_5;
  
  FUN_0068f260(param_5);
  local_5 = 0;
  uVar3 = 0;
  puVar2 = (undefined4 *)FUN_004324a0(param_2,param_3,param_4);
  cVar1 = FUN_007eb790(param_1,local_10,*puVar2,puVar2[1],puVar2[2],uVar3);
  return cVar1 == '\0';
}

