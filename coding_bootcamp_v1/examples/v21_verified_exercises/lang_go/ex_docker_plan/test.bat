@echo off
go run . | findstr /C:"PASS_DOCKER_PLAN"
