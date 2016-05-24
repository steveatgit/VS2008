#include <stdio.h>
#include <windows.h>

int CrnGetImageFileMachine(char* lpFileName)
{
   IMAGE_DOS_HEADER idh;
   FILE *f = fopen(lpFileName, "rb");
   fread(&idh, sizeof(idh), 1, f);
   IMAGE_FILE_HEADER ifh;
   fseek(f, idh.e_lfanew + 4, SEEK_SET);
   fread(&ifh, sizeof(ifh), 1, f);
   fclose(f);

   return ifh.Machine;
}

int main(int argc, char *argv[])
{
   if(argc !=2) {
      printf("The number of params is wrong, should exe + fileName");
   }
   int n = CrnGetImageFileMachine(argv[1]);
   if (n == 0x014C) printf("x86\n");
   else if (n == 0x0200) printf("IA64\n");
   else if (n == 0x8664) printf("x64\n");
   else printf("don't know\n");

   return 1;
}