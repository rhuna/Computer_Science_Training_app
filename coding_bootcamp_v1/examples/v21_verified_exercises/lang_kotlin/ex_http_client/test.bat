@echo off
kotlinc Main.kt -include-runtime -d main.jar || exit /b 1
java -jar main.jar | findstr /C:"PASS_HTTP_CLIENT"
