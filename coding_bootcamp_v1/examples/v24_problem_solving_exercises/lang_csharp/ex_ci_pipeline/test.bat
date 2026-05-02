@echo off
dotnet run | findstr /C:"PASS_CI_PIPELINE"
