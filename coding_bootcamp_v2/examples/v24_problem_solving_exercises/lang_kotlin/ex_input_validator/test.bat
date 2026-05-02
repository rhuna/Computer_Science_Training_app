@echo off
kotlinc Main.kt -include-runtime -d main.jar || exit /b 1
java -jar main.jar | findstr /C:"PASS_INPUT_VALIDATOR"
