@echo off
sqlite3 practice.db < queries.sql | findstr /C:"PASS_V15_CROSS_LANGUAGE_API_CLIENT"
