//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************
#include "stdafx.h"
#include "D3D12RaytracingHelloWorld.h"

struct CaptureOptions
{
  bool allowVSync;
  bool allowFullscreen;
  bool apiValidation;
  bool captureCallstacks;
  bool captureCallstacksOnlyActions;
  uint32_t delayForDebugger;
  bool verifyBufferAccess;
  bool hookIntoChildren;
  bool refAllResources;
  bool captureAllCmdLists;
  bool debugOutputMute;
  uint32_t softMemoryLimit;
};

typedef void *func(const char *);
typedef void *func2(CaptureOptions *);

//_Use_decl_annotations_
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
int main()
{
  const char *lib = R"(D:\CppProjects\renderdoc\x64\Development\renderdoc.dll)";
  HMODULE renderdoc = LoadLibraryA(lib);
  func *proc = (func *)GetProcAddress(renderdoc, "INTERNAL_SetCaptureFile");
  proc("test.rdc");

  // proc = (func *)GetProcAddress(renderdoc, "INTERNAL_SetDebugLogFile");
  // proc("debug.txt");

  CaptureOptions options = {true,  true,  false, false, false, 0,
                            false, false, false, false, true,  0};

  func2 *proc2 = (func2 *)GetProcAddress(renderdoc, "INTERNAL_SetCaptureOptions");
  proc2(&options);

  HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
  int nCmdShow = 10;
  D3D12RaytracingHelloWorld sample(1280, 720, L"D3D12 Raytracing - Hello World");
  return Win32Application::Run(&sample, hInstance, nCmdShow);
}
