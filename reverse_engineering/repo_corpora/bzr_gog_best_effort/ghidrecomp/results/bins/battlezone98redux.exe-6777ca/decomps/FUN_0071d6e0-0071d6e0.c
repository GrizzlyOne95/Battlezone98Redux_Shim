
int __fastcall FUN_0071d6e0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_48 [28];
  undefined1 local_2c [28];
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  *(undefined4 *)(param_1 + 0x200) = 0;
  *(undefined4 *)(param_1 + 0x204) = 0;
  local_8 = param_1;
  FUN_006f6650(local_2c);
  FUN_006f66a0(local_48);
  while( true ) {
    cVar1 = FUN_0071e8c0(local_2c,local_48);
    if ((cVar1 == '\0') || (0x3f < *(uint *)(local_8 + 0x200))) break;
    puVar2 = (undefined4 *)FUN_0071e880();
    local_10 = *puVar2;
    local_c = puVar2[1];
    FUN_006ae4c0(local_8 + *(int *)(local_8 + 0x200) * 8,&local_10);
    iVar3 = FUN_006ae390(&local_10);
    *(int *)(local_8 + 0x204) = iVar3 + *(int *)(local_8 + 0x204);
    FUN_0071e8a0();
    *(int *)(local_8 + 0x200) = *(int *)(local_8 + 0x200) + 1;
  }
  return local_8;
}

