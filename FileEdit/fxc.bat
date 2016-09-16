set FXC="D:\Microsoft DirectX SDK (June 2010)\Utilities\bin\x86\fxc.exe"
%FXC% main_hlsl.fx /T fx_2_0 /Fo main_hlsl.cfx
%FXC% main_hlsl.fx /T fx_2_0 /Fc main_hlslAmb.asm
pause
