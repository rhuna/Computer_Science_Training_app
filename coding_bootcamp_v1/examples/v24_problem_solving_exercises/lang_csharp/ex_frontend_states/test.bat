@echo off
dotnet run | findstr /C:"PASS_FRONTEND_STATES"
