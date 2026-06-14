#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void pathyExport(const char appName[256]) {
 char bashrcPath[256];
 snprintf(bashrcPath, sizeof(bashrcPath), "%s/.bashrc", getenv("HOME"));
 FILE *file = fopen(bashrcPath, "a");
 if(!file) {
  return;
 }
 char exportCommand[512];
 snprintf(exportCommand, sizeof(exportCommand), "export PATH=\"$PATH:%s/.pathy/apps/%s\"", getenv("HOME"), appName);
 fprintf(file, exportCommand);
 fclose(file);
}

int smkdir(const char *input) {
 char path[256];
 snprintf(path, sizeof(path), "%s%s", getenv("HOME"), input);
 if(mkdir(path, 0775)) {
  if(errno == EEXIST) {
   return 0;
  }
  return -1;
 }
 return 0;
}

int main(int argc, char *argv[]) {
 if(argc < 2) {
  printf("Pathy is a free, open source tool for adding your applications to path.\nUSAGE: pathy myTool\n");
  return 0;
 }
 const char *appName = argv[1];
 if(strcmp(appName, "help") == 0) {
  printf("Pathy is a free, open source tool for adding your applications to path.\nUSAGE: pathy myTool\n");
  return 0;
 }
 if(strcmp(appName, "license") == 0) {
  printf("MIT License Copyright (c) 2026 science-penguin Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n");
  return 0;
 }
 if(smkdir("/.pathy") == 0) {
  if(smkdir("/.pathy/apps") == 0) {
   char filePath[100];
   snprintf(filePath, sizeof(filePath), "/.pathy/apps/%s", appName);
   if(smkdir(filePath) == 0) {
    char command[512];
    snprintf(command, sizeof(command), "cp -r \"%s\" \"%s/.pathy/apps/\"", appName, getenv("HOME"));
    system(command);
    pathyExport(appName);
   } else {
    printf("FATAL ERROR IN MAKING DIR: \"$HOME%s\"\n", filePath);
    return 1;
   }
  } else {
   printf("FATAL ERROR IN MAKING DIR: \"$HOME/.pathy/apps\"\n");
   return 1;
  }
 } else {
  printf("FATAL ERROR IN MAKING DIR: \"$HOME/.pathy\"\n");
  return 1;
}
 return 0;
}
