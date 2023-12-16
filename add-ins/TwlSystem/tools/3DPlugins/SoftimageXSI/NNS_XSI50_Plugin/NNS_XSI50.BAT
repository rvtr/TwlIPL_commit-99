@echo off
call C:\Softimage\XSI_5.11\Application\bin\SETENV.BAT
set NNS_XSI_Plugin_ROOT=C:\NNS_XSI50_Plugin
echo "Starting Softimage(R) XSI v5.11"
echo "with NINTENDO NITRO-System Plugin for SOFTIMAGE|XSI"
xsi %1 
echo on
