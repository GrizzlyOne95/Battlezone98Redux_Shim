/*
 * Entry: 004d5747
 * Name: GetObjectName
 * Namespace: Global
 * Signature: char * GetObjectName(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl GetObjectName(GameObject *param_1)

{
  int iVar1;
  char *pcVar2;
  int in_ECX;
  
  if (in_ECX == 0) {
    return "NULL";
  }
  pcVar2 = *(char **)(in_ECX + 0xf4);
  if (pcVar2 == (char *)0x0) {
    iVar1 = (*(code *)**(undefined4 **)(in_ECX + 0x20))();
    sprintf(name,"label(NULL) odf(%s)",iVar1 + 0x40);
    pcVar2 = name;
  }
  return pcVar2;
}
