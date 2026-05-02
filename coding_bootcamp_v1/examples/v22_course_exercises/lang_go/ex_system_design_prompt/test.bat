@echo off
go run . | findstr /C:"PASS_SYSTEM_DESIGN_PROMPT"
