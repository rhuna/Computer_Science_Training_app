@echo off
python main.py | findstr /C:"PASS_DOCKER_PLAN"
