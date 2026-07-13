/*
 * Entry: 0041b521
 * Name: LuaMissionClass::Matches
 * Namespace: LuaMissionClass
 * Signature: int Matches(LuaMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __thiscall LuaMissionClass::Matches(LuaMissionClass *this,char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  char local_18 [8];
  uint local_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar6 = *(char **)&this->field_0x4;
  pcVar3 = pcVar6;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  iVar4 = _strnicmp(param_1,pcVar6,(int)pcVar3 - (int)(pcVar6 + 1));
  if (iVar4 == 0) {
    uVar5 = 1;
  }
  else {
    local_18[0] = '\0';
    local_18[1] = '\0';
    local_18[2] = '\0';
    local_18[3] = '\0';
    local_18[4] = '\0';
    local_18[5] = '\0';
    local_18[6] = '\0';
    local_18[7] = '\0';
    local_10 = 0;
    uStack_c = 0;
    strncpy(local_18,&msn_filename,8);
    local_10 = local_10 & 0xffffff00;
    pcVar6 = strchr(local_18,0x2e);
    if (pcVar6 != (char *)0x0) {
      *pcVar6 = '\0';
    }
    puVar2 = (undefined4 *)&stack0xffffffe7;
    do {
      puVar7 = puVar2;
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = 0x61756c2e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    iVar4 = ItemExists(local_18);
    uVar5 = (uint)(iVar4 != 0);
  }
  return uVar5;
}
