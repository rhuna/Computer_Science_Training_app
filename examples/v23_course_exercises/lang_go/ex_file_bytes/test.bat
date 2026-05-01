@echo off
go run . | findstr /C:"PASS_FILE_BYTES"
