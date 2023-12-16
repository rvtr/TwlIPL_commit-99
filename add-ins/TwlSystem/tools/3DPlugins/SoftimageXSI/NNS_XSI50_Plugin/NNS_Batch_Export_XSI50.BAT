@echo off
call C:\Softimage\XSI_5.11\Application\bin\SETENV.BAT
set NNS_XSI_Plugin_ROOT=C:\NNS_XSI50_Plugin
set NNS_Batch_Export=%NNS_XSI_Plugin_ROOT%\NNS_Batch_Export.vbs
echo "Starting Softimage(R) XSI v5.11"
echo "with NINTENDO NITRO-System Plugin for SOFTIMAGE|XSI"

xsi -script %NNS_Batch_Export% -main command_main -args -arg0 %1

echo on
