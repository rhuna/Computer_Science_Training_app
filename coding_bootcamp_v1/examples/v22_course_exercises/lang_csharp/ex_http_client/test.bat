@echo off
dotnet run | findstr /C:"PASS_HTTP_CLIENT"
