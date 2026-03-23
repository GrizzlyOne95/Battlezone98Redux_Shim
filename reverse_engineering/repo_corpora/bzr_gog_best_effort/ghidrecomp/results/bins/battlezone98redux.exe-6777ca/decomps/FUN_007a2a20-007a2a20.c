
/* WARNING: Removing unreachable block (ram,0x007a2a5e) */

int __thiscall FUN_007a2a20(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  undefined1 local_6;
  undefined1 local_5;
  
  local_c = param_1;
  if (param_1 != param_2) {
    uVar1 = Getal(&local_5);
    uVar2 = Getal(&local_6);
    operator!=<>(uVar2,uVar1);
    puVar3 = (undefined4 *)FID_conflict_begin(local_10);
    uVar1 = *puVar3;
    puVar3 = (undefined4 *)FUN_00438c40(local_14);
    FUN_007a2c20(*puVar3,uVar1);
  }
  return local_c;
}

