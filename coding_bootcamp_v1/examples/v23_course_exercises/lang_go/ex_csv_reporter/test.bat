@echo off
go run . | findstr /C:"PASS_CSV_REPORTER"
