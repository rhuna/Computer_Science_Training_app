@echo off
dotnet run | findstr /C:"PASS_SQL_SCHEMA"
