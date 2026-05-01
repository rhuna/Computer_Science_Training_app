@echo off
python main.py | findstr /C:"PASS_LRU_CACHE"
