@echo off
dotnet run | findstr /C:"PASS_FILE_BYTES"
